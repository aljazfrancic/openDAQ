#include <opendaq/instance_factory.h>
#include <opendaq/module_ptr.h>
#include <opendaq/opendaq.h>
#include <ref_fb_module/module_dll.h>
#include "testutils/memcheck_listener.h"
using namespace daq;

template <typename T>
using vecvec = std::vector<std::vector<T> >;

// TODO use SetUp
class TriggerTest : public testing::Test
{
public:
    template <typename T>
    void runTriggerTest(DataRulePtr rule,
                        vecvec<daq::Bool> expectedData,
                        vecvec<daq::Int> expectedDomain,
                        vecvec<T> mockPackets,
                        vecvec<daq::Int> mockDomainPackets = {})
    {
        // Create logger, context and module
        auto logger = Logger();
        auto context = Context(Scheduler(logger), logger, nullptr, nullptr);
        ModulePtr module;
        createModule(&module, context);

        // Create domain signal with descriptor
        auto domainSignalDescriptorBuilder = DataDescriptorBuilder();
        domainSignalDescriptorBuilder.setUnit(Unit("s", -1, "seconds", "Time"));
        domainSignalDescriptorBuilder.setSampleType(SampleType::Int64);
        domainSignalDescriptorBuilder.setRule(rule);
        domainSignalDescriptorBuilder.setOrigin("1970");
        domainSignalDescriptorBuilder.setTickResolution(Ratio(1, 1000));
        auto domainSignalDescriptor = domainSignalDescriptorBuilder.build();
        auto domainSignal = SignalWithDescriptor(context, domainSignalDescriptor, nullptr, "domain signal");

        // Create domain packets
        std::vector<DataPacketPtr> domainPackets;
        for (size_t i = 0; i < mockPackets.size(); i++)
        {
            // Create one domain packet

            if (rule.getType() == DataRuleType::Explicit)
            {
                // Explicit
                auto domainPacket = DataPacket(domainSignalDescriptor, mockPackets[i].size());
                auto domainPacketData = static_cast<daq::Int*>(domainPacket.getData());
                for (size_t ii = 0; ii < mockDomainPackets[i].size(); ii++)
                    *domainPacketData++ = static_cast<daq::Int>(mockDomainPackets[i][ii]);
                domainPackets.push_back(domainPacket);
            }
            else
            {
                //  Linear
                auto offset = 0;
                for (size_t ii = 0; ii < i; ii++)
                {
                    daq::Int delta = rule.getParameters().get("delta");
                    offset = offset + mockPackets[ii].size() * delta;
                }

                auto domainPacket = DataPacket(domainSignalDescriptor, mockPackets[i].size(), offset);
                domainPackets.push_back(domainPacket);
            }
        }

        // Create signal with descriptor
        auto signalDescriptorBuilder = DataDescriptorBuilder();
        // TODO sample type
        signalDescriptorBuilder.setSampleType(SampleType::Float64);
        signalDescriptorBuilder.setValueRange(Range(0, 100));
        signalDescriptorBuilder.setRule(ExplicitDataRule());
        auto signalDescriptor = signalDescriptorBuilder.build();
        auto signal = SignalWithDescriptor(context, signalDescriptor, nullptr, "signal");

        // Set domain signal of signal
        signal.setDomainSignal(domainSignal);

        // Create function block
        auto fb = module.createFunctionBlock("ref_fb_module_trigger", nullptr, "fb");

        // Set input (port) and output (signal) of the function block
        fb.getInputPorts()[0].connect(signal);
        auto reader = PacketReader(fb.getSignals()[0]);

        // Send packets
        for (size_t i = 0; i < mockPackets.size(); i++)
        {
            // Create data packets
            auto dataPacket = DataPacketWithDomain(domainPackets[i], signalDescriptor, mockPackets[i].size());
            auto packetData = static_cast<daq::Float*>(dataPacket.getData());  // TODO type
            for (size_t ii = 0; ii < mockPackets[i].size(); ii++)
                *packetData++ = static_cast<daq::Float>(mockPackets[i][ii]);  // TODO type

            // Send
            domainSignal.sendPacket(domainPackets[i]);
            signal.sendPacket(dataPacket);
        }

        // Receive data packets
        for (size_t i = 0; i < mockPackets.size(); i++)
        {
            // Receive data packets that come from single input data packet
            std::vector<DataPacketPtr> receivedPacketVector;
            // Receive until you get all expected packets
            while (receivedPacketVector.size() < expectedData[i].size())
            {
                auto receivedPackets = reader.readAll();
                for (size_t ii = 0; ii < receivedPackets.getCount(); ii++)
                {
                    // Ignore PacketType::Event
                    if (receivedPackets[ii].getType() == PacketType::Data)
                    {
                        receivedPacketVector.push_back(receivedPackets[ii]);
                    }
                }
            }

            ASSERT_EQ(receivedPacketVector.size(), expectedData[i].size());

            // Check packet(s) contents
            for (size_t ii = 0; ii < expectedData[i].size(); ii++)
            {
                auto data = static_cast<daq::Bool*>(receivedPacketVector[ii].getData());
                const size_t sampleCount = receivedPacketVector[ii].getSampleCount();

                auto domainData = static_cast<daq::Int*>(receivedPacketVector[ii].getDomainPacket().getData());
                const size_t domainSampleCount = receivedPacketVector[ii].getDomainPacket().getSampleCount();

                // Assert that packet has one sample
                ASSERT_EQ(sampleCount, 1);
                // Assert that domain packet has one sample
                ASSERT_EQ(domainSampleCount, 1);

                // Assert that first sample equals expected value
                ASSERT_EQ(data[0], expectedData[i][ii]);
                // Assert that first domain sample equals expected value
                ASSERT_EQ(domainData[0], expectedDomain[i][ii]);
            }
        }
    }
};

