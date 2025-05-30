#include <coretypes/coretype_utils.h>
#include <coretypes/validation.h>
#include <opendaq/data_descriptor_builder_impl.h>
#include <opendaq/data_descriptor_builder_ptr.h>
#include <opendaq/data_descriptor_factory.h>
#include <opendaq/data_descriptor_impl.h>
#include <opendaq/data_rule_factory.h>
#include <opendaq/dimension_factory.h>
#include <opendaq/range_factory.h>
#include <opendaq/scaling_factory.h>
#include <opendaq/signal_errors.h>

BEGIN_NAMESPACE_OPENDAQ

namespace detail
{
    static const StructTypePtr dataDescriptorStructType = DataDescriptorStructType();
}

DictPtr<IString, IBaseObject> DataDescriptorImpl::PackBuilder(IDataDescriptorBuilder* dataDescriptorBuilder)
{
    const auto builderPtr = DataDescriptorBuilderPtr::Borrow(dataDescriptorBuilder);
    auto params = Dict<IString, IBaseObject>();
    params.set("Dimensions", builderPtr.getDimensions());
    params.set("Name", builderPtr.getName());
    params.set("SampleType", static_cast<Int>(builderPtr.getSampleType()));
    params.set("Unit", builderPtr.getUnit());
    params.set("ValueRange", builderPtr.getValueRange());
    params.set("DataRule", builderPtr.getRule());
    params.set("Scaling", builderPtr.getPostScaling());
    params.set("Origin", builderPtr.getOrigin());
    params.set("TickResolution", builderPtr.getTickResolution());
    params.set("StructFields", builderPtr.getStructFields());
    params.set("Metadata", builderPtr.getMetadata());
    params.set("ReferenceDomainInfo", builderPtr.getReferenceDomainInfo());

    return params;
}

DataDescriptorImpl::DataDescriptorImpl(IDataDescriptorBuilder* dataDescriptorBuilder)
    : Super(detail::dataDescriptorStructType, PackBuilder(dataDescriptorBuilder))
{
    const auto dataDescriptorBuilderPtr = DataDescriptorBuilderPtr(dataDescriptorBuilder);
    this->dimensions = dataDescriptorBuilderPtr.getDimensions();
    this->name = dataDescriptorBuilderPtr.getName();
    this->sampleType = dataDescriptorBuilderPtr.getSampleType(); 
    this->unit = dataDescriptorBuilderPtr.getUnit(); 
    this->valueRange = dataDescriptorBuilderPtr.getValueRange(); 
    this->dataRule = dataDescriptorBuilderPtr.getRule(); 
    this->scaling = dataDescriptorBuilderPtr.getPostScaling(); 
    this->origin = dataDescriptorBuilderPtr.getOrigin(); 
    this->resolution = dataDescriptorBuilderPtr.getTickResolution(); 
    this->structFields = dataDescriptorBuilderPtr.getStructFields(); 
    this->metadata = dataDescriptorBuilderPtr.getMetadata(); 
    this->scalingCalc = nullptr;
    this->dataRuleCalc = nullptr;
    this->referenceDomainInfo = dataDescriptorBuilderPtr.getReferenceDomainInfo();
    checkErrorInfo(validate());
    calculateSampleMemSize();
}

