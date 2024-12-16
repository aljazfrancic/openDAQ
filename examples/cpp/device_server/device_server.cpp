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

    auto typeManager = instance.getContext().getTypeManager();
    typeManager.addType(StructType("StructName", {"FieldName"}, {"Default"}, List<IType>(SimpleType(ctString))));

    auto myStruct = StructBuilder("StructName", typeManager).set("FieldName", "FieldValue µ").build();
    auto structProp = PropertyBuilder("MyStructProp").setDefaultValue(myStruct).setValueType(ctStruct).build();

    instance.addProperty(structProp);

    std::cin.get();
    return 0;
}
