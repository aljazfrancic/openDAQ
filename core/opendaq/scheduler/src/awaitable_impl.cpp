#include <opendaq/awaitable_impl.h>
#include <opendaq/scheduler_errors.h>
#include <coretypes/objectptr.h>

BEGIN_NAMESPACE_OPENDAQ

template <typename TReturn>
AwaitableImpl<TReturn>::AwaitableImpl(Future future)
    : future(std::move(future))
    , completed(false)
{
}

template <typename TReturn>
ErrCode AwaitableImpl<TReturn>::cancel(Bool* canceled)
{
    *canceled = future.cancel();
    return OPENDAQ_SUCCESS;
}

template <typename TReturn>
ErrCode AwaitableImpl<TReturn>::wait()
{
    if (completed)
    {
        return  OPENDAQ_IGNORED;
    }

    if (!future.valid())
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_EMPTY_AWAITABLE);
    }

    OPENDAQ_TRY(
        future.wait();
        completed = true; 
    )

    return OPENDAQ_SUCCESS;
}

template <typename TReturn>
ErrCode AwaitableImpl<TReturn>::getResult(daq::IBaseObject** result)
{
    OPENDAQ_PARAM_NOT_NULL(result);

    if (!completed && !future.valid())
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_EMPTY_AWAITABLE);
    }

    if constexpr (std::is_void_v<TReturn>)
    {
        future.get();
        *result = nullptr;
    }
    else
    {
        std::optional<BaseObjectPtr> optional;
        OPENDAQ_TRY(optional = future.get();)

        completed = true;

        if (!optional.has_value())
        {
            *result = nullptr;
        }
        else
        {
            *result = optional->addRefAndReturn();
        }
    }
    return OPENDAQ_SUCCESS;
}

template <typename TReturn>
ErrCode AwaitableImpl<TReturn>::hasCompleted(Bool* finished)
{
    OPENDAQ_PARAM_NOT_NULL(finished);

    if (!future.valid())
        *finished = this->completed.load();

    *finished = !future.valid();
    return OPENDAQ_SUCCESS;
}

template class AwaitableImpl<void>;
template class AwaitableImpl<std::optional<ObjectPtr<IBaseObject>>>;

END_NAMESPACE_OPENDAQ
