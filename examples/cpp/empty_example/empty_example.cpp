
#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    const InstancePtr instance = Instance("");
    auto dev = instance.addDevice("daq://openDAQ_007");

    auto myStructProp = dev.getPropertyValue("MyStructProp");
    auto myStruct = myStructProp.asPtr<IStruct>();
    auto myField = myStruct.get("FieldName").asPtr<IString>();
    std::cout << myField << std::endl;

    std::cin.get();
    return 0;
}
