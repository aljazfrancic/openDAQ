#include <websocket_streaming_client_module/websocket_streaming_client_module_impl.h>
#include <websocket_streaming_client_module/version.h>
#include <coretypes/version_info_factory.h>
#include <chrono>
#include <websocket_streaming/websocket_client_device_factory.h>
#include <websocket_streaming/websocket_streaming_factory.h>
#include <opendaq/streaming_type_factory.h>
#include <opendaq/device_type_factory.h>
#include <opendaq/address_info_factory.h>
#include <regex>

BEGIN_NAMESPACE_OPENDAQ_WEBSOCKET_STREAMING_CLIENT_MODULE

static std::string WebsocketDeviceTypeId = "OpenDAQLTStreaming";
static std::string OldWebsocketDeviceTypeId = "OpenDAQLTStreamingOld";
static std::string WebsocketDevicePrefix = "daq.lt";
static std::string OldWebsocketDevicePrefix = "daq.ws";

static const std::regex RegexIpv6Hostname(R"(^(.+://)?(\[[a-fA-F0-9:]+(?:\%[a-zA-Z0-9_\.-~]+)?\])(?::(\d+))?(/.*)?$)");
static const std::regex RegexIpv4Hostname(R"(^(.+://)?([^:/\s]+)(?::(\d+))?(/.*)?$)");

using namespace discovery;
using namespace daq::websocket_streaming;

WebsocketStreamingClientModule::WebsocketStreamingClientModule(ContextPtr context)
    : Module("OpenDAQWebsocketClientModule",
            daq::VersionInfo(WS_STREAM_CL_MODULE_MAJOR_VERSION, WS_STREAM_CL_MODULE_MINOR_VERSION, WS_STREAM_CL_MODULE_PATCH_VERSION),
            std::move(context),
            "OpenDAQWebsocketClientModule")
    , deviceIndex(0)
    , discoveryClient(
        {"LT"}
    )
{
    discoveryClient.initMdnsClient(List<IString>("_streaming-lt._tcp.local.", "_streaming-ws._tcp.local."));
    loggerComponent = this->context.getLogger().getOrAddComponent("StreamingLTClient");
}

ListPtr<IDeviceInfo> WebsocketStreamingClientModule::onGetAvailableDevices()
{
    auto availableDevices = List<IDeviceInfo>();
    for (const auto& device : discoveryClient.discoverMdnsDevices())
        availableDevices.pushBack(populateDiscoveredDevice(device));
    return availableDevices;
}

DictPtr<IString, IDeviceType> WebsocketStreamingClientModule::onGetAvailableDeviceTypes()
{
    auto result = Dict<IString, IDeviceType>();

    const auto websocketDeviceType = createWebsocketDeviceType(false);
    const auto oldWebsocketDeviceType = createWebsocketDeviceType(true);

    result.set(websocketDeviceType.getId(), websocketDeviceType);
    result.set(oldWebsocketDeviceType.getId(), oldWebsocketDeviceType);

    return result;
}

DictPtr<IString, IStreamingType> WebsocketStreamingClientModule::onGetAvailableStreamingTypes()
{
    auto result = Dict<IString, IStreamingType>();

    auto websocketStreamingType = createWebsocketStreamingType();

    result.set(websocketStreamingType.getId(), websocketStreamingType);

    return result;
}

DevicePtr WebsocketStreamingClientModule::onCreateDevice(const StringPtr& connectionString,
                                                         const ComponentPtr& parent,
                                                         const PropertyObjectPtr& config)
{
    if (!connectionString.assigned())
        DAQ_THROW_EXCEPTION(ArgumentNullException);

    if (!acceptsConnectionParameters(connectionString, config))
        DAQ_THROW_EXCEPTION(InvalidParameterException);

    if (!context.assigned())
        DAQ_THROW_EXCEPTION(InvalidParameterException, "Context is not available.");

    // We don't create any streaming objects here since the
    // internal streaming object is always created within the device

    const StringPtr strPtr = formConnectionString(connectionString, config);
    const std::string str = strPtr;

    std::scoped_lock lock(sync);

    std::string localId = fmt::format("websocket_pseudo_device{}", deviceIndex++);
    auto device = WebsocketClientDevice(context, parent, localId, strPtr);

    // Set the connection info for the device
    auto host = String("");
    auto port = -1;
    {
        std::smatch match;

        bool parsed = false;
        parsed = std::regex_search(str, match, RegexIpv6Hostname);
        if (!parsed)
        {
            parsed = std::regex_search(str, match, RegexIpv4Hostname);
        }

        if (parsed)
        {
            host = match[2].str();
            port = 7414;
            if (match[3].matched)
                port = std::stoi(match[3]);
        }
    }

    // Set the connection info for the device
    ServerCapabilityConfigPtr connectionInfo = device.getInfo().getConfigurationConnectionInfo();
    connectionInfo.setProtocolId(WebsocketDeviceTypeId);
    connectionInfo.setProtocolName("OpenDAQLTStreaming");
    connectionInfo.setProtocolType(ProtocolType::Streaming);
    connectionInfo.setConnectionType("TCP/IP");
    connectionInfo.addAddress(host);
    connectionInfo.setPort(port);
    connectionInfo.setPrefix("daq.lt");
    connectionInfo.setConnectionString(strPtr);

    return device;
}

