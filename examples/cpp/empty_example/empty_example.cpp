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
    auto signal = Signal(instance.getContext(), signals, "sig1");
    signals.addItem(signal);

    auto chans = root.getChannels();

    instance.addStandardServers();

    // test_last_value_data_packet
    // TODO

    // test_last_value_signal
    auto descriptor = DataDescriptorBuilder().setSampleType(SampleType::Float64).build();  // CHANGE

    auto packet = DataPacket(descriptor, 5);

    auto data = static_cast<double*>(packet.getData());  // CHANGE
    data[4] = 0.3;                                       // CHANGE

    // test_last_value_range
    // TODO

    signal.setDescriptor(descriptor);
    signal.sendPacket(packet);

    while (true)
        std::this_thread::sleep_for(100ms);
}
