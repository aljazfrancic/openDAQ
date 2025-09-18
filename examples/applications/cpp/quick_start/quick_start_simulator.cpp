/**
 * Part of the openDAQ stand-alone application quick start guide. Starts
 * an openDAQ server on localhost that contains a simulated device.
 */

#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    using namespace std::chrono_literals;
    StringPtr loggerPath = "ref_device_simulator.log";

    auto users = List<IUser>();
    users.pushBack(User("opendaq", "$2b$10$bqZWNEd.g1R1Q1inChdAiuDr5lbal33bBNOehlCwuWcxRH5weF3hu"));          // password: opendaq
    users.pushBack(User("root", "$2b$10$k/Tj3yqFV7uQz42UCJK2n.4ECd.ySQ2Sfd81Kx.xfuMOeluvA/Vpy", {"admin"}));  // password: root
    const AuthenticationProviderPtr authenticationProvider = StaticAuthenticationProvider(true, users);

    PropertyObjectPtr config = PropertyObject();
    config.addProperty(StringProperty("Name", "MYSIM"));
    config.addProperty(StringProperty("LocalId", "RefDevSimulator"));
    config.addProperty(StringProperty("SerialNumber", "sim01"));
    config.addProperty(BoolProperty("EnableLogging", true));
    config.addProperty(StringProperty("LoggingPath", loggerPath));

    const InstancePtr instance = InstanceBuilder()
                                     .addModulePath(MODULE_PATH)
                                     .addDiscoveryServer("mdns")
                                     .setRootDevice("daqref://device1", config)
                                     .setLogger(Logger(loggerPath))
                                     .setAuthenticationProvider(authenticationProvider)
                                     .build();

    auto refDevice = instance.addDevice("daqref://device0");
    refDevice.setPropertyValue("EnableProtectedChannel", true);

    auto enumNames = List<IString>();
    enumNames.pushBack("First");
    enumNames.pushBack("Second");
    enumNames.pushBack("Third");
    auto typeManager = instance.getContext().getTypeManager();
    typeManager.addType(EnumerationType("Enum", enumNames));  // Must be registered before creating the Enumeration
    auto enu = Enumeration("Enum", "Second", typeManager);
    auto enumProp = EnumerationProperty("Enum", enu);
    instance.addProperty(enumProp);

    const auto structType = StructType("StructType", List<IString>("Int", "Float"), List<IType>(SimpleType(ctInt), SimpleType(ctFloat)));
    typeManager.addType(structType);
    const auto stru = StructBuilder("StructType", typeManager).set("Int", 5).set("Float", 5.3).build();
    const auto struProp = StructProperty("Struct", stru);
    instance.addProperty(struProp);

    auto coercedProp = IntPropertyBuilder("CoercedProp", 5).setCoercer(Coercer("if(Value > 10, 10, Value)")).build();
    instance.addProperty(coercedProp);

    const auto servers = instance.addStandardServers();

    for (const auto& server : servers)
        server.enableDiscovery();

    std::cout << "Press \"enter\" to exit the application..." << std::endl;
    std::cin.get();
    return 0;
}
