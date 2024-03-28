#!/usr/bin/env python

import unittest

from opendaq import IDataPacket

import opendaq_test
import opendaq

mock = opendaq.MockSignal()
mock.add_data([0.1, 0.2, 0.3])
signal = mock.signal


# TODO update
# Corresponding document: Antora/modules/howto_guides/pages/howto_measure_single_value.adoc
class TestDocumentationHowToLastValue(opendaq_test.TestCase):

    def test_last_value_data_packet(self):
        packet = opendaq.IDataPacket()

        # START DOCS CODE

        # Get last value of a Data Packet
        packet.last_value()  # TODO ()???

        # END DOCS CODE

    def test_last_value_signal(self):
        # START DOCS CODE

        # Get last value of a Signal
        last_value = signal.last_value

        # Print last value
        print("last value: ", last_value)

        # END DOCS CODE

        self.assertEqual(last_value, 0.3)

    def test_last_value_range(self):
        # START DOCS CODE

        # The Data Descriptor for RangeInt64
        builder = opendaq.DataDescriptorBuilder()
        builder.sample_type = opendaq.SampleType.RangeInt64
        descriptor = builder.build()

        # Get last value of a Signal
        last_value = signal.last_value

        # END DOCS CODE

        last_value = opendaq.IRange()

        # START DOCS CODE

        # Extract values
        low = last_value.low_value
        high = last_value.high_value

        # END DOCS CODE

    def test_last_value_signal_complex_float32(self):
        # START DOCS CODE

        # The Data Descriptor for ComplexFloat32
        builder = opendaq.DataDescriptorBuilder()
        builder.sample_type = opendaq.SampleType.ComplexFloat32
        descriptor = builder.build()

        # Get last value of a Signal
        last_value = signal.last_value

        # END DOCS CODE

        last_value = opendaq.IComplexNumber()

        # START DOCS CODE

        # Extract values
        real = last_value.real
        imaginary = last_value.imaginary

        # END DOCS CODE

    def test_last_value_signal_struct(self):
        # START DOCS CODE

        # Create a Data Descriptor
        builder_int = opendaq.DataDescriptorBuilder()
        builder_int.name = "MyInt32"
        builder_int.sample_type = opendaq.SampleType.Int32
        descriptor_int = builder_int.build()

        builder_float = opendaq.DataDescriptorBuilder()
        builder_float.name = "MyFloat64"
        builder_float.sample_type = opendaq.SampleType.Float64
        descriptor_float = builder_float.build()

        builder = opendaq.DataDescriptorBuilder()
        builder.name = "MyStruct"
        builder.sample_type = opendaq.SampleType.Struct  # TODO not implemented
        struct_fields = opendaq.List()
        struct_fields.append(descriptor_int)
        struct_fields.append(descriptor_float)
        builder.struct_fields = struct_fields
        descriptor = builder.build()

        # Get last value of a Signal
        last_value = signal.last_value

        # END DOCS CODE

        last_value = opendaq.IStruct()

        # START DOCS CODE

        # Extract values
        my_int = last_value.get("MyInt32")
        my_float = last_value.get("MyFloat64")

        # END DOCS CODE

    def test_last_value_signal_list(self):
        # START DOCS CODE

        # Get last value of a Signal
        last_value = signal.last_value

        # END DOCS CODE

        last_value = opendaq.IList()

        # START DOCS CODE

        # Extract the third item
        third = last_value[2]

        # END DOCS CODE

if __name__ == '__main__':
    unittest.main()
