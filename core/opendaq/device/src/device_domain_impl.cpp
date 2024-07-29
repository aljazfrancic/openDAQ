#include <coretypes/validation.h>
#include <opendaq/device_domain_impl.h>
#include <opendaq/device_domain_factory.h>

BEGIN_NAMESPACE_OPENDAQ

namespace detail
{
    static const StructTypePtr deviceDomainStructType = DeviceDomainStructType();
}

DeviceDomainImpl::DeviceDomainImpl(
    RatioPtr tickResolution, StringPtr origin, UnitPtr unit, StringPtr referenceDomainId, IntegerPtr referenceDomainOffset)
    : GenericStructImpl<IDeviceDomain, IStruct>(detail::deviceDomainStructType,
                                                Dict<IString, IBaseObject>({{"TickResolution", std::move(tickResolution)},
                                                                            {"Origin", std::move(origin)},
                                                                            {"Unit", std::move(unit)},
                                                                            {"ReferenceDomainId", std::move(referenceDomainId)},
                                                                            {"ReferenceDomainOffset", std::move(referenceDomainOffset)}}))
{
}

ErrCode DeviceDomainImpl::getTickResolution(IRatio** tickResolution)
{
    OPENDAQ_PARAM_NOT_NULL(tickResolution);

    *tickResolution = this->fields.get("TickResolution").asPtr<IRatio>().addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DeviceDomainImpl::getOrigin(IString** origin)
{
    OPENDAQ_PARAM_NOT_NULL(origin);

    *origin = this->fields.get("Origin").asPtr<IString>().addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DeviceDomainImpl::getUnit(IUnit** unit)
{
    OPENDAQ_PARAM_NOT_NULL(unit);

    *unit = this->fields.get("Unit").asPtr<IUnit>().addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DeviceDomainImpl::getReferenceDomainId(IString** referenceDomainId)
{
    OPENDAQ_PARAM_NOT_NULL(referenceDomainId);

    auto ptr = this->fields.get("ReferenceDomainId");
    if (ptr.assigned())
        *referenceDomainId = ptr.asPtr<IString>().addRefAndReturn();

    return OPENDAQ_SUCCESS;
}

ErrCode DeviceDomainImpl::getReferenceDomainOffset(IInteger** referenceDomainOffset)
{
    OPENDAQ_PARAM_NOT_NULL(referenceDomainOffset);

    auto ptr = this->fields.get("ReferenceDomainOffset");
    if (ptr.assigned())
        *referenceDomainOffset = ptr.asPtr<IInteger>().addRefAndReturn();

    return OPENDAQ_SUCCESS;
}

ErrCode DeviceDomainImpl::serialize(ISerializer* serializer)
{
    OPENDAQ_PARAM_NOT_NULL(serializer);

    serializer->startTaggedObject(this);
    {
        const RatioPtr resolution = this->fields.get("TickResolution");
        if (resolution.assigned())
        {
            serializer->key("tickResolution");
            resolution.serialize(serializer);
        }
        
        const StringPtr origin = this->fields.get("Origin");
        if (origin.assigned() && origin != "")
        {
            serializer->key("origin");
            serializer->writeString(origin.getCharPtr(), origin.getLength());
        }
        
        const UnitPtr unit = this->fields.get("Unit");
        if (unit.assigned())
        {
            serializer->key("unit");
            unit.serialize(serializer);
        }

        const StringPtr referenceDomainId = this->fields.get("ReferenceDomainId");
        if (referenceDomainId.assigned()) // TODO: maybe check for empty string?
        {
            serializer->key("referenceDomainId");
            serializer->writeString(referenceDomainId.getCharPtr(), referenceDomainId.getLength());
        }

        const IntegerPtr referenceDomainOffset = this->fields.get("ReferenceDomainOffset");
        if (referenceDomainOffset.assigned())
        {
            serializer->key("referenceDomainOffset");
            serializer->writeInt(referenceDomainOffset);
        }
    }

    serializer->endObject();
    return OPENDAQ_SUCCESS;
}

ErrCode DeviceDomainImpl::getSerializeId(ConstCharPtr* id) const
{
    OPENDAQ_PARAM_NOT_NULL(id);

    *id = SerializeId();
    return OPENDAQ_SUCCESS;
}

ConstCharPtr DeviceDomainImpl::SerializeId()
{
    return "DeviceDomain";
}

ErrCode DeviceDomainImpl::Deserialize(ISerializedObject* serialized, IBaseObject*, IFunction*, IBaseObject** obj)
{
    OPENDAQ_PARAM_NOT_NULL(serialized);
    OPENDAQ_PARAM_NOT_NULL(obj);
    SerializedObjectPtr serializedObj = SerializedObjectPtr::Borrow(serialized);

    RatioPtr resolution;
    StringPtr origin;
    UnitPtr unit;
    StringPtr referenceDomainId;
    IntegerPtr referenceDomainOffset;
    
    if (serializedObj.hasKey("tickResolution"))
    {
        resolution = serializedObj.readObject("tickResolution");
    }
    
    if (serializedObj.hasKey("origin"))
    {
        origin = serializedObj.readString("origin");
    }

    if (serializedObj.hasKey("unit"))
    {
        unit = serializedObj.readObject("unit");
    }

    if (serializedObj.hasKey("referenceDomainId"))
    {
        referenceDomainId = serializedObj.readString("referenceDomainId");
    }

    if (serializedObj.hasKey("referenceDomainOffset"))
    {
        referenceDomainOffset = serializedObj.readInt("referenceDomainOffset");
    }

    *obj = DeviceDomain(resolution, origin, unit, referenceDomainId, referenceDomainOffset).as<IBaseObject>();
    return OPENDAQ_SUCCESS;
}

OPENDAQ_DEFINE_CLASS_FACTORY(LIBRARY_FACTORY, DeviceDomain,
    IRatio*, tickResolution,
    IString*, origin,
    IUnit*, unit,
    IString*, referenceDomainId,
    IInteger*, referenceDomainOffset
)

END_NAMESPACE_OPENDAQ
