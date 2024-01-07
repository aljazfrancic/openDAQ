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
    auto modules = instance.getModuleManager().getModules();

    std::cout << "MODULES AND THEIR FUNCTION BLOCKS:" << std::endl;
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
    std::cout << "DEVICES:" << std::endl;
    daq::ListPtr<daq::IDeviceInfo> availableDevicesInfo = instance.getAvailableDevices();
    for (const auto& deviceInfo : availableDevicesInfo)
        std::cout << "  Name: " << deviceInfo.getName() << ", Address: " << deviceInfo.getConnectionString() << std::endl;

    // Add a reference device and set it as root
    auto device = instance.addDevice("daqref://device0");

    // Print device properties
    std::cout << "DEVICE PROPERTIES:" << std::endl;
    auto deviceProps = device.getVisibleProperties();
    for (const auto& prop : deviceProps)
        std::cout << "  " << prop.getName() << ": " << device.getPropertyValue(prop.getName()) << std::endl;

    // Add my filter and renderer function blocks
    auto myFilter = instance.addFunctionBlock("my_filter");
    auto renderer = instance.addFunctionBlock("ref_fb_module_renderer");

    // Print my filter function block properties
    std::cout << "FUNCTION BLOCK PROPERTIES: " << std::endl;
    auto functionBlockProps = myFilter.getVisibleProperties();
    for (const auto& prop : functionBlockProps)
        std::cout << "  " << prop.getName() << ": " << myFilter.getPropertyValue(prop.getName()) << std::endl;

    // Get channel and signal of reference device
    const auto sineChannel = device.getChannels()[0];
    const auto sineSignal = sineChannel.getSignals()[0];

    // Print sine channel properties
    std::cout << "SINE CHANNEL PROPERTIES:" << std::endl;
    auto sineChannelProps = sineChannel.getVisibleProperties();
    for (const auto& prop : sineChannelProps)
        std::cout << "  " << prop.getName() << ": " << sineChannel.getPropertyValue(prop.getName()) << std::endl;

    // Print sine sinal properties
    std::cout << "SINE SIGNAL PROPERTIES:" << std::endl;
    auto sineSignalProps = sineSignal.getVisibleProperties();
    for (const auto& prop : sineSignalProps)
        std::cout << "  " << prop.getName() << ": " << sineSignal.getPropertyValue(prop.getName()) << std::endl;

    // Add noise to the sine wave
    sineChannel.setPropertyValue("NoiseAmplitude", 0.5);

    // Modify sine freqency
    sineChannel.setPropertyValue("Frequency", 1);

    // Connect the signal to the renderer and my filter
    myFilter.getInputPorts()[0].connect(sineSignal);
    const auto averagedSine = myFilter.getSignalsRecursive()[0];

    renderer.getInputPorts()[0].connect(sineSignal);
    renderer.getInputPorts()[1].connect(averagedSine);

    // Sleep to demonstrate online cutoff freqency change via properties
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));

    // Change cutoff frequency
    myFilter.setPropertyValue("CutoffFrequency", 200);

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
