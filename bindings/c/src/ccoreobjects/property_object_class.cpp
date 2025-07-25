//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CGenerator v0.7.0) on 03.06.2025 22:05:17.
// </auto-generated>
//------------------------------------------------------------------------------

#include <ccoreobjects/property_object_class.h>

#include <opendaq/opendaq.h>

#include <copendaq_private.h>

const daqIntfID DAQ_PROPERTY_OBJECT_CLASS_INTF_ID = { daq::IPropertyObjectClass::Id.Data1, daq::IPropertyObjectClass::Id.Data2, daq::IPropertyObjectClass::Id.Data3, daq::IPropertyObjectClass::Id.Data4_UInt64 };

daqErrCode daqPropertyObjectClass_getParentName(daqPropertyObjectClass* self, daqString** parentName)
{
    return reinterpret_cast<daq::IPropertyObjectClass*>(self)->getParentName(reinterpret_cast<daq::IString**>(parentName));
}

daqErrCode daqPropertyObjectClass_getProperty(daqPropertyObjectClass* self, daqString* propertyName, daqProperty** property)
{
    return reinterpret_cast<daq::IPropertyObjectClass*>(self)->getProperty(reinterpret_cast<daq::IString*>(propertyName), reinterpret_cast<daq::IProperty**>(property));
}

daqErrCode daqPropertyObjectClass_hasProperty(daqPropertyObjectClass* self, daqString* propertyName, daqBool* hasProperty)
{
    return reinterpret_cast<daq::IPropertyObjectClass*>(self)->hasProperty(reinterpret_cast<daq::IString*>(propertyName), hasProperty);
}

daqErrCode daqPropertyObjectClass_getProperties(daqPropertyObjectClass* self, daqBool includeInherited, daqList** properties)
{
    return reinterpret_cast<daq::IPropertyObjectClass*>(self)->getProperties(includeInherited, reinterpret_cast<daq::IList**>(properties));
}

daqErrCode daqPropertyObjectClass_createPropertyObjectClassFromBuilder(daqPropertyObjectClass** obj, daqPropertyObjectClassBuilder* builder)
{
    daq::IPropertyObjectClass* ptr = nullptr;
    daqErrCode err = daq::createPropertyObjectClassFromBuilder(&ptr, reinterpret_cast<daq::IPropertyObjectClassBuilder*>(builder));
    *obj = reinterpret_cast<daqPropertyObjectClass*>(ptr);
    return err;
}
