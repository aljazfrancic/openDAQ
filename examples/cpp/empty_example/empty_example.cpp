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

    std::cout << "DEVICES:" << std::endl;
    daq::ListPtr<daq::IDeviceInfo> infos = instance.getAvailableDevices();
    for (const auto& info : infos)
        std::cout << "  Name: " << info.getName() << ", Address: " << info.getConnectionString()
                  << ", Serial number: " << info.getSerialNumber() << std::endl;


    auto strings = std::vector{"daq.opcua://192.168.56.101/", "daqref://device0"};

    for (auto& str : strings)
    {
        auto dev = instance.addDevice(str);

        std::this_thread::sleep_for(std::chrono::seconds(1));

        std::cout << "last value: " << dev.getChannels()[0].getSignals()[0].getLastValue() << std::endl;

        std::cout << "localID: " << dev.getLocalId() << std::endl;
    }

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
