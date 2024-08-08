#include <coretypes/common.h>
#include <opendaq/context_factory.h>
#include <opendaq/instance_factory.h>
#include <opendaq/module_ptr.h>
#include <opendaq/packet_factory.h>
#include <opendaq/reader_factory.h>
#include <opendaq/scheduler_factory.h>
#include <opendaq/search_filter_factory.h>
#include <opendaq/signal_factory.h>
#include <ref_fb_module/module_dll.h>
#include <ref_fb_module/version.h>
#include <testutils/testutils.h>
#include <thread>
#include "testutils/memcheck_listener.h"

using RefFbModuleTest = testing::Test;
using namespace daq;

static ModulePtr CreateModule()
{
    ModulePtr module;
    auto logger = Logger();
    createModule(&module, Context(Scheduler(logger), logger, nullptr, nullptr, nullptr));
    return module;
}

TEST_F(RefFbModuleTest, CreateModule)
{
    IModule* module = nullptr;
    ErrCode errCode = createModule(&module, NullContext());
    ASSERT_TRUE(OPENDAQ_SUCCEEDED(errCode));

    ASSERT_NE(module, nullptr);
    module->releaseRef();
}

TEST_F(RefFbModuleTest, ModuleName)
{
    auto module = CreateModule();
    ASSERT_EQ(module.getName(), "ReferenceFunctionBlockModule");
}

TEST_F(RefFbModuleTest, VersionAvailable)
{
    auto module = CreateModule();
    ASSERT_TRUE(module.getVersionInfo().assigned());
}

TEST_F(RefFbModuleTest, VersionCorrect)
{
    auto module = CreateModule();
    auto version = module.getVersionInfo();

    ASSERT_EQ(version.getMajor(), REF_FB_MODULE_MAJOR_VERSION);
    ASSERT_EQ(version.getMinor(), REF_FB_MODULE_MINOR_VERSION);
    ASSERT_EQ(version.getPatch(), REF_FB_MODULE_PATCH_VERSION);
}

TEST_F(RefFbModuleTest, EnumerateDevices)
{
    auto module = CreateModule();

    ListPtr<IDeviceInfo> deviceInfoDict;
    ASSERT_NO_THROW(deviceInfoDict = module.getAvailableDevices());
    ASSERT_EQ(deviceInfoDict.getCount(), 0u);
}

TEST_F(RefFbModuleTest, GetAvailableComponentTypes)
{
    const auto module = CreateModule();

    DictPtr<IString, IDeviceType> deviceTypes;
    ASSERT_NO_THROW(deviceTypes = module.getAvailableDeviceTypes());
    ASSERT_EQ(deviceTypes.getCount(), 0u);

    DictPtr<IString, IServerType> serverTypes;
    ASSERT_NO_THROW(serverTypes = module.getAvailableServerTypes());
    ASSERT_EQ(serverTypes.getCount(), 0u);

    DictPtr<IString, IFunctionBlockType> functionBlockTypes;
    ASSERT_NO_THROW(functionBlockTypes = module.getAvailableFunctionBlockTypes());
    ASSERT_TRUE(functionBlockTypes.assigned());
    ASSERT_EQ(functionBlockTypes.getCount(), 8u);

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModuleRenderer"));
    ASSERT_EQ("RefFBModuleRenderer", functionBlockTypes.get("RefFBModuleRenderer").getId());

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModuleStatistics"));
    ASSERT_EQ("RefFBModuleStatistics", functionBlockTypes.get("RefFBModuleStatistics").getId());

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModulePower"));
    ASSERT_EQ("RefFBModulePower", functionBlockTypes.get("RefFBModulePower").getId());

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModulePowerReader"));
    ASSERT_EQ("RefFBModulePowerReader", functionBlockTypes.get("RefFBModulePowerReader").getId());

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModuleScaling"));
    ASSERT_EQ("RefFBModuleScaling", functionBlockTypes.get("RefFBModuleScaling").getId());

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModuleClassifier"));
    ASSERT_EQ("RefFBModuleClassifier", functionBlockTypes.get("RefFBModuleClassifier").getId());

    ASSERT_TRUE(functionBlockTypes.hasKey("RefFBModuleTrigger"));
    ASSERT_EQ("RefFBModuleTrigger", functionBlockTypes.get("RefFBModuleTrigger").getId());
}

TEST_F(RefFbModuleTest, CreateFunctionBlockNotFound)
{
    const auto module = CreateModule();

    ASSERT_THROW(module.createFunctionBlock("test", nullptr, "Id"), NotFoundException);
}

TEST_F(RefFbModuleTest, DISABLED_CreateFunctionBlockRenderer)
{
    MemCheckListener::expectMemoryLeak = true;

    const auto module = CreateModule();

    auto fb = module.createFunctionBlock("RefFBModuleRenderer", nullptr, "Id");
    ASSERT_TRUE(fb.assigned());

    // std::this_thread::sleep_for(std::chrono::milliseconds(10000));
}

