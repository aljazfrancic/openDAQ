#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    const InstancePtr instance = Instance(MODULE_PATH);

    std::cout << "DEVICES:" << std::endl;
    daq::ListPtr<daq::IDeviceInfo> infos = instance.getAvailableDevices();
    std::vector<std::string> strings;
    strings.push_back("daqref://device0");

    for (const auto& info : infos)
    {
        const auto address = info.getConnectionString().toStdString();
        std::cout << "  Name: " << info.getName() << ", Address: " << address << ", Serial number: " << info.getSerialNumber() << std::endl;
        if (address.substr(0, 9) == "daq.opcua")
            strings.push_back(address);
    }

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
