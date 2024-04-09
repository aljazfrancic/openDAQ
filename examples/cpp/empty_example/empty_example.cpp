#include <opendaq/channel_impl.h>
#include <opendaq/opendaq.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace daq;
using namespace std::chrono_literals;

int main(int /*argc*/, const char* /*argv*/[])
{
    auto instance = Instance();

    auto root = instance.getRootDevice();

    FolderConfigPtr signals = root.getItem("Sig");

    // test_last_value_signal
    {
        auto signal = Signal(instance.getContext(), signals, "float");
        signals.addItem(signal);
        auto descriptor = DataDescriptorBuilder().setSampleType(SampleType::Float64).build();
        auto packet = DataPacket(descriptor, 5);
        auto data = static_cast<double*>(packet.getData());
        data[4] = 0.3;
        signal.setDescriptor(descriptor);
        signal.sendPacket(packet);
    }

    // test_last_value_range
    {
        auto signal = Signal(instance.getContext(), signals, "range");
        signals.addItem(signal);
        auto descriptor = DataDescriptorBuilder().setSampleType(SampleType::RangeInt64).build();
        auto packet = DataPacket(descriptor, 5);
        auto data = static_cast<int64_t*>(packet.getData());
        data[8] = 2;
        data[9] = 4;
        signal.setDescriptor(descriptor);
        signal.sendPacket(packet);
    }

    // test_last_value_signal_complex_float32
    {
        auto signal = Signal(instance.getContext(), signals, "complex");
        signals.addItem(signal);
        auto descriptor = DataDescriptorBuilder().setSampleType(SampleType::ComplexFloat32).build();
        auto packet = DataPacket(descriptor, 5);
        auto data = static_cast<float*>(packet.getData());
        data[8] = 2.2f;
        data[9] = 4.4f;
        signal.setDescriptor(descriptor);
        signal.sendPacket(packet);
    }

    // test_last_value_signal_list
    {
        auto signal = Signal(instance.getContext(), signals, "list");
        signals.addItem(signal);

        auto numbers = List<INumber>();
        numbers.pushBack(1);
        numbers.pushBack(2);

        auto dimensions = List<IDimension>();
        dimensions.pushBack(Dimension(ListDimensionRule(numbers)));

        auto descriptor = DataDescriptorBuilder().setSampleType(SampleType::Int64).setDimensions(dimensions).build();

        auto packet = DataPacket(descriptor, 5);
        int64_t* data = static_cast<int64_t*>(packet.getData());
        data[8] = 4;
        data[9] = 44;

        signal.setDescriptor(descriptor);
        signal.sendPacket(packet);
    }

    instance.addStandardServers();

    while (true)
        std::this_thread::sleep_for(100ms);
}
