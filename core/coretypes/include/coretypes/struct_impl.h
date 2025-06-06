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
#include <coretypes/struct.h>
#include <coretypes/coretype.h>
#include <coretypes/intfs.h>
#include <coretypes/string_ptr.h>
#include <coretypes/dictobject_factory.h>
#include <coretypes/baseobject_factory.h>
#include <coretypes/struct_ptr.h>
#include <coretypes/enumeration_ptr.h>
#include <coretypes/type_manager_ptr.h>
#include <coretypes/struct_type_factory.h>
#include <coretypes/stringobject_factory.h>
#include <coretypes/simple_type_factory.h>
#include <coretypes/struct_builder_ptr.h>
#include <coretypes/deserializer.h>

BEGIN_NAMESPACE_OPENDAQ

template <class StructInterface, class... Interfaces>
class GenericStructImpl : public ImplementationOf<StructInterface, ICoreType, ISerializable, Interfaces...>
{
public:
    explicit GenericStructImpl(const StringPtr& name, DictPtr<IString, IBaseObject> fields, const TypeManagerPtr& typeManager);
    explicit GenericStructImpl(const StructBuilderPtr& builder);

    ErrCode INTERFACE_FUNC equals(IBaseObject* other, Bool* equal) const override;

    ErrCode INTERFACE_FUNC getStructType(IStructType** type) override;
    ErrCode INTERFACE_FUNC getFieldNames(IList** names) override;
    ErrCode INTERFACE_FUNC getFieldValues(IList** values) override;
    ErrCode INTERFACE_FUNC get(IString* name, IBaseObject** field) override;
    ErrCode INTERFACE_FUNC getAsDictionary(IDict** dictionary) override;
    ErrCode INTERFACE_FUNC hasField(IString* name, Bool* hasField) override;

    ErrCode INTERFACE_FUNC getCoreType(CoreType* coreType) override;

    ErrCode INTERFACE_FUNC serialize(ISerializer* serializer) override;
    ErrCode INTERFACE_FUNC getSerializeId(ConstCharPtr* id) const override;

    ErrCode INTERFACE_FUNC toString(CharPtr* str) override;
    
    static ConstCharPtr SerializeId();

    static ErrCode Deserialize(ISerializedObject* ser, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj);

protected:
    explicit GenericStructImpl(StructTypePtr type, DictPtr<IString, IBaseObject> fields);

    StructTypePtr structType;
    DictPtr<IString, IBaseObject> fields;
};

using StructImpl = GenericStructImpl<IStruct>;


template <class StructInterface, class... Interfaces>
GenericStructImpl<StructInterface, Interfaces...>::GenericStructImpl (StructTypePtr type, DictPtr<IString, IBaseObject> fields)
    : structType(std::move(type))
    , fields(std::move(fields))
{
    this->fields.freeze();
}

template <class StructInterface, class... Interfaces>
GenericStructImpl<StructInterface, Interfaces...>::GenericStructImpl(const StringPtr& name,
                                                                     DictPtr<IString, IBaseObject> fields,
                                                                     const TypeManagerPtr& typeManager)
{
    if (!typeManager.assigned())
        DAQ_THROW_EXCEPTION(InvalidParameterException, "Type manager must be assigned on custom Struct creation.");

    if (typeManager.hasType(name))
    {
        structType = typeManager.getType(name);
        const auto types = structType.getFieldTypes();
        const auto defaultValues = structType.getFieldDefaultValues();
        const auto names = structType.getFieldNames();

        std::unordered_set<std::string> namesSet;
        for (const auto& fieldName : names)
            namesSet.insert(fieldName);

        if (!fields.assigned())
            fields = Dict<IString, IBaseObject>();

        for (const auto& [key, val] : fields)
            if (!namesSet.count(key))
                DAQ_THROW_EXCEPTION(InvalidParameterException, R"(Struct field "{}" is not part of the Struct type)", key.toStdString());

        for (SizeT i = 0; i < types.getCount(); ++i)
        {
            auto fieldName = names[i];
            if (!fields.hasKey(fieldName))
            {
                if (defaultValues.assigned())
                    fields.set(fieldName, defaultValues[i]);
                else
                    fields.set(fieldName, nullptr);
            }
            else
            {
                auto fieldType = types[i];
                const auto field = fields.get(fieldName);
                if (!field.assigned())
                    continue;

                if (fieldType.getCoreType() == ctStruct && fieldType.template supportsInterface<IStructType>())
                {
                    StructPtr structObj = field;
                    if (structObj.getStructType() != fieldType)
                        DAQ_THROW_EXCEPTION(InvalidParameterException, R"(Struct field "{}" type mismatch.)", fieldName.toStdString());
                }
                else
                {
                    auto coreType = field.getCoreType();
                    auto fieldCoreType = fieldType.getCoreType();
                    if (fieldCoreType != ctUndefined && coreType != fieldCoreType)
                        DAQ_THROW_EXCEPTION(InvalidParameterException, R"(Struct field "{}" type mismatch.)", fieldName.toStdString());
                }
            }
        }
    }
    else
    {
        if (!fields.assigned())
            DAQ_THROW_EXCEPTION(InvalidParameterException, "Fields dictionary is missing.");

        auto types = List<IType>();
        auto fieldValues = fields.getValueList();
        for (SizeT i = 0; i < fieldValues.getCount(); ++i)
        {
            const auto val = fieldValues[i];
            if (!val.assigned())
            {
                types.pushBack(SimpleType(ctUndefined));
                continue;
            }
            const auto ct = val.getCoreType();
            if (ct == ctStruct)
                types.pushBack(val.asPtr<IStruct>().getStructType());
            else if (ct == ctEnumeration)
            {
                types.pushBack(val.asPtr<IEnumeration>().getEnumerationType());
            }
            else
                types.pushBack(SimpleType(ct));
        }

        structType = StructType(name, fields.getKeyList(), types);
        typeManager.addType(structType);
    }

    this->fields = std::move(fields);
    this->fields.freeze();
}

