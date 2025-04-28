#include <opendaq/opendaq.h>
#include <iostream>

#include "coreobjects/argument_info_factory.h"
#include "coreobjects/callable_info_factory.h"

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    const InstancePtr instance = InstanceBuilder().addDiscoveryServer("mdns").setRootDevice("daqref://device0").build();

    const auto servers = instance.addStandardServers();

    for (const auto& server : servers)
        server.enableDiscovery();

    const auto sumXYProp =
        FunctionPropertyBuilder(
            "SumXY",
            FunctionInfo(ctInt,
                         List<IArgumentInfo>(ArgumentInfo("Val1", ctInt), ArgumentInfo("Val2", ctInt), ArgumentInfo("Val3", ctString))))
            .build();

    instance.addProperty(sumXYProp);

    auto myFun = Function(
        [](Int val1, Int val2, StringPtr val3)
        {
            std::cout << "SumXY str is: " << val3 << "\n";
            return Integer(val1 + val2);
        });

    instance.setPropertyValue("SumXY", myFun);

    FunctionPtr sum = instance.getPropertyValue("SumXY");

    std::cout << "Result sum: " << sum(2, 3, "example") << "\n";

    std::cout << "Result myFun: " << myFun(2, 3, "example") << "\n";

    std::cout << "Press \"enter\" to exit the application..." << "\n";
    std::cin.get();
    return 0;
}
