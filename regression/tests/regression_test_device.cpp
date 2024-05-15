#include <gtest/gtest.h>
#include "get_protocol.h"

using namespace daq;

class RegressionTestDevice : public testing::Test
{
private:
    ModuleManagerPtr moduleManager;
    ContextPtr context;
    InstancePtr instance;

protected:
    DevicePtr device;

    void SetUp() override
    {
        moduleManager = ModuleManager("");
        context = Context(nullptr, Logger(), TypeManager(), moduleManager);
        instance = InstanceCustom(context, "mock_instance");

        device = instance.addDevice(connectionString);
    }
};

TEST_F(RegressionTestDevice, getInfo)
{
    DeviceInfoPtr info;
    ASSERT_NO_THROW(info = device.getInfo());
    ASSERT_TRUE(info.assigned());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_EQ(info.getName(), "Device 1");
        ASSERT_EQ(info.getModel(), "Reference Device");
        ASSERT_EQ(info.getSerialNumber(), "dev_ser_1");
    }
    else if (connectionString == "daq.ns://127.0.0.1")
    {
        ASSERT_EQ(info.getName(), "NativeStreamingClientPseudoDevice");
    }
    else if (connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_EQ(info.getName(), "WebsocketClientPseudoDevice");
    }
}

TEST_F(RegressionTestDevice, getDomain)
{
    if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        return;
    }

    DeviceDomainPtr domain;
    ASSERT_NO_THROW(domain = device.getDomain());
    ASSERT_EQ(domain.getTickResolution().getNumerator(), 1);
    ASSERT_EQ(domain.getTickResolution().getDenominator(), 1000000);
    ASSERT_EQ(domain.getOrigin(), "1970-01-01T00:00:00Z");

    if (connectionString == "daq.opcua://127.0.0.1")
    {
        ASSERT_EQ(domain.getUnit(), Unit("", -1, "", ""));
    }
    else if (connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_EQ(domain.getUnit(), Unit("s", -1, "second", "time"));
    }
}

TEST_F(RegressionTestDevice, getInputsOutputsFolder)
{
    FolderPtr folder;
    ASSERT_NO_THROW(folder = device.getInputsOutputsFolder());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_EQ(folder.getItems().getCount(), 2);
    }
    else if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_EQ(folder.getItems().getCount(), 0);
    }
}

TEST_F(RegressionTestDevice, getCustomComponents)
{
    ListPtr<IComponent> components;
    ASSERT_NO_THROW(components = device.getCustomComponents());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_GT(components.getCount(), 0);
    }
    else if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_EQ(components.getCount(), 0);
    }
}

TEST_F(RegressionTestDevice, getSignals)
{
    ListPtr<ISignal> signals;
    ASSERT_NO_THROW(signals = device.getSignals());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_EQ(signals.getCount(), 0);
    }
    else if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_GT(signals.getCount(), 0);
    }
}

TEST_F(RegressionTestDevice, getSignalsRecursive)
{
    ListPtr<ISignal> signals;
    ASSERT_NO_THROW(signals = device.getSignalsRecursive());
    ASSERT_GT(signals.getCount(), 0);
}

TEST_F(RegressionTestDevice, getChannels)
{
    ListPtr<IChannel> channels;
    ASSERT_NO_THROW(channels = device.getChannels());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_GT(channels.getCount(), 0);
    }
    else if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_EQ(channels.getCount(), 0);
    }
}

TEST_F(RegressionTestDevice, getChannelsRecursive)
{
    ListPtr<IChannel> channels;
    ASSERT_NO_THROW(channels = device.getChannelsRecursive());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_GT(channels.getCount(), 0);
    }
    else if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_EQ(channels.getCount(), 0);
    }
}

TEST_F(RegressionTestDevice, getDevices)
{
    ListPtr<IDevice> devices;
    ASSERT_NO_THROW(devices = device.getDevices());
    ASSERT_EQ(devices.getCount(), 0);
}

TEST_F(RegressionTestDevice, getAvailableDevices)
{
    ListPtr<IDeviceInfo> infos;
    ASSERT_NO_THROW(infos = device.getAvailableDevices());
    ASSERT_EQ(infos.getCount(), 0);
}

TEST_F(RegressionTestDevice, getAvailableDeviceTypes)
{
    DictPtr<IString, IDeviceType> types;
    ASSERT_NO_THROW(types = device.getAvailableDeviceTypes());
    ASSERT_EQ(types.getCount(), 0);
}

TEST_F(RegressionTestDevice, getFunctionBlocks)
{
    ListPtr<IFunctionBlock> functionBlocks;
    ASSERT_NO_THROW(functionBlocks = device.getFunctionBlocks());
    ASSERT_EQ(functionBlocks.getCount(), 0);
}

TEST_F(RegressionTestDevice, getAvailableFunctionBlockTypes)
{
    DictPtr<IString, IFunctionBlockType> types;
    ASSERT_NO_THROW(types = device.getAvailableFunctionBlockTypes());
    if (connectionString == "daq.opcua://127.0.0.1" || connectionString == "daq.nd://127.0.0.1")
    {
        ASSERT_GT(types.getCount(), 0);
    }
    else if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        ASSERT_EQ(types.getCount(), 0);
    }
}

TEST_F(RegressionTestDevice, addFunctionBlockRemoveFunctionBlock)
{
    if (connectionString == "daq.ns://127.0.0.1" || connectionString == "daq.lt://127.0.0.1")
    {
        return;
    }
    // TODO: should not rely on "ref_fb_module_trigger" being present
    FunctionBlockPtr fb;
    ASSERT_NO_THROW(fb = device.addFunctionBlock("ref_fb_module_trigger"));
    ASSERT_NO_THROW(device.removeFunctionBlock(fb));
}

TEST_F(RegressionTestDevice, saveConfigurationLoadConfiguration)
{
    StringPtr config;
    ASSERT_NO_THROW(config = device.saveConfiguration());
    ASSERT_NO_THROW(device.loadConfiguration(config));
}

TEST_F(RegressionTestDevice, getTicksSinceOrigin)
{
    ASSERT_NO_THROW(device.getTicksSinceOrigin());
}