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

    auto device = instance.addDevice("daq.nd://[fe80::a00:27ff:fe07:d6d3%19]:7420/", config);  // change to your device address

    // Restore defaults
    device.setPropertyValue("userName", "");
    device.setPropertyValue("NumberOfChannels", 2);
    device.setPropertyValue("GlobalSampleRate", 1000.0);
    device.setPropertyValue("EnableCANChannel", false);

    // Begin/End update
    device.beginUpdate();

    // Set value of all types available on existing components
    device.setPropertyValue("userName", "testUserName");  // string
    device.setPropertyValue("NumberOfChannels", 3);       // integer
    device.setPropertyValue("GlobalSampleRate", 1024.3);  // float
    device.setPropertyValue("EnableCANChannel", true);    // boolean

    // To validate Begin/End update
    assert(device.getPropertyValue("userName") != "testUserName");
    assert(device.getPropertyValue("NumberOfChannels") != 3);
    assert(device.getPropertyValue("GlobalSampleRate") != 1024.3);
    assert(device.getPropertyValue("EnableCANChannel") != true);

    // Begin/End update
    device.endUpdate();

    // Get value of all types available on existing components
    assert(device.getPropertyValue("userName") == "testUserName");
    assert(device.getPropertyValue("NumberOfChannels") == 3);
    assert(device.getPropertyValue("GlobalSampleRate") == 1024.3);
    assert(device.getPropertyValue("EnableCANChannel") == true);

    // Function
    FunctionPtr fun = device.getPropertyValue("Protected.Sum");
    assert(fun(2, 3) == 5);

    // Get/Set nested object values
    device.setPropertyValue("Protected.Owner", "testOwner");
    assert(device.getPropertyValue("Protected.Owner") == "testOwner");

    // CANNOT SET REMOTE FUNCTION PROPERTY
    // auto proc = Function([](IntegerPtr a, IntegerPtr b) { return a * b; });
    // device.setPropertyValue("Protected.Sum", proc);
    // FunctionPtr newFun = device.getPropertyValue("Protected.Sum");
    // assert(newFun(2, 3) == 6);

    return 0;
}
