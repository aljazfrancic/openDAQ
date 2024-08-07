#!/usr/bin/env python

import unittest
import opendaq_test
import opendaq

# Corresponding document: Antora/modules/howto_guides/pages/howto_add_function_block.adoc
class TestDocumentationHow(opendaq_test.TestCase):

    def test_start_simulator(self):
        # Create openDAQ instance
        instance = opendaq.Instance()

        # Add a reference device and set it as root
        instance.set_root_device('daqref://device0')
        device = instance.root_device

        # Start a web-socket streaming server
        instance.add_server('OpenDAQLTStreaming', None)

        # Start an openDAQ OPC UA and native streaming servers
        # TODO: remove assignment to `servers` once OPC UA server destruction order issue is fixed
        servers = instance.add_standard_servers()

    def test_discovering_devices(self):
        # Create openDAQ instance
        instance = opendaq.Instance()

        # Find and output the names and connection strings of all available devices
        available_devices_info = instance.available_devices
        for device_info in available_devices_info:
            print("Name:", device_info.name, "Connection string:", device_info.connection_string)

    def test_connecting_to_device(self):
        # Create a fresh openDAQ instance we will use for all the interactions with the openDAQ SDK
        instance = opendaq.Instance()

        # Find and connect to a device hosting an OPC UA TMS server
        for device_info in instance.available_devices:
            if 'daqref://' in device_info.connection_string:
                device = instance.add_device(device_info.connection_string)
                break
        else:
            # Exit if no device is found
            exit(1)

        # Output the name of the added device
        print(device.info.name)

    def test_read_signal(self):
        import time

        instance = opendaq.Instance()
        device = instance.add_device('daqref://device0')
        signal = device.signals_recursive[0]

        reader = opendaq.StreamReader(signal)

        time.sleep(0.1)
        samples = reader.read(100)
        if len(samples) > 0:
            print(samples[-1])

if __name__ == '__main__':
    unittest.main()
