#include <coreobjects/eval_value_factory.h>
#include <my_module/dispatch.h>
#include <my_module/my_filter_impl.h>
#include <opendaq/custom_log.h>
#include <opendaq/data_descriptor_ptr.h>
#include <opendaq/event_packet_params.h>
#include <opendaq/event_packet_ptr.h>
#include <opendaq/input_port_factory.h>
#include <opendaq/signal_factory.h>
#include <iostream>
#include "coreobjects/unit_factory.h"
#include "opendaq/data_packet.h"
#include "opendaq/data_packet_ptr.h"
#include "opendaq/event_packet_ids.h"
#include "opendaq/packet_factory.h"
#include "opendaq/range_factory.h"
#include "opendaq/sample_type_traits.h"

BEGIN_NAMESPACE_MY_MODULE

namespace My
{

    MyFilterImpl::MyFilterImpl(const ContextPtr& ctx, const ComponentPtr& parent, const StringPtr& localId)
        : FunctionBlock(CreateType(), ctx, parent, localId)
        , butterworth(FILTER_ORDER, CUTOFF_FREQUENCY, SAMPLING_FREQUENCY)
    {
        createInputPorts();
        createSignals();
        initProperties();
    }

    void MyFilterImpl::initProperties()
    {
        const auto filterOrder = IntProperty("FilterOrder", FILTER_ORDER);
        objPtr.addProperty(filterOrder);
        objPtr.getOnPropertyValueWrite("FilterOrder") += [this](PropertyObjectPtr& obj, PropertyValueEventArgsPtr& args)
        {
            propertyChanged(true);
            butterworthPropertyChanged();
        };

        const auto cutoffFrequncy = IntProperty("CutoffFrequency", CUTOFF_FREQUENCY);
        objPtr.addProperty(cutoffFrequncy);
        objPtr.getOnPropertyValueWrite("CutoffFrequency") += [this](PropertyObjectPtr& obj, PropertyValueEventArgsPtr& args)
        {
            propertyChanged(true);
            butterworthPropertyChanged();
        };

        const auto samplingFreqency = IntProperty("SamplingFreqency", SAMPLING_FREQUENCY);
        objPtr.addProperty(samplingFreqency);
        objPtr.getOnPropertyValueWrite("SamplingFreqency") += [this](PropertyObjectPtr& obj, PropertyValueEventArgsPtr& args)
        {
            propertyChanged(true);
            butterworthPropertyChanged();
        };

        const auto outputNameProp = StringProperty("OutputName", "");
        objPtr.addProperty(outputNameProp);
        objPtr.getOnPropertyValueWrite("OutputName") +=
            [this](PropertyObjectPtr& obj, PropertyValueEventArgsPtr& args) { propertyChanged(true); };

        const auto outputUnitProp = StringProperty("OutputUnit", "");
        objPtr.addProperty(outputUnitProp);
        objPtr.getOnPropertyValueWrite("OutputUnit") +=
            [this](PropertyObjectPtr& obj, PropertyValueEventArgsPtr& args) { propertyChanged(true); };

        readProperties();
    }

    void MyFilterImpl::butterworthPropertyChanged()
    {
        std::scoped_lock lock(sync);  // BUTTERWORTH LOCK???
        butterworth = Butterworth(order, cutoff, fs);
    }

    void MyFilterImpl::propertyChanged(bool configure)
    {
        std::scoped_lock lock(sync);
        readProperties();
        if (configure)
            this->configure();
    }

    void MyFilterImpl::readProperties()
    {
        order = objPtr.getPropertyValue("FilterOrder");
        cutoff = objPtr.getPropertyValue("CutoffFrequency");
        fs = objPtr.getPropertyValue("SamplingFreqency");
        outputUnit = static_cast<std::string>(objPtr.getPropertyValue("OutputUnit"));
        outputName = static_cast<std::string>(objPtr.getPropertyValue("OutputName"));
    }

    FunctionBlockTypePtr MyFilterImpl::CreateType()
    {
        return FunctionBlockType("my_filter", "My Filter (Butterworth)", "My signal filter (Butterworth)");
    }

    void MyFilterImpl::processSignalDescriptorChanged(const DataDescriptorPtr& inputDataDescriptor,
                                                      const DataDescriptorPtr& inputDomainDataDescriptor)
    {
        if (inputDataDescriptor.assigned())
            this->inputDataDescriptor = inputDataDescriptor;
        if (inputDomainDataDescriptor.assigned())
            this->inputDomainDataDescriptor = inputDomainDataDescriptor;

        configure();
    }

