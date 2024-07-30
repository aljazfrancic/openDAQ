/**
 * Empty example
 */

#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    // Create an Instance, loading modules at MODULE_PATH
    const InstancePtr instance = Instance(MODULE_PATH);

    // Both old and new function block IDs
    const auto fbIds = List<IString>("AudioDeviceModuleWavWriter",
                                     //"RefFBModuleRenderer",
                                     "RefFBModuleStatistics",
                                     "RefFBModulePower",
                                     "RefFBModuleScaling",
                                     "RefFBModuleClassifier",
                                     "RefFBModuleTrigger",
                                     "RefFBModuleFFT",
                                     "audio_device_module_wav_writer",
                                     //"ref_fb_module_renderer",
                                     "ref_fb_module_statistics",
                                     "ref_fb_module_power",
                                     "ref_fb_module_scaling",
                                     "ref_fb_module_classifier",
                                     "ref_fb_module_trigger",
                                     "ref_fb_module_fft");

    // Old server IDs
    const auto serverOldIds = List<IString>("openDAQ LT Streaming", "openDAQ Native Streaming", "openDAQ OpcUa");

    // Add device
    const auto dev = instance.addDevice("daq.nd://127.0.0.1/");

    // Add function block
    for (const auto& id : fbIds)
    {
        const auto fb = instance.addFunctionBlock(id);
        std::cout << "typeId used for addFunctionBlock: " << id << std::endl;
        std::cout << "Added instance function block: local id: " << fb.getLocalId() << " (name: " + fb.getName() + ")" << std::endl
                  << std::endl;
    }

    // Add server
    for (const auto& id : serverOldIds)
    {
        const auto server = instance.addServer(id, nullptr);
        std::cout << "serverTypeId used for addServer (OLD): " << id << std::endl;
        std::cout << "Added Instance server: server id: " << server.getId() << std::endl << std::endl;
    }

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