// TODO multiple tests
TEST_F(TriggerTest, TriggerTest)
{
    daq::Int delta = 2;

    std::vector<daq::Float> mockData1{0.1, 0.2, 0.3, 2, 3, 4, 4.5, 0.2, 0.1, 0, 5, 6, 7};
    daq::Int start1 = 3;
    std::vector<daq::Int> mockDomainData1;
    for (size_t i = 0; i < mockData1.size(); i++)
        mockDomainData1.push_back(i * delta + start1);
    std::vector<daq::Bool> expectedData1{true, false, true};
    std::vector<daq::Int> expectedDomain1{9, 17, 23};

    std::vector<daq::Float> mockData2{6, 0.1, 0, 6, 7};
    daq::Int start2 = 29;
    std::vector<daq::Int> mockDomainData2;
    for (size_t i = 0; i < mockData2.size(); i++)
        mockDomainData2.push_back(i * delta + start2);
    std::vector<daq::Bool> expectedData2{false, true};
    std::vector<daq::Int> expectedDomain2{31, 35};

    std::vector<daq::Float> mockData3{7, 8, 0.1};
    daq::Int start3 = 39;
    std::vector<daq::Int> mockDomainData3;
    for (size_t i = 0; i < mockData3.size(); i++)
        mockDomainData3.push_back(i * delta + start3);
    std::vector<daq::Bool> expectedData3{false};
    std::vector<daq::Int> expectedDomain3{43};

    // TODO more concise + add fourth
    vecvec<daq::Float> mockPackets{mockData1, mockData2, mockData3};
    vecvec<daq::Int> mockDomainPackets{mockDomainData1, mockDomainData2, mockDomainData3};
    vecvec<daq::Bool> expectedData{expectedData1, expectedData2, expectedData3};
    vecvec<daq::Int> expectedDomain{expectedDomain1, expectedDomain2, expectedDomain3};

    // TODO multiple different types, multiple packets, thresh changed + test edge cases
    runTriggerTest(ExplicitDataRule(), expectedData, expectedDomain, mockPackets, mockDomainPackets);
    runTriggerTest(LinearDataRule(2, 3), expectedData, expectedDomain, mockPackets);
}
