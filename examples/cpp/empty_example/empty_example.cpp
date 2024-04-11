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

    // test_last_value_signal_struct
    {
        auto signal = Signal(instance.getContext(), signals, "MyTestStructType");
        signals.addItem(signal);

        // Create data descriptor
        const auto descriptor = DataDescriptorBuilder()
                                    .setName("MyTestStructType")
                                    .setSampleType(SampleType::Struct)
                                    .setStructFields(List<DataDescriptorPtr>(
                                        DataDescriptorBuilder().setName("Int32").setSampleType(SampleType::Int32).build(),
                                        DataDescriptorBuilder().setName("Float64").setSampleType(SampleType::Float64).build()))
                                    .build();

        // Prepare data packet
        auto sizeInBytes = sizeof(int32_t) + sizeof(double);
        const auto packet = DataPacket(descriptor, 5);
        auto data = packet.getData();

        // Start points to beggining of data
        auto start = static_cast<char*>(data);

        // First member of data is int32_t
        void* a = start + sizeInBytes * 4;
        auto A = static_cast<int32_t*>(a);
        *A = 12;

        // Second member of data is double
        void* b = start + sizeInBytes * 4 + sizeof(int32_t);
        auto B = static_cast<double*>(b);
        *B = 15.1;

        signal.setDescriptor(descriptor);
        signal.sendPacket(packet);
    }

    instance.addStandardServers();

    while (true)
        std::this_thread::sleep_for(100ms);
}
