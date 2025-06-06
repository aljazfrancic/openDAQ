/*
 * Copyright 2022-2025 openDAQ d.o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <coretypes/common.h>
#include <coreobjects/core_event_args.h>
#include <coretypes/event_args_impl.h>
#include <coretypes/validation.h>
#include <coreobjects/core_event_args_ptr.h>

BEGIN_NAMESPACE_OPENDAQ

namespace core_event_args_impl
{
    static std::string getCoreEventName(const CoreEventId id)
    {
        switch(id)
        {
            case CoreEventId::PropertyValueChanged:
                return "PropertyValueChanged";
            case CoreEventId::PropertyObjectUpdateEnd:
                return "PropertyObjectUpdateEnd";
            case CoreEventId::PropertyAdded:
                return "PropertyAdded";
            case CoreEventId::PropertyRemoved:
                return "PropertyRemoved";
            case CoreEventId::ComponentAdded:
                return "ComponentAdded";
            case CoreEventId::ComponentRemoved:
                return "ComponentRemoved";
            case CoreEventId::SignalConnected:
                return "SignalConnected";
            case CoreEventId::SignalDisconnected:
                return "SignalDisconnected";
            case CoreEventId::DataDescriptorChanged:
                return "DataDescriptorChanged";
            case CoreEventId::ComponentUpdateEnd:
                return "ComponentUpdateEnd";
            case CoreEventId::AttributeChanged:
                return "AttributeChanged";
            case CoreEventId::TagsChanged:
                return "TagsChanged";
            case CoreEventId::StatusChanged:
                return "StatusChanged";
            case CoreEventId::TypeAdded:
                return "TypeAdded";
            case CoreEventId::TypeRemoved:
                return "TypeRemoved";
            case CoreEventId::DeviceDomainChanged:
                return "DeviceDomainChanged";
            case CoreEventId::DeviceLockStateChanged:
                return "DeviceLockStateChanged";
            case CoreEventId::ConnectionStatusChanged:
                return "ConnectionStatusChanged";
            case CoreEventId::DeviceOperationModeChanged:
                return "DeviceOperationModeChanged";
            case CoreEventId::PropertyOrderChanged:
                return "PropertyOrderChanged";
            default:
                break;
        }

        return "Unknown";
    }
}


class CoreEventArgsImpl : public EventArgsBase<ICoreEventArgs, ISerializable>
{
public:
    explicit CoreEventArgsImpl (CoreEventId id, const DictPtr<IString, IBaseObject>& parameters);
    explicit CoreEventArgsImpl (CoreEventId id, const StringPtr& name, const DictPtr<IString, IBaseObject>& parameters);

    ErrCode INTERFACE_FUNC getParameters(IDict** parameters) override;
    
    ErrCode INTERFACE_FUNC serialize(ISerializer* serializer) override;
    ErrCode INTERFACE_FUNC getSerializeId(ConstCharPtr* id) const override;
    
    static ConstCharPtr SerializeId();

    static ErrCode Deserialize(ISerializedObject* ser, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj);

private:
    DictPtr<IString, IBaseObject> parameters;
    bool validateParameters() const;
};


inline CoreEventArgsImpl::CoreEventArgsImpl(CoreEventId id, const DictPtr<IString, IBaseObject>& parameters)
    : EventArgsImplTemplate<ICoreEventArgs, ISerializable>(static_cast<int>(id), core_event_args_impl::getCoreEventName(id))
    , parameters(parameters)
{
    if (!validateParameters())
        DAQ_THROW_EXCEPTION(InvalidParameterException, "Core event parameters for event type \"{}\" are invalid", this->eventName);
}

inline CoreEventArgsImpl::CoreEventArgsImpl(CoreEventId id, const StringPtr& name, const DictPtr<IString, IBaseObject>& parameters)
    : EventArgsImplTemplate<ICoreEventArgs, ISerializable>(static_cast<int>(id), name)
    , parameters(parameters)
{
    if (!validateParameters())
        DAQ_THROW_EXCEPTION(InvalidParameterException, "Core event parameters for event type \"{}\" are invalid", this->eventName);
}

inline ErrCode CoreEventArgsImpl::getParameters(IDict** parameters)
{
    OPENDAQ_PARAM_NOT_NULL(parameters);

    *parameters = this->parameters.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

inline ErrCode CoreEventArgsImpl::serialize(ISerializer* serializer)
{
    serializer->startTaggedObject(this);

    serializer->key("id");
    serializer->writeInt(this->eventId);

    serializer->key("name");
    serializer->writeString(this->eventName.getCharPtr(), this->eventName.getLength());

    serializer->key("params");
    ISerializable* serializableParams;
    ErrCode errCode = this->parameters->borrowInterface(ISerializable::Id, reinterpret_cast<void**>(&serializableParams));

    if (errCode == OPENDAQ_ERR_NOINTERFACE)
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NOT_SERIALIZABLE);

    OPENDAQ_RETURN_IF_FAILED(errCode);

    errCode = serializableParams->serialize(serializer);

    OPENDAQ_RETURN_IF_FAILED(errCode);

    serializer->endObject();

    return OPENDAQ_SUCCESS;
}

inline ErrCode CoreEventArgsImpl::getSerializeId(ConstCharPtr* id) const
{
    *id = SerializeId();

    return OPENDAQ_SUCCESS;
}

inline ConstCharPtr CoreEventArgsImpl::SerializeId()
{
    return "CoreEventArgs";
}

inline ErrCode CoreEventArgsImpl::Deserialize(ISerializedObject* ser, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj)
{
    Int id;
    ErrCode errCode = ser->readInt("id"_daq, &id);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    StringPtr name;
    errCode = ser->readString("name"_daq, &name);
    if (errCode == OPENDAQ_ERR_NOTFOUND)
    {
        daqClearErrorInfo();
        name = core_event_args_impl::getCoreEventName((CoreEventId) id);
        errCode = OPENDAQ_SUCCESS;
    }

    OPENDAQ_RETURN_IF_FAILED(errCode);

    BaseObjectPtr params;
    errCode = ser->readObject("params"_daq, context, factoryCallback, &params);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    try
    {
        CoreEventArgsPtr argsPtr; 
        createCoreEventArgs(&argsPtr, (CoreEventId) id, name, params.asPtr<IDict>());
        *obj = argsPtr.detach();
    }
    catch(const DaqException& e)
    {
        return errorFromException(e);
    }
    catch(...)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_GENERALERROR, "Unknown error occurred while deserializing CoreEventArgs");
    }

    return OPENDAQ_SUCCESS;
}

inline bool CoreEventArgsImpl::validateParameters() const
{
    switch(static_cast<CoreEventId>(eventId))
    {
        case CoreEventId::PropertyValueChanged:
            return parameters.hasKey("Name") && parameters.hasKey("Value") && parameters.hasKey("Path");
        case CoreEventId::PropertyObjectUpdateEnd:
            return parameters.hasKey("UpdatedProperties") && parameters.get("UpdatedProperties").supportsInterface<IDict>() && parameters.hasKey("Path");
        case CoreEventId::PropertyAdded:
            return parameters.hasKey("Property") && parameters.hasKey("Path");
        case CoreEventId::PropertyRemoved:
            return parameters.hasKey("Name") && parameters.hasKey("Path");
        case CoreEventId::ComponentAdded:
            return parameters.hasKey("Component");
        case CoreEventId::ComponentRemoved:
            return parameters.hasKey("Id");
        case CoreEventId::SignalConnected:
            return parameters.hasKey("Signal");
        case CoreEventId::DataDescriptorChanged:
            return parameters.hasKey("DataDescriptor");
        case CoreEventId::AttributeChanged:
            return parameters.hasKey("AttributeName");
        case CoreEventId::TagsChanged:
            return parameters.hasKey("Tags");
        case CoreEventId::TypeAdded:
            return parameters.hasKey("Type");
        case CoreEventId::TypeRemoved:
            return parameters.hasKey("TypeName");
        case CoreEventId::DeviceDomainChanged:
            return parameters.hasKey("DeviceDomain");
        case CoreEventId::DeviceLockStateChanged:
            return parameters.hasKey("IsLocked");
        case CoreEventId::ConnectionStatusChanged:
            return parameters.hasKey("StatusName")
                   && parameters.hasKey("StatusValue")
                   && parameters.hasKey("ConnectionString")
                   && parameters.hasKey("ProtocolType")
                   && parameters.hasKey("StreamingObject")
                   && parameters.hasKey("Message");
        case CoreEventId::DeviceOperationModeChanged:
            return parameters.hasKey("OperationMode");
        case CoreEventId::PropertyOrderChanged:
            return parameters.hasKey("PropertyOrder") && parameters.hasKey("Path");
        default:
            break;
    }

    return true;
}

OPENDAQ_REGISTER_DESERIALIZE_FACTORY(CoreEventArgsImpl)

END_NAMESPACE_OPENDAQ
