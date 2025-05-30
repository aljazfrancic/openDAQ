#include <coretypes/stringobject_impl.h>
#include <coretypes/errors.h>
#include <coretypes/impl.h>
#include <cstring>

BEGIN_NAMESPACE_OPENDAQ

StringImpl::StringImpl(ConstCharPtr data, SizeT length)
    : hashCode(0)
    , hashCalculated(false)
    , length(length)
{
    if (data == nullptr)
    {
        this->str = nullptr;
        this->length = 0;
    }
    else
    {
        this->str = new char[length + 1];

        memcpy(this->str, data, length);
        this->str[length] = '\0';
    }
}

StringImpl::StringImpl(ConstCharPtr str)
    : StringImpl(str, str == nullptr ? 0 : strlen(str))
{
}

StringImpl::~StringImpl()
{
    if (str != nullptr)
    {
        delete[] str;
        str = nullptr;
    }
}

ErrCode StringImpl::getHashCode(SizeT* hashCode)
{
    if (str == nullptr)
    {
        *hashCode = 0;
        return OPENDAQ_SUCCESS;
    }

    if (!hashCalculated)
    {
        uint32_t h = 0, high;
        char* s = str;

        while (*s)
        {
            h = (h << 4) + *s++;
            if ((high = h & 0xF0000000))
                h ^= high >> 24;
            h &= ~high;
        }
        this->hashCode = h;
        hashCalculated = true;
    }

    *hashCode = this->hashCode;
    return OPENDAQ_SUCCESS;
}

ErrCode StringImpl::equals(IBaseObject* other, Bool* equal) const
{
    if (equal == nullptr)
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Equal output parameter must not be null.");
    }

    if (other == nullptr)
    {
        *equal = false;
        return OPENDAQ_SUCCESS;
    }

    *equal = false;
    IString* otherString;

    if (OPENDAQ_SUCCEEDED(other->borrowInterface(IString::Id, reinterpret_cast<void**>(&otherString))))
    {
        SizeT otherLength;
        auto err = otherString->getLength(&otherLength);
        OPENDAQ_RETURN_IF_FAILED(err);

        if (otherLength != length)
        {
            return OPENDAQ_SUCCESS;
        }

        ConstCharPtr otherValue;
        err = otherString->getCharPtr(&otherValue);
        OPENDAQ_RETURN_IF_FAILED(err);

        if (otherValue == nullptr)
        {
            *equal = str == nullptr;
        }
        else
        {
            *equal = strcmp(str, otherValue) == 0;
        }
    }

    return OPENDAQ_SUCCESS;
}

ErrCode StringImpl::getCharPtr(ConstCharPtr* value)
{
    *value = str;
    return OPENDAQ_SUCCESS;
}

ErrCode StringImpl::getLength(SizeT* size)
{
    *size = length;
    return OPENDAQ_SUCCESS;
}

ErrCode StringImpl::toString(CharPtr* str)
{
    OPENDAQ_PARAM_NOT_NULL(str);

    return daqDuplicateCharPtr(this->str, str);
}

ErrCode StringImpl::toFloat(Float* val)
{
    try
    {
        *val = std::stod(std::string(str));
        return OPENDAQ_SUCCESS;
    }
    catch (const std::exception& e)
    {
        return errorFromException(e, nullptr, OPENDAQ_ERR_CONVERSIONFAILED);
    }
}

ErrCode StringImpl::toInt(Int* val)
{
    try
    {
        *val = std::stoll(std::string(str));
        return OPENDAQ_SUCCESS;
    }
    catch (const std::exception& e)
    {
        return errorFromException(e, nullptr, OPENDAQ_ERR_CONVERSIONFAILED);
    }
}

ErrCode StringImpl::toBool(Bool* val)
{
    if (length == 0)
        *val = False;
#if defined(_WIN32)
    else if (_stricmp("True", str) == 0)
#else
    else if (strcasecmp("True", str) == 0)
#endif
        *val = True;
    else
    {
        Int intVal;
        ErrCode errCode = toInt(&intVal);
        if (OPENDAQ_SUCCEEDED(errCode))
            *val = intVal != 0 ? True : False;
        else
            *val = False;
    }
    return OPENDAQ_SUCCESS;
}

ErrCode StringImpl::getCoreType(CoreType* coreType)
{
    *coreType = ctString;
    return OPENDAQ_SUCCESS;
}

ErrCode StringImpl::compareTo(IBaseObject* obj)
{
    if (obj == nullptr)
        return  OPENDAQ_LOWER;

    ConstCharPtr otherValue = nullptr;
    CharPtr otherValueOwned = nullptr;

    IString* otherString = nullptr;
    ErrCode err = obj->borrowInterface(IString::Id, reinterpret_cast<void**>(&otherString));
    if (OPENDAQ_FAILED(err))
    {
        err = obj->toString(&otherValueOwned);
        OPENDAQ_RETURN_IF_FAILED(err);
        otherValue = otherValueOwned;
    }
    else
    {
        err = otherString->getCharPtr(&otherValue);
        OPENDAQ_RETURN_IF_FAILED(err);
    }

    int r = strcmp(str, otherValue);
    if (r > 0)
        err = OPENDAQ_GREATER;
    else if (r < 0)
        err = OPENDAQ_LOWER;
    else
        err = OPENDAQ_EQUAL;

    if (otherValueOwned)
        daqFreeMemory(otherValueOwned);

    return err;
}

ErrCode StringImpl::getSerializeId(ConstCharPtr* /*id*/) const
{
    return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_NOTIMPLEMENTED);
}

ErrCode StringImpl::serialize(ISerializer* serializer)
{
    SizeT length;
    ErrCode errCode = getLength(&length);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    serializer->writeString(str, length);

    return OPENDAQ_SUCCESS;
}

OPENDAQ_DEFINE_CLASS_FACTORY(LIBRARY_FACTORY, String, ConstCharPtr, str)
OPENDAQ_DEFINE_CLASS_FACTORY_WITH_INTERFACE_AND_CREATEFUNC_OBJ(
    LIBRARY_FACTORY, StringImpl, IString, createStringN,
    ConstCharPtr, str,
    SizeT, length
)

END_NAMESPACE_OPENDAQ
