#include <coreobjects/property_value_event_args_impl.h>
#include <coretypes/validation.h>

BEGIN_NAMESPACE_OPENDAQ

ErrCode PropertyValueEventArgsImpl::getProperty(IProperty** prop)
{
    if (prop == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Cannot return property by a null pointer.");
    }

    *prop = property.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode PropertyValueEventArgsImpl::getValue(IBaseObject** value)
{
    if (value == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Cannot return the value by a null pointer");
    }

    *value = newValue.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode PropertyValueEventArgsImpl::getOldValue(IBaseObject** value)
{
    if (value == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Cannot return the old value by a null pointer");
    }

    *value = oldValue.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode PropertyValueEventArgsImpl::setValue(IBaseObject* value)
{
    newValue = value;
    return OPENDAQ_SUCCESS;
}

ErrCode PropertyValueEventArgsImpl::getPropertyEventType(PropertyEventType* changeType)
{
    OPENDAQ_PARAM_NOT_NULL(changeType);

    *changeType = type;
    return OPENDAQ_SUCCESS;
}

ErrCode PropertyValueEventArgsImpl::getIsUpdating(Bool* isUpdating)
{
    OPENDAQ_PARAM_NOT_NULL(isUpdating);

    *isUpdating = updating;
    return OPENDAQ_SUCCESS;
}

OPENDAQ_DEFINE_CLASS_FACTORY(LIBRARY_FACTORY, PropertyValueEventArgs, 
    IProperty*, prop, 
    IBaseObject*, value,
    IBaseObject*, oldValue, 
    PropertyEventType, type, 
    Bool, isUpdating)

END_NAMESPACE_OPENDAQ
