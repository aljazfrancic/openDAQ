#include <coretypes/json_serialized_object.h>
#include <coretypes/coretypes.h>
#include <coretypes/json_deserializer_impl.h>
#include <coretypes/json_serialized_list.h>
#include <coretypes/serialization.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

BEGIN_NAMESPACE_OPENDAQ
JsonSerializedObject::JsonSerializedObject(const JsonObject& obj)
    : object(obj)
    , root(false)
{
}

JsonSerializedObject::JsonSerializedObject(const JsonObject& obj, bool isRoot)
    : object(obj)
    , root(isRoot)
{
}

ErrCode JsonSerializedObject::readSerializedObject(IString* key, ISerializedObject** plainObj)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        if (object[member].IsObject())
        {
            *plainObj = new(std::nothrow) JsonSerializedObject(object[member].GetObject());
            (*plainObj)->addRef();
            return OPENDAQ_SUCCESS;
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readSerializedList(IString* key, ISerializedList** list)
{
    using namespace rapidjson;

    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        if (object[member].IsArray())
        {
            SerializedListPtr serList;
            ErrCode err = createObject<ISerializedList, JsonSerializedList>(&serList, object[member].GetArray());
            if (OPENDAQ_FAILED(err))
            {
                return err;
            }

            *list = serList.addRefAndReturn();
            return OPENDAQ_SUCCESS;
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readList(IString* key, IBaseObject* context, IFunction* factoryCallback, IList** list)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        if (object[member].IsArray())
        {
            return JsonDeserializerImpl::Deserialize(object[member], context, factoryCallback, reinterpret_cast<IBaseObject**>(list));
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readObject(IString* key, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        return JsonDeserializerImpl::Deserialize(object[member], context, factoryCallback, obj);
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readString(IString* key, IString** string)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        if (object[member].IsString())
        {
            ErrCode errCode = createString(string, object[member].GetString());
            if (OPENDAQ_FAILED(errCode))
            {
                return errCode;
            }
            return OPENDAQ_SUCCESS;
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readBool(IString* key, Bool* boolean)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        if (object[member].IsBool())
        {
            *boolean = object[member].GetBool();

            return OPENDAQ_SUCCESS;
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readInt(IString* key, Int* integer)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        auto& value = object[member];
        if (value.IsInt())
        {
            *integer = value.GetInt();
            return OPENDAQ_SUCCESS;
        }

        if (value.IsInt64())
        {
            *integer = value.GetInt64();
            return OPENDAQ_SUCCESS;
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::readFloat(IString* key, Float* real)
{
    ConstCharPtr member;
    key->getCharPtr(&member);

    if (object.HasMember(member))
    {
        auto& value = object[member];
        if (value.IsDouble())
        {
            *real = value.GetDouble();

            return OPENDAQ_SUCCESS;
        }
        return OPENDAQ_ERR_INVALIDTYPE;
    }

    return OPENDAQ_ERR_NOTFOUND;
}

ErrCode JsonSerializedObject::getKeys(IList** list)
{
    ErrCode errCode = createList(list);
    if (OPENDAQ_FAILED(errCode))
    {
        return errCode;
    }

    for (const auto& prop : object)
    {
        errCode = (*list)->pushBack(String(prop.name.GetString()));

        if (OPENDAQ_FAILED(errCode))
        {
            return errCode;
        }
    }

    return OPENDAQ_SUCCESS;
}

ErrCode JsonSerializedObject::getType(IString* key, CoreType* type)
{
    OPENDAQ_PARAM_NOT_NULL(type);

    ConstCharPtr str;
    key->getCharPtr(&str);

    auto iter = object.FindMember(str);
    if (iter == object.MemberEnd())
    {
        return OPENDAQ_ERR_NOTFOUND;
    }

    *type = JsonDeserializerImpl::GetCoreType(iter->value);
    return OPENDAQ_SUCCESS;
}

ErrCode JsonSerializedObject::isRoot(Bool* isRoot)
{
    OPENDAQ_PARAM_NOT_NULL(isRoot);

    *isRoot = root;
    return OPENDAQ_SUCCESS;
}

ErrCode JsonSerializedObject::toJson(IString** jsonString)
{
    OPENDAQ_PARAM_NOT_NULL(jsonString);

    *jsonString = objToJson(object).detach();
    return OPENDAQ_SUCCESS;
}

ErrCode JsonSerializedObject::toString(CharPtr* str)
{
    OPENDAQ_PARAM_NOT_NULL(str);

    return daqDuplicateCharPtr("JsonSerializedObject", str);
}

StringPtr JsonSerializedObject::objToJson(const rapidjson::Value& val)
{
    rapidjson::StringBuffer sb;
    rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
    val.Accept(writer);
    std::string s = sb.GetString();
    return s;
}

ErrCode JsonSerializedObject::hasKey(IString* key, Bool* hasKey)
{
    ConstCharPtr ptr;
    key->getCharPtr(&ptr);

    *hasKey = object.HasMember(ptr);

    return OPENDAQ_SUCCESS;
}

END_NAMESPACE_OPENDAQ
