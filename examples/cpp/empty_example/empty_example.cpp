
#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    const InstancePtr instance = Instance("");
    auto dev = instance.addDevice("daq://openDAQ_007");

    auto myStructProp = dev.getProperty("MyStructProp");
    auto mySymbol = myStructProp.getUnit().getSymbol();
    std::cout << mySymbol << std::endl;

    std::cin.get();
    return 0;
}
