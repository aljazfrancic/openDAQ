/**
 * Part of the openDAQ stand-alone application quick start guide. The full
 * example can be found in app_quick_start_full.cpp
 */

#include <opendaq/opendaq.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace daq;

void parallelConnect(DictObjectPtr<IDict, IString, IPropertyObject> connectionArgs, InstancePtr instance = nullptr)
{
    InstancePtr client;
    if (instance.assigned())
        client = instance;
    else
        client = Instance();

    auto errCodes = Dict<IString, IInteger>();
    auto errorInfos = Dict<IString, IErrorInfo>();

    auto devices = client.addDevices(connectionArgs, errCodes, errorInfos);
}

void sequetialConnect(DictObjectPtr<IDict, IString, IPropertyObject> connectionArgs, InstancePtr instance = nullptr)
{
    InstancePtr client;
    if (instance.assigned())
        client = instance;
    else
        client = Instance();

    for (const auto& [connectionString, config] : connectionArgs)
    {
        auto device = client.addDevice(connectionString, config);
    }
}

int main(int /*argc*/, const char* /*argv*/[])
{
    const auto client = Instance();

    // Discover all available devices
    auto strings = List<IString>();
    strings.pushBack("daq.ns://[fe80::a00:27ff:fe3d:35c0%16]");
    strings.pushBack("daq.ns://[fe80::a00:27ff:fe47:2281%50]");
    strings.pushBack("daq.ns://[fe80::a00:27ff:feab:27f6%45]");

    // Create a configuration for the devices
    auto config = client.createDefaultAddDeviceConfig();
    PropertyObjectPtr generalConfig = config.getPropertyValue("General");
    generalConfig.setPropertyValue("Username", "user");
    generalConfig.setPropertyValue("Password", "password");

    // Connection arguments
    auto connectionArgs = Dict<IString, IPropertyObject>();

    for (const auto& string : strings)
    {
        connectionArgs.set(string, nullptr);
    }

    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        sequetialConnect(connectionArgs);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Time difference sequential = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]"
                  << std::endl;
    }

    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        parallelConnect(connectionArgs);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

        std::cout << "Time difference parallel = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]"
                  << std::endl;
    }

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