bool WebsocketStreamingClientModule::acceptsConnectionParameters(const StringPtr& connectionString, const PropertyObjectPtr& /*config*/)
{
    std::string connStr = connectionString;
    auto found = connStr.find(WebsocketDevicePrefix + "://") == 0 || connStr.find(OldWebsocketDevicePrefix + "://") == 0;
    return found;
}

bool WebsocketStreamingClientModule::acceptsStreamingConnectionParameters(const StringPtr& connectionString, const PropertyObjectPtr& config)
{
    if (connectionString.assigned() && connectionString != "")
    {
        return acceptsConnectionParameters(connectionString, config);
    }
    return false;
}

StreamingPtr WebsocketStreamingClientModule::onCreateStreaming(const StringPtr& connectionString, const PropertyObjectPtr& config)
{
    if (!connectionString.assigned())
        DAQ_THROW_EXCEPTION(ArgumentNullException);

    if (!acceptsStreamingConnectionParameters(connectionString, config))
        DAQ_THROW_EXCEPTION(InvalidParameterException);

    const StringPtr str = formConnectionString(connectionString, config);
    return WebsocketStreaming(str, context);
}

Bool WebsocketStreamingClientModule::onCompleteServerCapability(const ServerCapabilityPtr& source, const ServerCapabilityConfigPtr& target)
{
    if (target.getProtocolId() != "OpenDAQLTStreaming")
        return false;

    if (source.getConnectionType() != "TCP/IP")
        return false;

    if (!source.getAddresses().assigned() || !source.getAddresses().getCount())
    {
        LOG_W("Source server capability address is not available when filling in missing LT streaming capability information.")
        return false;
    }

    const auto addrInfos = source.getAddressInfo();
    if (!addrInfos.assigned() || !addrInfos.getCount())
    {
        LOG_W("Source server capability addressInfo is not available when filling in missing LT streaming capability information.")
        return false;
    }

    auto port = target.getPort();
    if (port == -1)
    {
        port = 7414;
        target.setPort(port);
        LOG_W("LT server capability is missing port. Defaulting to 7414.")
    }

    const auto path = target.hasProperty("Path") ? target.getPropertyValue("Path") : "";
    const auto targetAddress = target.getAddresses();
    for (const auto& addrInfo : addrInfos)
    {
        const auto address = addrInfo.getAddress();
        if (auto it = std::find(targetAddress.begin(), targetAddress.end(), address); it != targetAddress.end())
            continue;

        StringPtr connectionString;
        if (source.getPrefix() == target.getPrefix())
            connectionString = addrInfo.getConnectionString();
        else
            connectionString = createUrlConnectionString(address, port, path);
        const auto targetAddrInfo = AddressInfoBuilder()
                                        .setAddress(address)
                                        .setReachabilityStatus(addrInfo.getReachabilityStatus())
                                        .setType(addrInfo.getType())
                                        .setConnectionString(connectionString)
                                        .build();

        target.addAddressInfo(targetAddrInfo)
              .setConnectionString(connectionString)
              .addAddress(address);
    }

    return true;
}

StringPtr WebsocketStreamingClientModule::createUrlConnectionString(const StringPtr& host,
                                                                    const IntegerPtr& port,
                                                                    const StringPtr& path)
{
    return String(std::string(WebsocketDevicePrefix) + fmt::format("://{}:{}{}", host, port, path));
}