template <class StructInterface, class... Interfaces>
GenericStructImpl<StructInterface, Interfaces...>::GenericStructImpl (const StructBuilderPtr& builder)
{
    structType = builder.getStructType();

    const auto types = structType.getFieldTypes();
    const auto defaultValues = structType.getFieldDefaultValues();
    const auto names = structType.getFieldNames();

    std::unordered_set<std::string> namesSet;
    for (const auto& fieldName : names)
        namesSet.insert(fieldName);
    
    auto fields = builder.getAsDictionary();
    if (!fields.assigned())
        fields = Dict<IString, IBaseObject>();

    for (const auto& [key, val] : fields)
        if (!namesSet.count(key))
            DAQ_THROW_EXCEPTION(InvalidParameterException, R"(Struct field "{}" is not part of the Struct type)", key.toStdString());

    for (SizeT i = 0; i < types.getCount(); ++i)
    {
        auto fieldName = names[i];
        if (!fields.hasKey(fieldName))
        {
            if (defaultValues.assigned())
                fields.set(fieldName, defaultValues[i]);
            else
                fields.set(fieldName, nullptr);
        }
        else
        {
            auto fieldType = types[i];
            const auto field = fields.get(fieldName);
            if (!field.assigned())
                continue;

            if (fieldType.getCoreType() == ctStruct && fieldType.template supportsInterface<IStructType>())
            {
                StructPtr structObj = field;
                if (structObj.getStructType() != fieldType)
                    DAQ_THROW_EXCEPTION(InvalidParameterException, R"(Struct field "{}" type mismatch.)", fieldName.toStdString());
            }
            else
            {
                auto coreType = field.getCoreType();
                auto fieldCoreType = fieldType.getCoreType();
                if (fieldCoreType != ctUndefined && coreType != fieldCoreType)
                    DAQ_THROW_EXCEPTION(InvalidParameterException, R"(Struct field "{}" type mismatch.)", fieldName.toStdString());
            }
        }
    }
    
    this->fields = std::move(fields);
    this->fields.freeze();
}


