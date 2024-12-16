#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    PropertyObjectPtr config = PropertyObject();
    config.addProperty(StringProperty("SerialNumber", "007"));
    const InstancePtr instance = InstanceBuilder().addDiscoveryServer("mdns").setRootDevice("daqref://device0", config).build();
    auto servers = instance.addStandardServers();
    for (const auto& server : servers)
        server.enableDiscovery();

    auto myUnit = Unit("µ", -1, "SpecialName", "Quant");
    auto structProp = PropertyBuilder("MyStructProp").setDefaultValue(3).setValueType(ctInt).setUnit(myUnit).build();

    instance.addProperty(structProp);

    std::cin.get();
    return 0;
}
