#include <opendaq/logger_impl.h>
#include <coretypes/impl.h>
#include <coretypes/validation.h>
#include <opendaq/logger_component_factory.h>
#include <opendaq/logger_sink_factory.h>
#include <opendaq/logger_sink_base_private_ptr.h>
#include <opendaq/logger_thread_pool_factory.h>
#include <spdlog/async.h>
#include <spdlog/spdlog.h>
#include <functional>
#include <utility>
#include <coretypes/ctutils.h>
#include <memory.h>
#include <iostream>

#include "opendaq/utils/thread_name.h"

BEGIN_NAMESPACE_OPENDAQ
LoggerImpl::LoggerImpl(const ListPtr<ILoggerSink>& sinksList, LogLevel level)
    : threadPool(LoggerThreadPool())
    , level(level)
    , flushLevel(LogLevel::Off)
{
    if (!sinksList.assigned())
    {
        DAQ_THROW_EXCEPTION(ArgumentNullException, "Sinks List must not be null.");
    }
    for (const ObjectPtr<ILoggerSink>& sink : sinksList)
    {
        if(!sink.assigned())
        {
            DAQ_THROW_EXCEPTION(ArgumentNullException, "Sink must not be null.");
        }
        if(!sink.supportsInterface<ILoggerSinkBasePrivate>())
        {
            DAQ_THROW_EXCEPTION(InvalidTypeException, "Sink must have valid type.");
        }
        sinks.push_back(sink);
    }

    using namespace std::chrono_literals;
    auto callback = [this]() { this->flush(); };
    auto initThread = []() { utils::setThreadName("LogPerWorker"); };
    periodicFlushWorker = std::make_unique<LoggerFlushWorker>(initThread, callback, 5s);
}

ErrCode LoggerImpl::setLevel(LogLevel level)
{
    this->level = level;
    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::getLevel(LogLevel* level)
{
    if (level == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Can not return by a null pointer.");
    }
    *level = this->level;

    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::getOrAddComponent(IString* name, ILoggerComponent** component)
{
    if (component == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Can not return by a null pointer.");
    }

    if (name == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Name can not be null.");
    }

    if (StringPtr::Borrow(name).getLength() == 0)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALIDPARAMETER, "Name can not be empty.");
    }

    std::lock_guard<std::mutex> lock(addComponentMutex);

    auto componentIt = components.find(toStdString(name));
    if (componentIt != components.end())
    {
        *component = componentIt->second.addRefAndReturn();
        return OPENDAQ_SUCCESS;
    }

    LoggerComponentPtr componentPtr = LoggerComponent(name, ListPtr<ILoggerSink>{sinks}, threadPool, level);
    componentPtr.flushOnLevel(this->flushLevel);
    auto res = components.insert({toStdString(name), componentPtr});
    if (!res.second)
    {
        return DAQ_MAKE_ERROR_INFO(
            OPENDAQ_ERR_ALREADYEXISTS,
            "Can't add LoggerComponent with already existent name [" + toStdString(name) + "]"
            );
    }

    *component = componentPtr.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::addComponent(IString* name, ILoggerComponent** component)
{
    if (component == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Can not return by a null pointer.");
    }

    if (name == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Name can not be null.");
    }

    if ( toStdString(name).empty() )
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALIDPARAMETER, "Name can not be empty.");
    }

    LoggerComponentPtr componentPtr = LoggerComponent(name, ListPtr<ILoggerSink>{sinks}, threadPool, level);
    componentPtr.flushOnLevel(this->flushLevel);

    {
        std::lock_guard<std::mutex> lock(addComponentMutex);
        auto res = components.insert({toStdString(name), componentPtr});
        if (!res.second)
        {
            return DAQ_MAKE_ERROR_INFO(
                OPENDAQ_ERR_ALREADYEXISTS,
                "Can't add LoggerComponent with already existent name [" + toStdString(name) + "]"
            );
        }
    }

    *component = componentPtr.addRefAndReturn();

    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::removeComponent(IString* name)
{
    OPENDAQ_PARAM_NOT_NULL(name);

    std::lock_guard<std::mutex> lock(addComponentMutex);

    auto componentIt = components.find(toStdString(name));
    if (componentIt == components.end())
    {
        return DAQ_MAKE_ERROR_INFO(
            OPENDAQ_ERR_NOTFOUND,
            "LoggerComponent with the specified name does not exist"
        );
    }

    componentIt->second.flush();
    components.erase(componentIt);

    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::getComponents(IList** list)
{
    if (list == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Can not return by a null pointer.");
    }

    auto componentsPtr = List<ILoggerComponent>();

    {
        std::lock_guard<std::mutex> lock(addComponentMutex);
        for (const auto& component : components)
        {
            componentsPtr.pushBack(component.second);
        }
    }

    *list = componentsPtr.detach();
    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::getComponent(IString* name, ILoggerComponent** component)
{
    if (component == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Can not return by a null pointer.");
    }
    if (name == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Name can not be null.");
    }

    std::lock_guard<std::mutex> lock(addComponentMutex);

    auto componentIt = components.find(toStdString(name));
    if (componentIt == components.end())
    {
        return DAQ_MAKE_ERROR_INFO(
            OPENDAQ_ERR_NOTFOUND,
            "LoggerComponent with the specified name not found"
        );
    }

    *component = componentIt->second.addRefAndReturn();

    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::flush()
{
    flushComponents();
    flushSinks();

    return OPENDAQ_SUCCESS;
}

ErrCode LoggerImpl::flushOnLevel(LogLevel level)
{
    this->flushLevel = level;

    std::lock_guard<std::mutex> lock(addComponentMutex);
    for (const auto& component : components)
    {
        component.second.flushOnLevel(this->flushLevel);
    }

    return OPENDAQ_SUCCESS;
}

void LoggerImpl::flushComponents()
{
    std::lock_guard<std::mutex> lock(addComponentMutex);

    for (const auto& component : components)
    {
        component.second.flush();
    }
}

void LoggerImpl::flushSinks()
{
    for (const auto& sink : sinks)
    {
        sink.flush();
    }
}

OPENDAQ_DEFINE_CLASS_FACTORY(LIBRARY_FACTORY, Logger, IList*, sinks, LogLevel, level)

END_NAMESPACE_OPENDAQ
