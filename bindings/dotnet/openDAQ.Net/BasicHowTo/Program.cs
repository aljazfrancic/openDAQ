using System.Diagnostics;
using Daq.Core.Types;
using Daq.Core.Objects;
using Daq.Core.OpenDAQ;


var instance = OpenDAQFactory.Instance();

var config = instance.CreateDefaultAddDeviceConfig();
var generalConfig = config.GetPropertyValue("General").Cast<PropertyObject>();
generalConfig.SetPropertyValue("Username", "root");
generalConfig.SetPropertyValue("Password", "root");

var device = instance.AddDevice("daq.nd://[fe80::a00:27ff:fe07:d6d3%19]:7420/", config);  // change to your device address

// Restore defaults
device.SetPropertyValue("userName", "");
device.SetPropertyValue("NumberOfChannels", 2);
device.SetPropertyValue("GlobalSampleRate", 1000.0);
device.SetPropertyValue("EnableCANChannel", false);

// Begin/End update
device.BeginUpdate();

// Set value of all types available on existing components
device.SetPropertyValue("userName", "testUserName");  // string
device.SetPropertyValue("NumberOfChannels", 3);       // integer
device.SetPropertyValue("GlobalSampleRate", 1024.3);  // float
device.SetPropertyValue("EnableCANChannel", true);    // boolean

// To validate Begin/End update
Debug.Assert(device.GetPropertyValue("userName") != "testUserName");
Debug.Assert(device.GetPropertyValue("NumberOfChannels") != 3);
Debug.Assert(device.GetPropertyValue("GlobalSampleRate") != 1024.3);
Debug.Assert(device.GetPropertyValue("EnableCANChannel") != true);

// Begin/End update
device.EndUpdate();

// Get value of all types available on existing components
Debug.Assert(device.GetPropertyValue("userName") == "testUserName");
Debug.Assert(device.GetPropertyValue("NumberOfChannels") == 3);
Debug.Assert(device.GetPropertyValue("GlobalSampleRate") == 1024.3);
Debug.Assert(device.GetPropertyValue("EnableCANChannel") == true);

// Function
var fun = device.GetPropertyValue("Protected.Sum").Cast<Function>();
var list = CoreTypesFactory.CreateList<IntegerObject>();
list.Add(CoreTypesFactory.CreateInteger(2));
list.Add(CoreTypesFactory.CreateInteger(3));
var result = fun.Call((BaseObject)list).Cast<IntegerObject>();
Debug.Assert(result.Value == 5);

// Get/Set nested object values
device.SetPropertyValue("Protected.Owner", "testOwner");
Debug.Assert(device.GetPropertyValue("Protected.Owner") == "testOwner");
