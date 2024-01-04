/**
 * My example
 */

#include <opendaq/opendaq.h>
#include <chrono>
#include <iostream>
#include <thread>

int main(int /*argc*/, const char* /*argv*/[])
{
    // Create an Instance, loading modules at MODULE_PATH
    const daq::InstancePtr instance = daq::Instance(MODULE_PATH);

    // Print modules and their function blocks
    std::cout << "modules and their function blocks:" << std::endl;

    auto modules = instance.getModuleManager().getModules();

    for (auto module : modules)
    {
        std::cout << "  " << module.getName() << std::endl;

        auto fbts = module.getAvailableFunctionBlockTypes();
        for (auto fbt : fbts)
        {
            std::cout << "    " << fbt.first << std::endl;
        }
    }

    // Discover and print the names and connection strings of openDAQ(TM) devices
    std::cout << "devices:" << std::endl;
    daq::ListPtr<daq::IDeviceInfo> availableDevicesInfo = instance.getAvailableDevices();
    for (const auto& deviceInfo : availableDevicesInfo)
        std::cout << "Name: " << deviceInfo.getName() << ", Address: " << deviceInfo.getConnectionString() << std::endl;

    // Add a reference device and set it as root
    auto device = instance.addDevice("daqref://device0");

    // Add my filter and renderer function block
    auto my_filter = instance.addFunctionBlock("my_filter");
    auto renderer = instance.addFunctionBlock("ref_fb_module_renderer");

    // Set renderer to draw 2 s of data
    renderer.setPropertyValue("Duration", 2);

    // Get channel and signal of reference device
    const auto sineChannel = device.getChannels()[0];
    const auto sineSignal = sineChannel.getSignals()[0];

    // Add noise to the sine wave
    sineChannel.setPropertyValue("NoiseAmplitude", 0.5);
    sineChannel.setPropertyValue("Frequency", 1);

    // Set my filter properies
    my_filter.setPropertyValue("CutoffFrequency", 2);
    // my_filter.setPropertyValue("Offset", 5);

    // Connect the signals to the renderer and my filter
    my_filter.getInputPorts()[0].connect(sineSignal);
    const auto averagedSine = my_filter.getSignalsRecursive()[0];

    renderer.getInputPorts()[0].connect(sineSignal);
    renderer.getInputPorts()[1].connect(averagedSine);

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
