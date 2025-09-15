#include <opendaq/opendaq.h>
#include <iostream>

using namespace daq;

int main(int /*argc*/, const char* /*argv*/[])
{
    const InstancePtr instance = Instance(MODULE_PATH);

    auto config = instance.createDefaultAddDeviceConfig();
    PropertyObjectPtr generalConfig = config.getPropertyValue("General");
    generalConfig.setPropertyValue("Username", "root");
    generalConfig.setPropertyValue("Password", "root");

    auto device = instance.addDevice("daq.nd://[fe80::a00:27ff:fe07:d6d3%18]:7420/", config);  // change to your device address

    // Set value of all types available on existing components
    device.setPropertyValue("userName", "testUserName");  // string
    device.setPropertyValue("NumberOfChannels", 3);       // integer
    device.setPropertyValue("GlobalSampleRate", 1024.3);  // float
    device.setPropertyValue("EnableCANChannel", true);    // boolean

    // Get value of all types available on existing components
    assert(device.getPropertyValue("userName") == "testUserName");
    assert(device.getPropertyValue("NumberOfChannels") == 3);
    assert(device.getPropertyValue("GlobalSampleRate") == 1024.3);
    assert(device.getPropertyValue("EnableCANChannel") == true);

    // Procedure
    FunctionPtr fun = device.getPropertyValue("Protected.Sum");
    assert(fun(2, 3) == 5);
    auto proc = Function([](IntegerPtr a, IntegerPtr b) { return a * b; });
    // configureBasicProperty(fb, "Procedure", proc);
    // ProcedurePtr newProc = fb.getPropertyValue("Procedure");
    // newProc(42);

    return 0;
}