ErrCode DataDescriptorImpl::getName(IString** name)
{
    OPENDAQ_PARAM_NOT_NULL(name);

    *name = this->name.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getDimensions(IList** dimensions)
{
    OPENDAQ_PARAM_NOT_NULL(dimensions);

    *dimensions = this->dimensions.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getSampleType(SampleType* sampleType)
{
    OPENDAQ_PARAM_NOT_NULL(sampleType);

    *sampleType = this->sampleType;
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getUnit(IUnit** unit)
{
    OPENDAQ_PARAM_NOT_NULL(unit);

    *unit = this->unit.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getValueRange(IRange** valueRange)
{
    OPENDAQ_PARAM_NOT_NULL(valueRange);

    *valueRange = this->valueRange.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getRule(IDataRule** rule)
{
    OPENDAQ_PARAM_NOT_NULL(rule);

    *rule = this->dataRule.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getOrigin(IString** origin)
{
    OPENDAQ_PARAM_NOT_NULL(origin);

    *origin = this->origin.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getTickResolution(IRatio** tickResolution)
{
    OPENDAQ_PARAM_NOT_NULL(tickResolution);

    *tickResolution = this->resolution.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getPostScaling(IScaling** scaling)
{
    OPENDAQ_PARAM_NOT_NULL(scaling);

    *scaling = this->scaling.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getMetadata(IDict** metadata)
{
    OPENDAQ_PARAM_NOT_NULL(metadata);

    *metadata = this->metadata.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getStructFields(IList** structFields)
{
    OPENDAQ_PARAM_NOT_NULL(structFields);

    *structFields = this->structFields.addRefAndReturn();
    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getSampleSize(SizeT* sampleSize)
{
    OPENDAQ_PARAM_NOT_NULL(sampleSize);

    *sampleSize = this->sampleSize;

    return OPENDAQ_SUCCESS;
}

ErrCode INTERFACE_FUNC DataDescriptorImpl::getRawSampleSize(SizeT* rawSampleSize)
{
    OPENDAQ_PARAM_NOT_NULL(rawSampleSize);

    *rawSampleSize = this->rawSampleSize;

    return OPENDAQ_SUCCESS;
}

ErrCode INTERFACE_FUNC DataDescriptorImpl::getReferenceDomainInfo(IReferenceDomainInfo** referenceDomainInfo)
{
    OPENDAQ_PARAM_NOT_NULL(referenceDomainInfo);

    *referenceDomainInfo = this->referenceDomainInfo.addRefAndReturn();

    return OPENDAQ_SUCCESS;
}

void DataDescriptorImpl::calculateSampleMemSize()
{
    size_t elementCnt = 1;
    for (const auto& dimension : dimensions)
        elementCnt *= dimension.getSize();

    if (elementCnt == 0)
        elementCnt = 1;

    if (!structFields.assigned() || structFields.getCount() == 0)
    {
        sampleSize = daq::getSampleSize(sampleType);

        SampleType rawType = sampleType;
        if (scaling.assigned())
            rawType = scaling.getInputSampleType();
        rawSampleSize = daq::getSampleSize(rawType);

        sampleSize *= elementCnt;
        rawSampleSize *= elementCnt;

        if (dataRule.getType() != DataRuleType::Explicit)
            rawSampleSize = 0;
    }
    else
    {
        sampleSize = 0;
        rawSampleSize = 0;
        for (const auto& structField : structFields)
        {
            sampleSize += structField.getSampleSize();
            rawSampleSize += structField.getRawSampleSize();
        }
        sampleSize *= elementCnt;
        rawSampleSize *= elementCnt;
    }
}

ErrCode DataDescriptorImpl::validate()
{
    try
    {
        if (structFields.assigned() && structFields.getCount() != 0)
        {
            auto valid = sampleType == SampleType::Struct;
            valid = dataRule.getType() != DataRuleType::Explicit ? false : valid;
            valid = scaling.assigned() ? false : valid;
            valid = unit.assigned() ? false : valid;
            valid = valueRange.assigned() ? false : valid;
            valid = origin != "" ? false : valid;
            valid = resolution.assigned() ? false : valid;
            valid = scaling.assigned() ? false : valid;
            valid = !name.assigned() || name == "" ? false : valid;

            if (!valid)
            {
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALIDSTATE,
                                     "A Data descriptor with struct members can only have the name and dimensions configured. Its rule "
                                     "type must be explicit and Sample type set to Struct. It's name must be assigned and musn't be empty.");
            }

            structFields.freeze();
        }
        else
        {
            if (!dataRule.assigned())
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_CONFIGURATION_INCOMPLETE, "Data descriptor is missing data rule.");

            if (scaling.assigned() && sampleType != convertScaledToSampleType(scaling.getOutputSampleType()))
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALID_SAMPLE_TYPE, "Scaling output type does not match the descriptor's sample type.");

            if (scaling.assigned() && (dataRule.getType() != DataRuleType::Explicit || resolution.assigned() || origin != ""))
                return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALIDSTATE,
                                     "When using post scaling, the data rule type must be explicit, and the resolution and origin must "
                                     "not be configured.");

            if (!(dataRule.getType() == DataRuleType::Explicit || dataRule.getType() == DataRuleType::Constant ||
                  dataRule.getType() == DataRuleType::Other))
            {
                if (sampleType > SampleType::RangeInt64)
                    return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALID_SAMPLE_TYPE, "Implicit data rule types can only be real numbers.");
            }

            if (dataRule.getType() == DataRuleType::Constant)
            {
                if (referenceDomainInfo.assigned())
                    DAQ_THROW_EXCEPTION(InvalidParameterException, "Reference Domain Info not supported for constant data rule type.");
            }
            if (scaling.assigned())
            {
                if (referenceDomainInfo.assigned())
                    DAQ_THROW_EXCEPTION(InvalidParameterException, "Reference Domain Info not supported with post scaling.");
            }
                
        }

        if (dimensions.assigned())
            dimensions.freeze();

        if (metadata.assigned())
        {
            metadata.freeze();

            for (auto key : metadata.getKeys())
            {
                auto freezable = metadata.get(key).asPtrOrNull<IFreezable>();
                if (freezable.assigned())
                    freezable.freeze();
            }
        }

        initCalcs();
    }
    catch (const DaqException& e)
    {
        return errorFromException(e, this->getThisAsBaseObject());
    }
    
    return OPENDAQ_SUCCESS;
}

ErrCode INTERFACE_FUNC DataDescriptorImpl::equals(IBaseObject* other, Bool* equals) const
{
    return daqTry([this, &other, &equals]() {
        if (equals == nullptr)
            return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_ARGUMENT_NULL, "Equals out-parameter must not be null");

        *equals = false;
        if (!other)
            return OPENDAQ_SUCCESS;

        DataDescriptorPtr descriptor = BaseObjectPtr::Borrow(other).asPtrOrNull<IDataDescriptor>();
        if (descriptor == nullptr)
            return OPENDAQ_SUCCESS;

        if (name != descriptor.getName())
            return OPENDAQ_SUCCESS;

        if (!BaseObjectPtr::Equals(dimensions, descriptor.getDimensions()))
            return OPENDAQ_SUCCESS;

        if (sampleType != descriptor.getSampleType())
            return OPENDAQ_SUCCESS;
        if (!BaseObjectPtr::Equals(unit, descriptor.getUnit()))
            return OPENDAQ_SUCCESS;
        if (!BaseObjectPtr::Equals(valueRange, descriptor.getValueRange()))
            return OPENDAQ_SUCCESS;
        if (!BaseObjectPtr::Equals(dataRule, descriptor.getRule()))
            return OPENDAQ_SUCCESS;
        if (origin != descriptor.getOrigin())
            return OPENDAQ_SUCCESS;
        if (!BaseObjectPtr::Equals(resolution, descriptor.getTickResolution()))
            return OPENDAQ_SUCCESS;
        if (!BaseObjectPtr::Equals(scaling, descriptor.getPostScaling()))
            return OPENDAQ_SUCCESS;

        if (!BaseObjectPtr::Equals(structFields, descriptor.getStructFields()))
            return OPENDAQ_SUCCESS;
        if (!BaseObjectPtr::Equals(metadata, descriptor.getMetadata()))
            return OPENDAQ_SUCCESS;

        if (!BaseObjectPtr::Equals(referenceDomainInfo, descriptor.getReferenceDomainInfo()))
            return OPENDAQ_SUCCESS;

        *equals = true;
        return OPENDAQ_SUCCESS;
    });
}

// IScalingCalcPrivate
void* DataDescriptorImpl::scaleData(void* data, SizeT sampleCount) const
{
    if (scalingCalc)
        return scalingCalc->scaleData(data, sampleCount);

    return nullptr;
}

void DataDescriptorImpl::scaleData(void* data, SizeT sampleCount, void** output) const
{
    if (scalingCalc)
        scalingCalc->scaleData(data, sampleCount, output);
}

Bool DataDescriptorImpl::hasScalingCalc() const
{
    return (scalingCalc != nullptr) ? True : False;
}

// IDataRuleCalcPrivate
void* DataDescriptorImpl::calculateRule(const NumberPtr& packetOffset, SizeT sampleCount, void* input, SizeT inputSize) const
{
    if (dataRuleCalc)
        return dataRuleCalc->calculateRule(packetOffset, sampleCount, input, inputSize);

    return nullptr;
}

void DataDescriptorImpl::calculateRule(const NumberPtr& packetOffset, SizeT sampleCount, void* input, SizeT inputSize, void** output) const
{
    if (dataRuleCalc)
        dataRuleCalc->calculateRule(packetOffset, sampleCount, input, inputSize, output);
}

void* DataDescriptorImpl::calculateSample(const NumberPtr& packetOffset, SizeT sampleIndex, void* input, SizeT inputSize) const
{
    if (dataRuleCalc)
        return dataRuleCalc->calculateSample(packetOffset, sampleIndex, input, inputSize);

    return nullptr;
}

void DataDescriptorImpl::calculateSample(
    const NumberPtr& packetOffset, SizeT sampleIndex, void* input, SizeT inputSize, void** output) const
{
    if (dataRuleCalc)
        dataRuleCalc->calculateSample(packetOffset, sampleIndex, input, inputSize, output);
}

void DataDescriptorImpl::calculateLastSample(const NumberPtr& packetOffset, SizeT sampleCount, void* input, SizeT inputSize, void** output) const
{
    if (dataRuleCalc)
        dataRuleCalc->calculateLastSample(packetOffset, sampleCount, input, inputSize, output);
}

Bool DataDescriptorImpl::hasDataRuleCalc() const
{
    return (dataRuleCalc != nullptr) ? True : False;
}

void DataDescriptorImpl::initCalcs()
{
    if (structFields.assigned() && structFields.getCount() != 0)
        return;

    if (dataRule.assigned() && (dataRule.getType() == DataRuleType::Constant || dataRule.getType() == DataRuleType::Linear))
        dataRuleCalc = std::unique_ptr<DataRuleCalc>(createDataRuleCalcTyped(dataRule, sampleType));

    if (scaling.assigned())
        scalingCalc = std::unique_ptr<ScalingCalc>(createScalingCalcTyped(scaling));
}

ErrCode DataDescriptorImpl::serialize(ISerializer* serializer)
{
    OPENDAQ_PARAM_NOT_NULL(serializer);

    serializer->startTaggedObject(this);
    {
        serializer->key("name");
        serializer->writeString(name.getCharPtr(), name.getLength());

        serializer->key("sampleType");
        serializer->writeInt(static_cast<Int>(sampleType));

        if (unit.assigned())
        {
            serializer->key("unit");
            unit.serialize(serializer);
        }

        serializer->key("dimensions");
        dimensions.serialize(serializer);

        if (valueRange.assigned())
        {
            serializer->key("valueRange");
            valueRange.serialize(serializer);
        }

        serializer->key("rule");
        dataRule.serialize(serializer);

        if (scaling.assigned())
        {
            serializer->key("postScaling");
            scaling.serialize(serializer);
        }

        serializer->key("origin");
        serializer->writeString(origin.getCharPtr(), origin.getLength());

        if (resolution.assigned())
        {
            serializer->key("tickResolution");
            resolution.serialize(serializer);
        }

        serializer->key("metadata");
        metadata.serialize(serializer);

        serializer->key("structFields");
        structFields.serialize(serializer);

        if (referenceDomainInfo.assigned())
        {
            serializer->key("referenceDomainInfo");
            referenceDomainInfo.serialize(serializer);
        }
    }
    serializer->endObject();

    return OPENDAQ_SUCCESS;
}

ErrCode DataDescriptorImpl::getSerializeId(ConstCharPtr* id) const
{
    OPENDAQ_PARAM_NOT_NULL(id);

    *id = SerializeId();

    return OPENDAQ_SUCCESS;
}

ConstCharPtr DataDescriptorImpl::SerializeId()
{
    return "DataDescriptor";
}

ErrCode DataDescriptorImpl::Deserialize(ISerializedObject* serialized, IBaseObject*, IFunction*, IBaseObject** obj)
{
    OPENDAQ_PARAM_NOT_NULL(serialized);
    OPENDAQ_PARAM_NOT_NULL(obj);

    DataDescriptorBuilderPtr dataDescriptor;
    auto errCode = createObject<IDataDescriptorBuilder, DataDescriptorBuilderImpl>(&dataDescriptor);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    SerializedObjectPtr serializedObj = SerializedObjectPtr::Borrow(serialized);

    auto name = serializedObj.readString("name");
    dataDescriptor.setName(name);

    auto sampleType = static_cast<SampleType>(serializedObj.readInt("sampleType"));
    dataDescriptor.setSampleType(sampleType);

    if (serializedObj.hasKey("unit"))
    {
        UnitPtr unit = serializedObj.readObject("unit");
        dataDescriptor.setUnit(unit);
    }

    ListPtr<IDimension> dimensions = serializedObj.readObject("dimensions");
    dataDescriptor.setDimensions(dimensions);

    if (serializedObj.hasKey("valueRange"))
    {
        RangePtr valueRange = serializedObj.readObject("valueRange");
        dataDescriptor.setValueRange(valueRange);
    }

    DataRulePtr rule = serializedObj.readObject("rule");
    dataDescriptor.setRule(rule);

    if (serializedObj.hasKey("postScaling"))
    {
        ScalingPtr postScaling = serializedObj.readObject("postScaling");
        dataDescriptor.setPostScaling(postScaling);
    }

    auto origin = serializedObj.readString("origin");
    dataDescriptor.setOrigin(origin);

    if (serializedObj.hasKey("tickResolution"))
    {
        RatioPtr tick_resolution = serializedObj.readObject("tickResolution");
        dataDescriptor.setTickResolution(tick_resolution);
    }

    DictPtr<IString, IString> metadata = serializedObj.readObject("metadata");
    dataDescriptor.setMetadata(metadata);

    ListPtr<IDataDescriptor> structFields = serializedObj.readObject("structFields");
    dataDescriptor.setStructFields(structFields);

    if (serializedObj.hasKey("referenceDomainInfo"))
    {
        auto referenceDomainInfo = serializedObj.readObject("referenceDomainInfo");
        dataDescriptor.setReferenceDomainInfo(referenceDomainInfo);
    }

    *obj = dataDescriptor.build().as<IBaseObject>();

    return OPENDAQ_SUCCESS;
}

OPENDAQ_DEFINE_CLASS_FACTORY_WITH_INTERFACE_AND_CREATEFUNC(
    LIBRARY_FACTORY, DataDescriptor,
    IDataDescriptor, createDataDescriptorFromBuilder,
    IDataDescriptorBuilder*, builder
)

END_NAMESPACE_OPENDAQ
