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

    std::cout << "kek" << std::endl;

    auto modules = instance.getModuleManager().getModules();

    for (auto module : modules)
    {
        std::cout << "  " << module.getName() << std::endl;

        auto fbts = module.getAvailableFunctionBlockTypes();
        for (auto fbt : fbts)
        {
            std::cout << "    " << fbt.first << std::endl;
        }
    }

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