DeviceTypePtr WebsocketStreamingClientModule::createWebsocketDeviceType(bool useOldPrefix)
{
    const StringPtr prefix = useOldPrefix ? String(OldWebsocketDevicePrefix) : String(WebsocketDevicePrefix);
    const StringPtr id = useOldPrefix ? String(OldWebsocketDeviceTypeId) : String(WebsocketDeviceTypeId);

    return DeviceTypeBuilder()
        .setId(id)
        .setName("Streaming LT enabled pseudo-device")
        .setDescription("Pseudo device, provides only signals of the remote device as flat list")
        .setConnectionStringPrefix(prefix)
        .setDefaultConfig(createDefaultConfig())
        .build();
}

StreamingTypePtr WebsocketStreamingClientModule::createWebsocketStreamingType()
{
    return StreamingTypeBuilder()
        .setId(WebsocketDeviceTypeId)
        .setName("Streaming LT")
        .setDescription("openDAQ native streaming protocol client")
        .setConnectionStringPrefix("daq.lt")
        .setDefaultConfig(createDefaultConfig())
        .build();
}

PropertyObjectPtr WebsocketStreamingClientModule::createDefaultConfig()
{
    auto obj = PropertyObject();
    obj.addProperty(IntProperty("Port", 7414));
    return obj;
}

StringPtr WebsocketStreamingClientModule::formConnectionString(const StringPtr& connectionString, const PropertyObjectPtr& config)
{
    int port = 7414;   
    if (config.assigned() && config.hasProperty("Port"))
        port = config.getPropertyValue("Port");

    std::string urlString = connectionString.toStdString();
    std::smatch match;

    std::string host = "";
    std::string prefix = "";
    std::string path = "/";

    bool parsed = false;
    parsed = std::regex_search(urlString, match, RegexIpv6Hostname);
    if (!parsed)
    {
        parsed = std::regex_search(urlString, match, RegexIpv4Hostname);
    }

    if (parsed)
    {
        prefix = match[1];
        host = match[2];

        if (match[3].matched)
            port = std::stoi(match[3]);
        
        if (port == 7414)
            return connectionString;

        if (match[4].matched)
            path = match[4];

        return prefix + host + ":" + std::to_string(port) + path;
    }

    return connectionString;
}

DeviceInfoPtr WebsocketStreamingClientModule::populateDiscoveredDevice(const MdnsDiscoveredDevice& discoveredDevice)
{
    auto cap = ServerCapability(WebsocketDeviceTypeId, "OpenDAQLTStreaming", ProtocolType::Streaming);

    if (!discoveredDevice.ipv4Address.empty())
    {
        auto connectionStringIpv4 = WebsocketStreamingClientModule::createUrlConnectionString(
            discoveredDevice.ipv4Address,
            discoveredDevice.servicePort,
            discoveredDevice.getPropertyOrDefault("path", "/")
            );
        cap.addConnectionString(connectionStringIpv4);
        cap.addAddress(discoveredDevice.ipv4Address);
        const auto addressInfo = AddressInfoBuilder().setAddress(discoveredDevice.ipv4Address)
                                     .setReachabilityStatus(AddressReachabilityStatus::Unknown)
                                     .setType("IPv4")
                                     .setConnectionString(connectionStringIpv4)
                                     .build();
        cap.addAddressInfo(addressInfo);
    }

    if(!discoveredDevice.ipv6Address.empty())
    {
        auto connectionStringIpv6 = WebsocketStreamingClientModule::createUrlConnectionString(
            discoveredDevice.ipv6Address,
            discoveredDevice.servicePort,
            discoveredDevice.getPropertyOrDefault("path", "/")
            );
        cap.addConnectionString(connectionStringIpv6);
        cap.addAddress(discoveredDevice.ipv6Address);

        const auto addressInfo = AddressInfoBuilder().setAddress(discoveredDevice.ipv6Address)
                                     .setReachabilityStatus(AddressReachabilityStatus::Unknown)
                                     .setType("IPv6")
                                     .setConnectionString(connectionStringIpv6)
                                     .build();
        cap.addAddressInfo(addressInfo);
    }

    cap.setConnectionType("TCP/IP");
    cap.setPrefix("daq.lt");
    cap.setProtocolVersion(discoveredDevice.getPropertyOrDefault("protocolVersion", ""));
    if (discoveredDevice.servicePort > 0)
        cap.setPort(discoveredDevice.servicePort);

    return populateDiscoveredDeviceInfo(DiscoveryClient::populateDiscoveredInfoProperties, discoveredDevice, cap, createWebsocketDeviceType(false));
}

END_NAMESPACE_OPENDAQ_WEBSOCKET_STREAMING_CLIENT_MODULE
