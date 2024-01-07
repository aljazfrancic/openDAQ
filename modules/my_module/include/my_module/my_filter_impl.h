#pragma once
#include <my_module/butterworth.h>
#include <my_module/common.h>
#include <opendaq/function_block_impl.h>
#include <opendaq/function_block_ptr.h>
#include <opendaq/function_block_type_factory.h>
#include <opendaq/signal_config_ptr.h>
#include "opendaq/data_packet_ptr.h"
#include "opendaq/event_packet_ptr.h"

#include <vector>

constexpr auto FILTER_ORDER = 4;
constexpr auto CUTOFF_FREQUENCY = 50;
constexpr auto SAMPLING_FREQUENCY = 1000;

BEGIN_NAMESPACE_MY_MODULE

namespace My
{

    class MyFilterImpl final : public FunctionBlock
    {
    public:
        explicit MyFilterImpl(const ContextPtr& ctx, const ComponentPtr& parent, const StringPtr& localId);
        ~MyFilterImpl() override = default;

        static FunctionBlockTypePtr CreateType();

    private:
        Butterworth butterworth;

        InputPortPtr inputPort;

        DataDescriptorPtr inputDataDescriptor;
        DataDescriptorPtr inputDomainDataDescriptor;

        DataDescriptorPtr outputDataDescriptor;
        DataDescriptorPtr outputDomainDataDescriptor;

        SampleType inputSampleType;

        SignalConfigPtr outputSignal;
        SignalConfigPtr outputDomainSignal;

        Int order;
        Int cutoff;
        Int fs;
        std::string outputUnit;
        std::string outputName;

        void createInputPorts();
        void createSignals();

        template <SampleType InputSampleType>
        void processDataPacket(const DataPacketPtr& packet);

        void processEventPacket(const EventPacketPtr& packet);
        void onPacketReceived(const InputPortPtr& port) override;

        void processSignalDescriptorChanged(const DataDescriptorPtr& inputDataDescriptor,
                                            const DataDescriptorPtr& inputDomainDataDescriptor);

        void configure();

        void initProperties();
        void propertyChanged(bool configure);
        void butterworthPropertyChanged();
        void readProperties();
    };
}

END_NAMESPACE_MY_MODULE
