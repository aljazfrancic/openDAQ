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

    const auto sumXYProp = FunctionPropertyBuilder("SumXY",
                                                   FunctionInfo(ctInt,
                                                                List<IArgumentInfo>(ArgumentInfo("Val1", ctInt),
                                                                                    ArgumentInfo("Val2", ctInt),
                                                                                    ArgumentInfo("Val3", ctString),
                                                                                    ArgumentInfo("Val4", ctList),
                                                                                    ArgumentInfo("Val5", ctList),
                                                                                    ArgumentInfo("Val6", ctList),
                                                                                    ArgumentInfo("Val7", ctList))))
                               .build();

    instance.addProperty(sumXYProp);

    auto myFun = Function(
        [](Int val1, Int val2, StringPtr val3, ListPtr<IInteger> val4, ListPtr<IString> val5, ListPtr<IFloat> val6, ListPtr<IBoolean> val7)
        {
            std::cout << "val1: " << val1 << " val2: " << val2 << " val3: " << val3 << "\n" << "val4: " << "\n";
            for (size_t i = 0; i < val4.getCount(); i++)
            {
                std::cout << "  " << val4[i] << "\n";
            }
            std::cout << "val5: " << "\n";
            for (size_t i = 0; i < val5.getCount(); i++)
            {
                std::cout << "  " << val5[i] << "\n";
            }
            std::cout << "val6: " << "\n";
            for (size_t i = 0; i < val6.getCount(); i++)
            {
                std::cout << "  " << val6[i] << "\n";
            }
            std::cout << "val7: " << "\n";
            for (size_t i = 0; i < val7.getCount(); i++)
            {
                std::cout << "  " << val7[i] << "\n";
            }
            std::cout << "\n\n";
            return Integer(val1 + val2);
        });

    instance.setPropertyValue("SumXY", myFun);

    FunctionPtr sum = instance.getPropertyValue("SumXY");

    auto list = List<IInteger>();
    list.pushBack(33);
    list.pushBack(34);

    auto stringList = List<IString>();
    stringList.pushBack("test1");
    stringList.pushBack("test2");

    auto floatList = List<IFloat>();
    floatList.pushBack(1.1f);
    floatList.pushBack(2.2f);

    auto boolList = List<IBoolean>();
    boolList.pushBack(true);
    boolList.pushBack(false);

    std::cout << "Result sum: " << sum(2, 3, "example", list, stringList, floatList, boolList) << "\n";

    std::cout << "Result myFun: " << myFun(2, 3, "example", list, stringList, floatList, boolList) << "\n";

    auto result = sum(2, 3, "example", list, stringList, floatList, boolList);

    auto ptr = result.asPtrOrNull<IInteger>();

    if (ptr.assigned())
    {
        std::cout << "Result asPtrOrNull: " << ptr.toString() << "\n";
    }
    else
    {
        std::cout << "Result asPtrOrNull: null" << "\n";
    }

    std::cout << "Press \"enter\" to exit the application..." << "\n";
    std::cin.get();

    return 0;
}
