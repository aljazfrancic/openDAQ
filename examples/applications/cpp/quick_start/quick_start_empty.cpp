#include <opendaq/opendaq.h>
#include <chrono>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    const daq::InstancePtr instance = daq::Instance(MODULE_PATH);

    auto avail = instance.getAvailableDevices();

    daq::DevicePtr dev;  // = instance.addDevice("daq.nd://192.168.131.1/");  // change to your device address

    for (const auto& deviceInfo : avail)
    {
        std::cout << "Found device: " << deviceInfo.getName() << " at " << deviceInfo.getConnectionString() << "\n";

        if (deviceInfo.getName() == "MYSIM")
        {
            dev = instance.addDevice(deviceInfo.getConnectionString());
            std::cout << "Added MYSIM\n";
        }
    }

    // Enumeration Property
    dev.setPropertyValue("Enum", 1);            // "Second"
    assert(dev.getPropertyValue("Enum") == 1);  // "Second"
    dev.setPropertyValue("Enum", 2);            // "Third"
    assert(dev.getPropertyValue("Enum") == 2);  // "Third"

    // Struct Property
    const auto stru = StructBuilder("StructType", instance.getContext().getTypeManager()).set("Int", 4).set("Float", 4.2).build();
    dev.setPropertyValue("Struct", stru);
    assert(dev.getPropertyValue("Struct") == stru);

    // Coerced Property
    dev.setPropertyValue("CoercedProp", 100);
    assert(dev.getPropertyValue("CoercedProp") == 10);

    // Reference Property
    dev.setPropertyValue("Integer", 0);
    assert(dev.getPropertyValue("RefProp") == "foo");
    dev.setPropertyValue("Integer", 1);
    assert(dev.getPropertyValue("RefProp") == "bar");
    dev.setPropertyValue("Integer", 0);

    return 0;
}
