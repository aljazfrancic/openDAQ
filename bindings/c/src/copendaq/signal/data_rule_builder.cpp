//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CGenerator v0.7.0) on 03.06.2025 22:07:41.
// </auto-generated>
//------------------------------------------------------------------------------

#include <copendaq/signal/data_rule_builder.h>

#include <opendaq/opendaq.h>

#include <copendaq_private.h>

const daqIntfID DAQ_DATA_RULE_BUILDER_INTF_ID = { daq::IDataRuleBuilder::Id.Data1, daq::IDataRuleBuilder::Id.Data2, daq::IDataRuleBuilder::Id.Data3, daq::IDataRuleBuilder::Id.Data4_UInt64 };

daqErrCode daqDataRuleBuilder_build(daqDataRuleBuilder* self, daqDataRule** dataRule)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->build(reinterpret_cast<daq::IDataRule**>(dataRule));
}

daqErrCode daqDataRuleBuilder_setType(daqDataRuleBuilder* self, daqDataRuleType type)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->setType(static_cast<daq::DataRuleType>(type));
}

daqErrCode daqDataRuleBuilder_getType(daqDataRuleBuilder* self, daqDataRuleType* type)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->getType(reinterpret_cast<daq::DataRuleType*>(type));
}

daqErrCode daqDataRuleBuilder_setParameters(daqDataRuleBuilder* self, daqDict* parameters)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->setParameters(reinterpret_cast<daq::IDict*>(parameters));
}

daqErrCode daqDataRuleBuilder_getParameters(daqDataRuleBuilder* self, daqDict** parameters)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->getParameters(reinterpret_cast<daq::IDict**>(parameters));
}

daqErrCode daqDataRuleBuilder_addParameter(daqDataRuleBuilder* self, daqString* name, daqBaseObject* parameter)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->addParameter(reinterpret_cast<daq::IString*>(name), reinterpret_cast<daq::IBaseObject*>(parameter));
}

daqErrCode daqDataRuleBuilder_removeParameter(daqDataRuleBuilder* self, daqString* name)
{
    return reinterpret_cast<daq::IDataRuleBuilder*>(self)->removeParameter(reinterpret_cast<daq::IString*>(name));
}

daqErrCode daqDataRuleBuilder_createDataRuleBuilder(daqDataRuleBuilder** obj)
{
    daq::IDataRuleBuilder* ptr = nullptr;
    daqErrCode err = daq::createDataRuleBuilder(&ptr);
    *obj = reinterpret_cast<daqDataRuleBuilder*>(ptr);
    return err;
}

daqErrCode daqDataRuleBuilder_createDataRuleBuilderFromExisting(daqDataRuleBuilder** obj, daqDataRule* ruleToCopy)
{
    daq::IDataRuleBuilder* ptr = nullptr;
    daqErrCode err = daq::createDataRuleBuilderFromExisting(&ptr, reinterpret_cast<daq::IDataRule*>(ruleToCopy));
    *obj = reinterpret_cast<daqDataRuleBuilder*>(ptr);
    return err;
}
