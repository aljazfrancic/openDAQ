#include <opendaq/packet.h>
#include <opendaq/reader_factory.h>
#include <iostream>
#include "websocket_streaming/websocket_streaming_server.h"
#include <opendaq/device_private.h>
#include <coreobjects/property_factory.h>
#include <opendaq/search_filter_factory.h>
#include <opendaq/device_info_factory.h>
#include <opendaq/device_info_internal_ptr.h>
#include <opendaq/custom_log.h>
#include <coretypes/intfs.h>

BEGIN_NAMESPACE_OPENDAQ_WEBSOCKET_STREAMING

WebsocketStreamingServer::~WebsocketStreamingServer()
{
    this->context.getOnCoreEvent() -= event(this, &WebsocketStreamingServer::coreEventCallback);
    stopInternal();
}

WebsocketStreamingServer::WebsocketStreamingServer(const InstancePtr& instance)
    : WebsocketStreamingServer(instance.getRootDevice(), instance.getContext())
{
}

WebsocketStreamingServer::WebsocketStreamingServer(const DevicePtr& device, const ContextPtr& context)
    : device(device)
    , context(context)
    , streamingServer(context)
    , packetReader(device, context)
    , loggerComponent(context.getLogger().getOrAddComponent("WebsocketStreamingServer"))
{
}

void WebsocketStreamingServer::setStreamingPort(uint16_t port)
{
    this->streamingPort = port;
}

void WebsocketStreamingServer::setControlPort(uint16_t port)
{
    this->controlPort = port;
}

void WebsocketStreamingServer::start()
{
    if (!device.assigned())
        DAQ_THROW_EXCEPTION(InvalidStateException, "Device is not set.");
    if (!context.assigned())
        DAQ_THROW_EXCEPTION(InvalidStateException, "Context is not set.");
    if (streamingPort == 0 || controlPort == 0)
        return;

    streamingServer.onAccept([this](const daq::streaming_protocol::StreamWriterPtr& writer) { return device.getSignals(search::Recursive(search::Any())); });
    streamingServer.onStartSignalsRead([this](const ListPtr<ISignal>& signals) { packetReader.startReadSignals(signals); } );
    streamingServer.onStopSignalsRead([this](const ListPtr<ISignal>& signals) { packetReader.stopReadSignals(signals); } );
    streamingServer.start(streamingPort, controlPort);

    packetReader.setLoopFrequency(50);
    packetReader.onPacket([this](const SignalPtr& signal, const ListPtr<IPacket>& packets) {
        const auto signalId = signal.getGlobalId();
        for (const auto& packet : packets)
            streamingServer.broadcastPacket(signalId, packet);
    });
    packetReader.start();

    this->context.getOnCoreEvent() += event(this, &WebsocketStreamingServer::coreEventCallback);

    const ServerCapabilityConfigPtr serverCapability = ServerCapability("OpenDAQLTStreaming", "OpenDAQLTStreaming", ProtocolType::Streaming);
    serverCapability.setPrefix("daq.lt");
    serverCapability.setPort(streamingPort);
    serverCapability.setConnectionType("TCP/IP");
    this->device.getInfo().asPtr<IDeviceInfoInternal>().addServerCapability(serverCapability);
}

void WebsocketStreamingServer::stop()
{
    if (this->device.assigned())
    {
         const auto info = this->device.getInfo();
         const auto infoInternal = info.asPtr<IDeviceInfoInternal>();
         if (info.hasServerCapability("OpenDAQLTStreaming"))
             infoInternal.removeServerCapability("OpenDAQLTStreaming");
    }

    stopInternal();
}

void WebsocketStreamingServer::stopInternal()
{
    packetReader.stop();
    streamingServer.stop();
}

void WebsocketStreamingServer::coreEventCallback(ComponentPtr& sender, CoreEventArgsPtr& eventArgs)
{
    switch (static_cast<CoreEventId>(eventArgs.getEventId()))
    {
        case CoreEventId::ComponentAdded:
            componentAdded(sender, eventArgs);
            break;
        case CoreEventId::ComponentRemoved:
            componentRemoved(sender, eventArgs);
            break;
        case CoreEventId::ComponentUpdateEnd:
            componentUpdated(sender);
            break;
        default:
            break;
    }
}

DictPtr<IString, ISignal> WebsocketStreamingServer::getSignalsOfComponent(ComponentPtr& component)
{
    auto signals = Dict<IString, ISignal>();
    if (component.supportsInterface<ISignal>())
    {
        signals.set(component.getGlobalId(), component.asPtr<ISignal>());
    }
    else if (component.supportsInterface<IFolder>())
    {
        auto nestedComponents = component.asPtr<IFolder>().getItems(search::Recursive(search::Any()));
        for (const auto& nestedComponent : nestedComponents)
        {
            if (nestedComponent.supportsInterface<ISignal>())
                signals.set(nestedComponent.getGlobalId(), nestedComponent.asPtr<ISignal>());
        }
    }
    return signals;
}

void WebsocketStreamingServer::componentAdded(ComponentPtr& /*sender*/, CoreEventArgsPtr& eventArgs)
{
    ComponentPtr addedComponent = eventArgs.getParameters().get("Component");

    auto deviceGlobalId = device.getGlobalId().toStdString();
    auto addedComponentGlobalId = addedComponent.getGlobalId().toStdString();
    if (addedComponentGlobalId.find(deviceGlobalId) != 0)
        return;

    LOG_I("Added Component: {};", addedComponentGlobalId);
    streamingServer.addSignals(getSignalsOfComponent(addedComponent).getValueList());
}

void WebsocketStreamingServer::componentRemoved(ComponentPtr& sender, CoreEventArgsPtr& eventArgs)
{
    StringPtr removedComponentLocalId = eventArgs.getParameters().get("Id");

    auto deviceGlobalId = device.getGlobalId().toStdString();
    auto removedComponentGlobalId =
        sender.getGlobalId().toStdString() + "/" + removedComponentLocalId.toStdString();
    if (removedComponentGlobalId.find(deviceGlobalId) != 0)
         return;

    LOG_I("Component: {}; is removed", removedComponentGlobalId);
    streamingServer.removeComponentSignals(removedComponentGlobalId);
}

void WebsocketStreamingServer::componentUpdated(ComponentPtr& updatedComponent)
{
    auto deviceGlobalId = device.getGlobalId().toStdString();
    auto updatedComponentGlobalId = updatedComponent.getGlobalId().toStdString();
    if (updatedComponentGlobalId.find(deviceGlobalId) != 0)
        return;

    LOG_I("Component: {}; is updated", updatedComponentGlobalId);

    // update list of known signals to include added and exclude removed signals
    streamingServer.updateComponentSignals(getSignalsOfComponent(updatedComponent), updatedComponentGlobalId);
}

END_NAMESPACE_OPENDAQ_WEBSOCKET_STREAMING