    void MyFilterImpl::configure()
    {
        if (!inputDataDescriptor.assigned() || !inputDomainDataDescriptor.assigned())
        {
            LOG_D("Incomplete signal descriptors")
            return;
        }

        try
        {
            if (inputDataDescriptor.getDimensions().getCount() > 0)
                throw std::runtime_error("Arrays not supported");

            inputSampleType = inputDataDescriptor.getSampleType();
            if (inputSampleType != SampleType::Float64 && inputSampleType != SampleType::Float32 && inputSampleType != SampleType::Int8 &&
                inputSampleType != SampleType::Int16 && inputSampleType != SampleType::Int32 && inputSampleType != SampleType::Int64 &&
                inputSampleType != SampleType::UInt8 && inputSampleType != SampleType::UInt16 && inputSampleType != SampleType::UInt32 &&
                inputSampleType != SampleType::UInt64)
                throw std::runtime_error("Invalid sample type");

            auto outputDataDescriptorBuilder = DataDescriptorBuilder().setSampleType(SampleType::Float64);

            // Set output value range to be the same as input value range
            outputDataDescriptorBuilder.setValueRange(inputDataDescriptor.getValueRange());

            if (outputName.empty())
                outputDataDescriptorBuilder.setName(inputDataDescriptor.getName().toStdString() + "/ButterworthFiltered");
            else
                outputDataDescriptorBuilder.setName(outputName);

            if (outputUnit.empty())
                outputDataDescriptorBuilder.setUnit(inputDataDescriptor.getUnit());
            else
                outputDataDescriptorBuilder.setUnit(Unit(outputUnit));
            outputDataDescriptor = outputDataDescriptorBuilder.build();
            outputSignal.setDescriptor(outputDataDescriptor);
            outputDomainSignal.setDescriptor(inputDomainDataDescriptor);
        }
        catch (const std::exception& e)
        {
            LOG_W("Failed to set descriptor for power signal: {}", e.what())
            outputSignal.setDescriptor(nullptr);
        }
    }

    void MyFilterImpl::onPacketReceived(const InputPortPtr& port)
    {
        std::scoped_lock lock(sync);

        PacketPtr packet;
        const auto connection = inputPort.getConnection();
        if (!connection.assigned())
            return;

        packet = connection.dequeue();

        while (packet.assigned())
        {
            switch (packet.getType())
            {
                case PacketType::Event:
                    processEventPacket(packet);
                    break;

                case PacketType::Data:
                    SAMPLE_TYPE_DISPATCH(inputSampleType, processDataPacket, packet);
                    break;

                default:
                    break;
            }

            packet = connection.dequeue();
        };
    }

    void MyFilterImpl::processEventPacket(const EventPacketPtr& packet)
    {
        if (packet.getEventId() == event_packet_id::DATA_DESCRIPTOR_CHANGED)
        {
            DataDescriptorPtr inputDataDescriptor = packet.getParameters().get(event_packet_param::DATA_DESCRIPTOR);
            DataDescriptorPtr inputDomainDataDescriptor = packet.getParameters().get(event_packet_param::DOMAIN_DATA_DESCRIPTOR);
            processSignalDescriptorChanged(inputDataDescriptor, inputDomainDataDescriptor);
        }
    }

    template <SampleType InputSampleType>
    void MyFilterImpl::processDataPacket(const DataPacketPtr& packet)
    {
        using InputType = typename SampleTypeToType<InputSampleType>::Type;
        auto inputData = static_cast<InputType*>(packet.getData());
        const size_t sampleCount = packet.getSampleCount();

        // std::cout << "SAMPLE COUNT: " << sampleCount << std::endl;

        const auto outputPacket = DataPacketWithDomain(packet.getDomainPacket(), outputDataDescriptor, sampleCount);
        auto outputData = static_cast<Float*>(outputPacket.getData());

        // To vector
        std::vector<double> inputDataVector;
        for (size_t i = 0; i < sampleCount; i++)
            inputDataVector.push_back(static_cast<double>(*inputData++));

        // Apply Butterworth filter
        std::vector<double> outputDataVector = butterworth.filter(inputDataVector);

        // From vector
        for (size_t i = 0; i < sampleCount; i++)
            *outputData++ = outputDataVector[i];

        outputSignal.sendPacket(outputPacket);
        outputDomainSignal.sendPacket(packet.getDomainPacket());
    }

    void MyFilterImpl::createInputPorts()
    {
        inputPort = createAndAddInputPort("input", PacketReadyNotification::Scheduler);
    }

    void MyFilterImpl::createSignals()
    {
        outputSignal = createAndAddSignal(String("output"));
        outputDomainSignal = createAndAddSignal(String("output_domain"));
        outputSignal.setDomainSignal(outputDomainSignal);
    }

}

END_NAMESPACE_MY_MODULE
