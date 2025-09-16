import opendaq as daq

instance = daq.Instance()

config = instance.create_default_add_device_config()
general = config.get_property_value("General")

general.set_property_value("Username", "root")
general.set_property_value("Password", "root")

device = instance.add_device("daq.nd://[fe80::a00:27ff:fe07:d6d3%19]:7420/", config) # change to your device address

device.set_property_value("userName", "")
device.set_property_value("NumberOfChannels", 2)
device.set_property_value("GlobalSampleRate", 1000.0)
device.set_property_value("EnableCANChannel", False)

device.begin_update()

device.set_property_value("userName", "testUserName")
device.set_property_value("NumberOfChannels", 3)
device.set_property_value("GlobalSampleRate", 1024.3)
device.set_property_value("EnableCANChannel", True)

assert(device.get_property_value("userName") != "testUserName")
assert(device.get_property_value("NumberOfChannels") != 3)
assert(device.get_property_value("GlobalSampleRate") != 1024.3)
assert(device.get_property_value("EnableCANChannel") != True)

device.end_update()

assert(device.get_property_value("userName") == "testUserName")
assert(device.get_property_value("NumberOfChannels") == 3)
assert(device.get_property_value("GlobalSampleRate") == 1024.3)
assert(device.get_property_value("EnableCANChannel") == True)



pass