TEST_F(RefFbModuleTest, CreateFunctionBlockStatistics)
{
    const auto module = CreateModule();

    auto fb = module.createFunctionBlock("RefFBModuleStatistics", nullptr, "Id");
    ASSERT_TRUE(fb.assigned());
}

TEST_F(RefFbModuleTest, StatisticsNumOfSignals)
{
    auto module = CreateModule();

    auto fb = module.createFunctionBlock("RefFBModuleStatistics", nullptr, "Id");
    ASSERT_EQ(fb.getSignals(search::Recursive(search::Any())).getCount(), 3u);
}

TEST_F(RefFbModuleTest, CreateFunctionBlockClassifier)
{
    const auto module = CreateModule();

    auto fb = module.createFunctionBlock("RefFBModuleClassifier", nullptr, "Id");
    ASSERT_TRUE(fb.assigned());
}

TEST_F(RefFbModuleTest, CreateFunctionBlockTrigger)
{
    const auto module = CreateModule();

    auto fb = module.createFunctionBlock("RefFBModuleTrigger", nullptr, "Id");
    ASSERT_TRUE(fb.assigned());
}

TEST_F(RefFbModuleTest, AddFunctionBlockBackwardsCompat)
{
    const auto instance = Instance();

    instance.addFunctionBlock("ref_fb_module_classifier");
    instance.addFunctionBlock("ref_fb_module_fft");
    instance.addFunctionBlock("ref_fb_module_power");
    // instance.addFunctionBlock("ref_fb_module_renderer");
    instance.addFunctionBlock("ref_fb_module_scaling");
    instance.addFunctionBlock("ref_fb_module_statistics");
    instance.addFunctionBlock("ref_fb_module_trigger");
    instance.addFunctionBlock("audio_device_module_wav_writer");
}

TEST_F(RefFbModuleTest, TriggerWithReferenceDomainOffset)
{
    // Create domain signal
    auto logger = Logger();
    auto context = Context(Scheduler(logger), logger, nullptr, nullptr, nullptr);
    auto domainSignalDescriptor = DataDescriptorBuilder()
                                      .setUnit(Unit("s", -1, "seconds", "Time"))
                                      .setSampleType(SampleType::Int64)
                                      .setRule(LinearDataRule(5, 3))
                                      .setOrigin("1970")
                                      .setTickResolution(Ratio(1, 1000))
                                      .setReferenceDomainOffset(100)
                                      .build();
    auto domainSignal = SignalWithDescriptor(context, domainSignalDescriptor, nullptr, "DomainSignal");
    const auto sampleCount = 5;
    auto domainPacket = DataPacket(domainSignalDescriptor, sampleCount, 1);
    // Create signal with descriptor
    auto signalDescriptor =
        DataDescriptorBuilder().setSampleType(SampleType::Float64).setValueRange(Range(0, 300)).setRule(ExplicitDataRule()).build();
    auto signal = SignalWithDescriptor(context, signalDescriptor, nullptr, "Signal");
    // Set domain signal of signal
    signal.setDomainSignal(domainSignal);

    // Create module
    ModulePtr module;
    createModule(&module, context);

    // Fix for race condition
    auto config = module.getAvailableFunctionBlockTypes().get("RefFBModuleTrigger").createDefaultConfig();
    config.setPropertyValue("UseMultiThreadedScheduler", false);

    // Create function block
    auto fb = module.createFunctionBlock("RefFBModuleTrigger", nullptr, "FB", config);

    // Set input (port) and output (signal) of the function block
    fb.getInputPorts()[0].connect(signal);
    auto reader = PacketReader(fb.getSignals()[0]);

    // Create data packet
    auto dataPacket = DataPacketWithDomain(domainPacket, signalDescriptor, sampleCount);
    auto packetData = static_cast<double*>(dataPacket.getRawData());
    for (size_t i = 0; i < sampleCount; i++)
        *packetData++ = static_cast<double>(i);

    // Send packet
    domainSignal.sendPacket(domainPacket);
    signal.sendPacket(dataPacket);

    // Receive packet
    PacketPtr receivedPacket;
    while (true)
    {
        receivedPacket = reader.read();
        if (receivedPacket.assigned() && receivedPacket.getType() == PacketType::Data)
            break;
    }

    // Check domain data
    auto domainData = static_cast<int64_t*>(receivedPacket.asPtr<IDataPacket>().getDomainPacket().getData());

    // input data:      0, 1, 2, 3, 4
    //                     ^ trigger, becauase greater than 0.5
    // input domain:    104, 109, 114, 119, 124 (offset = 1, start = 3, reference domain offset = 100, delta = 5)
    //                        ^ expected output domain, one sample with value 109

    ASSERT_EQ(domainData[0], 109);
}
