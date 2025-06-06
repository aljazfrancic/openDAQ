#include <coretypes/event_impl.h>
#include <algorithm>

BEGIN_NAMESPACE_OPENDAQ

EventImpl::EventImpl()
{
    handlers.reserve(5);
}

ErrCode EventImpl::addHandler(IEventHandler* eventHandler)
{
    OPENDAQ_PARAM_NOT_NULL(eventHandler);

    std::scoped_lock lock(sync);

    if (frozen)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_FROZEN);
    }

    handlers.emplace_back(Handler{ eventHandler, false });
    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::removeHandler(IEventHandler* eventHandler)
{
    OPENDAQ_PARAM_NOT_NULL(eventHandler);

    std::scoped_lock lock(sync);

    if (frozen)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_FROZEN);
    }

    SizeT hashCode;
    ErrCode errCode = eventHandler->getHashCode(&hashCode);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    const ConstIterator iterator = std::find_if(handlers.begin(),
                                                handlers.end(),
                                                [hashCode](const Handler& lhs)
                                                {
                                                    return lhs.eventHandler.getHashCode() == hashCode;
                                                });

    if (iterator != handlers.cend())
    {
        handlers.erase(iterator);
    }
    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::clear()
{
    std::scoped_lock lock(sync);

    if (frozen)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_FROZEN);
    }

    handlers.clear();

    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::getSubscriberCount(SizeT* count)
{
    std::scoped_lock lock(sync);

    *count = handlers.size();

    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::getSubscribers(IList** subscribers)
{
    OPENDAQ_PARAM_NOT_NULL(subscribers);

	std::scoped_lock lock(sync);

    auto list = List<IEventHandler>();

    for (const auto& handler : handlers)
        list.pushBack(handler.eventHandler);

	*subscribers = list.detach();
	return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::trigger(IBaseObject* sender, IEventArgs* args)
{
    std::scoped_lock lock(sync);

    if (muted)
    {
        return OPENDAQ_SUCCESS;
    }

    for (const Handler& handler : handlers)
    {
        if (!handler.muted)
        {
            const ErrCode errCode = handler.eventHandler->handleEvent(sender, args);
            OPENDAQ_RETURN_IF_FAILED(errCode);
            continue;
        }

    }

    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::freeze()
{
    std::scoped_lock lock(sync);

    if (frozen)
        return  OPENDAQ_IGNORED;

    frozen = true;
    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::isFrozen(Bool* isFrozen) const
{
    std::scoped_lock lock(sync);

    *isFrozen = frozen;

    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::toString(CharPtr* str)
{
    return daqDuplicateCharPtr("Event", str);
}

ErrCode EventImpl::mute()
{
    std::scoped_lock lock(sync);

    muted = true;
    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::unmute()
{
    std::scoped_lock lock(sync);

    muted = false;
    return OPENDAQ_SUCCESS;
}

ErrCode EventImpl::muteListener(IEventHandler* eventHandler)
{
    std::scoped_lock lock(sync);

    return setMuted(eventHandler, true);
}

ErrCode EventImpl::unmuteListener(IEventHandler* eventHandler)
{
    std::scoped_lock lock(sync);

    return setMuted(eventHandler, false);
}

ErrCode EventImpl::setMuted(IEventHandler* eventHandler, bool muted)
{
    OPENDAQ_PARAM_NOT_NULL(eventHandler);

    SizeT hashCode;
    ErrCode errCode = eventHandler->getHashCode(&hashCode);

    OPENDAQ_RETURN_IF_FAILED(errCode);

    const Iterator iterator = std::find_if(handlers.begin(),
        handlers.end(),
        [hashCode](const Handler& lhs)
    {
        return lhs.eventHandler.getHashCode() == hashCode;
    });

    if (iterator != handlers.end())
        iterator->muted = muted;

    return OPENDAQ_SUCCESS;
}

OPENDAQ_DEFINE_CLASS_FACTORY(LIBRARY_FACTORY, Event)

END_NAMESPACE_OPENDAQ
