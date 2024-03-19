#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    // Create an Instance, loading modules at MODULE_PATH
    const InstancePtr instance = Instance(MODULE_PATH);

    // Add reference device
    const auto device = instance.addDevice("daqref://device0");

    // Add statistics function block
    const auto statistics = instance.addFunctionBlock("ref_fb_module_statistics");

    // Add renderer function block
    const auto renderer = instance.addFunctionBlock("ref_fb_module_renderer");

    // Make both renderer axes move in unison
    renderer.setPropertyValue("SingleXAxis", true);

    // Get sine channel from reference device
    const auto sineChannel = device.getChannels()[0];

    // Get sine signal form channel
    const auto sineSignal = sineChannel.getSignals()[0];

    // Set sine frequency to 1 Hz
    sineChannel.setPropertyValue("Frequency", 1);

    // Enable trigger mode in statistics
    statistics.setPropertyValue("TriggerMode", true);

    // Connect sine signal as input to statistics
    statistics.getInputPorts()[0].connect(sineSignal);

    // Connect THE SAME signal as input to nested trigger function block
    statistics.getFunctionBlocks()[0].getInputPorts()[0].connect(sineSignal);

    // Connect sine signal to renderer
    renderer.getInputPorts()[0].connect(sineSignal);

    // Connect statistics output to renderer
    renderer.getInputPorts()[1].connect(statistics.getSignals()[0]);

    // Statistics now only outputs when last trigger output was true
    // (when sine is above 0.5)

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