template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::equals(IBaseObject* other, Bool* equal) const
{
    if (equal == nullptr)
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Equals out-parameter must not be null");

    *equal = false;
    if (other == nullptr)
        return OPENDAQ_SUCCESS;

    const StructPtr structOther = BaseObjectPtr::Borrow(other).asPtrOrNull<IStruct>();
    if (structOther == nullptr)
        return OPENDAQ_SUCCESS;

    *equal = structOther.getFieldValues() == fields.getValueList() && structOther.getFieldNames() == fields.getKeyList() && structOther.getStructType() == structType;
    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::getStructType(IStructType** type)
{
    OPENDAQ_PARAM_NOT_NULL(type);

    *type = this->structType.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl <StructInterface, Interfaces...>::getFieldNames(IList** names)
{
    OPENDAQ_PARAM_NOT_NULL(names);

    *names = this->fields.getKeyList().addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class ... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::getFieldValues(IList** values)
{
    OPENDAQ_PARAM_NOT_NULL(values);

    *values = this->fields.getValueList().addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl <StructInterface, Interfaces...>::get(IString* name, IBaseObject** field)
{
    if (!name)
    {
        *field = nullptr;
        return OPENDAQ_SUCCESS;
    }

    OPENDAQ_PARAM_NOT_NULL(field);

    const auto nameObj = StringPtr::Borrow(name);
    *field = this->fields.getOrDefault(name).addRefAndReturn();

    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class ... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::getAsDictionary(IDict** dictionary)
{
    OPENDAQ_PARAM_NOT_NULL(dictionary);

    *dictionary = this->fields.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::hasField(IString* name, Bool* hasField)
{
    OPENDAQ_PARAM_NOT_NULL(hasField);
    
    *hasField = false;
    if (!name)
        return OPENDAQ_SUCCESS;

    const auto nameObj = StringPtr::Borrow(name);
    if (this->fields.hasKey(name))
        *hasField = true;

    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::getCoreType(CoreType* coreType)
{
    OPENDAQ_PARAM_NOT_NULL(coreType);

    *coreType = ctStruct;
    return OPENDAQ_SUCCESS;
}


template <class StructInterface, class ... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::serialize(ISerializer* serializer)
{
    serializer->startTaggedObject(this);

    const StringPtr typeName = this->structType.getName();
    serializer->key("typeName");
    serializer->writeString(typeName.getCharPtr(), typeName.getLength());

    serializer->key("fields");
    ISerializable* serializableFields;
    ErrCode errCode = this->fields->borrowInterface(ISerializable::Id, reinterpret_cast<void**>(&serializableFields));

    if (errCode == OPENDAQ_ERR_NOINTERFACE)
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NOT_SERIALIZABLE);

    OPENDAQ_RETURN_IF_FAILED(errCode);

    errCode = serializableFields->serialize(serializer);

    OPENDAQ_RETURN_IF_FAILED(errCode);

    serializer->endObject();

    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class ... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::getSerializeId(ConstCharPtr* id) const
{
    *id = SerializeId();

    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class ... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::toString(CharPtr* str)
{
    OPENDAQ_PARAM_NOT_NULL(str);

    std::ostringstream strStream;
    bool first = true;
    auto fieldNames = structType.getFieldNames();
    for (daq::SizeT i = 0; i < fieldNames.getCount(); i++)
    {
        const StringPtr& fieldName = fieldNames[i];
        const BaseObjectPtr& fieldValue = fields[fieldName];

        if (!first)
            strStream << "; ";

        first = false;
        strStream << fieldName.toStdString() << "=" << (fieldValue.assigned() ? static_cast<std::string>(fieldValue) : "null");
    }

    const auto len = strStream.str().size() + 1;
    *str = static_cast<CharPtr>(daqAllocateMemory(len));
    OPENDAQ_PARAM_NOT_NULL(*str);

#if defined(__STDC_SECURE_LIB__) || defined(__STDC_LIB_EXT1__)
    strcpy_s(*str, len, strStream.str().c_str());
#else
    strncpy(*str, strStream.str().c_str(), len);
#endif
    return OPENDAQ_SUCCESS;
}

template <class StructInterface, class ... Interfaces>
ConstCharPtr GenericStructImpl<StructInterface, Interfaces...>::SerializeId()
{
    return "Struct";
}

template <class StructInterface, class... Interfaces>
ErrCode GenericStructImpl<StructInterface, Interfaces...>::Deserialize(
    ISerializedObject* ser, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj)
{
    TypeManagerPtr typeManager;
    if (context == nullptr || OPENDAQ_FAILED(context->queryInterface(ITypeManager::Id, reinterpret_cast<void**>(&typeManager))))
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NO_TYPE_MANAGER, "Type manager is required for deserialization of Struct");

    StringPtr typeName;
    ErrCode errCode = ser->readString("typeName"_daq, &typeName);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    BaseObjectPtr fields;
    errCode = ser->readObject("fields"_daq, context, factoryCallback, &fields);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    try
    {
        StructPtr structPtr;
        createStruct(&structPtr, typeName, fields.asPtr<IDict>(), typeManager);
        *obj = structPtr.detach();
    }
    catch(const DaqException& e)
    {
        return e.getErrCode();
    }
    catch(...)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_GENERALERROR);
    }

    return OPENDAQ_SUCCESS;
}

OPENDAQ_REGISTER_DESERIALIZE_FACTORY(StructImpl)

END_NAMESPACE_OPENDAQ
