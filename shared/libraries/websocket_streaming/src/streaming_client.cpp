#include "websocket_streaming/streaming_client.h"
#include <websocket_streaming/signal_descriptor_converter.h>
#include <regex>
#include <streaming_protocol/Logging.hpp>
#include <streaming_protocol/ProtocolHandler.hpp>
#include "stream/WebsocketClientStream.hpp"
#include "stream/TcpClientStream.hpp"
#include "streaming_protocol/SignalContainer.hpp"
#include "opendaq/custom_log.h"
#include <opendaq/packet_factory.h>

BEGIN_NAMESPACE_OPENDAQ_WEBSOCKET_STREAMING

using namespace daq::stream;
using namespace daq::streaming_protocol;

// parsing connection string to four groups: prefix, host, port, path
static const std::regex RegexIpv6Hostname(R"(^(.+://)?(?:\[([a-fA-F0-9:]+(?:\%[a-zA-Z0-9_\.-~]+)?)\])(?::(\d+))?(/.*)?$)");
static const std::regex RegexIpv4Hostname(R"(^(.+://)?([^:/\s]+)(?::(\d+))?(/.*)?$)");

StreamingClient::StreamingClient(const ContextPtr& context, const std::string& connectionString, bool useRawTcpConnection)
    : context(context)
    , logger(context.getLogger())
    , loggerComponent( logger.assigned() ? logger.getOrAddComponent("StreamingClient") : throw ArgumentNullException("Logger must not be null") )
    , logCallback( [this](spdlog::source_loc location, spdlog::level::level_enum level, const char* msg) {
        this->loggerComponent.logMessage(SourceLocation{location.filename, location.line, location.funcname}, msg, static_cast<LogLevel>(level));
    })
    , signalContainer(logCallback)
    , useRawTcpConnection(useRawTcpConnection)
{
    parseConnectionString(connectionString);
    startBackgroundContext();
}

StreamingClient::StreamingClient(const ContextPtr& context, const std::string& host, uint16_t port, const std::string& target, bool useRawTcpConnection)
    : logger(context.getLogger())
    , loggerComponent( logger.assigned() ? logger.getOrAddComponent("StreamingClient") : throw ArgumentNullException("Logger must not be null") )
    , logCallback( [this](spdlog::source_loc location, spdlog::level::level_enum level, const char* msg) {
        this->loggerComponent.logMessage(SourceLocation{location.filename, location.line, location.funcname}, msg, static_cast<LogLevel>(level));
    })
    , host(host)
    , port(port)
    , target(target)
    , signalContainer(logCallback)
    , useRawTcpConnection(useRawTcpConnection)
{
    startBackgroundContext();
}

void daq::websocket_streaming::StreamingClient::startBackgroundContext()
{
    clientBackgroundThread = std::thread(
        [this]()
        {
            using namespace boost::asio;
            executor_work_guard<io_context::executor_type> workGuard(backgroundContext.get_executor());
            backgroundContext.run();
        }
    );
}

void StreamingClient::stopBackgroundContext()
{
    backgroundContext.stop();
    if (clientBackgroundThread.get_id() != std::this_thread::get_id())
    {
        if (clientBackgroundThread.joinable())
        {
            clientBackgroundThread.join();
            LOG_I("Websocket streaming client background thread joined");
        }
        else
        {
            LOG_W("Websocket streaming client background thread is not joinable");
        }
    }
    else
    {
        LOG_C("Websocket streaming client background thread cannot join itself");
    }
}

StreamingClient::~StreamingClient()
{
    disconnect();
    stopBackgroundContext();
}

bool StreamingClient::connect()
{
    if (connected)
        return true;
    if (host.empty() || port == 0)
        return false;

    connected = false;

    auto signalMetaCallback = [this](const SubscribedSignal& subscribedSignal, const std::string& method, const nlohmann::json& params)
    { onSignalMeta(subscribedSignal, method, params); };

    auto protocolMetaCallback = [this](ProtocolHandler& protocolHandler, const std::string& method, const nlohmann::json& params)
    { onProtocolMeta(protocolHandler, method, params); };

    auto messageCallback = [this](const SubscribedSignal& subscribedSignal, uint64_t timeStamp, const uint8_t* data, size_t valueCount)
    { onMessage(subscribedSignal, timeStamp, data, valueCount); };

    signalContainer.setSignalMetaCb(signalMetaCallback);
    signalContainer.setDataAsValueCb(messageCallback);

    std::unique_ptr<Stream> clientStream;
    if (useRawTcpConnection)
        clientStream = std::make_unique<TcpClientStream>(ioContext, host, std::to_string(port));
    else
        clientStream = std::make_unique<WebsocketClientStream>(ioContext, host, std::to_string(port), target);

    protocolHandler = std::make_shared<ProtocolHandler>(ioContext, signalContainer, protocolMetaCallback, logCallback);

    std::unique_lock<std::mutex> lock(clientMutex);
    protocolHandler->startWithSyncInit(std::move(clientStream));

    ioContext.restart();
    clientIoThread = std::thread([this]() { ioContext.run(); });

    conditionVariable.wait_for(lock, connectTimeout, [this]() { return connected; });

    if (connected)
        checkTmpSubscribedSignalsInit();

    return connected;
}

void StreamingClient::disconnect()
{
    ioContext.stop();
    if (clientIoThread.get_id() != std::this_thread::get_id())
    {
        if (clientIoThread.joinable())
        {
            clientIoThread.join();
            LOG_I("Websocket streaming client IO thread joined");
        }
        else
        {
            LOG_W("Websocket streaming client IO thread is not joinable");
        }
    }
    else
    {
        LOG_C("Websocket streaming client IO thread cannot join itself");
    }

    connected = false;
}

void StreamingClient::onPacket(const OnPacketCallback& callack)
{
    onPacketCallback = callack;
}

void StreamingClient::onDeviceAvailableSignalInit(const OnSignalCallback& callback)
{
    onAvailableSignalInitCb = callback;
}

void StreamingClient::onDeviceSignalUpdated(const OnSignalCallback& callback)
{
    onSignalUpdatedCallback = callback;
}

void StreamingClient::onDeviceDomainSingalInit(const OnDomainSignalInitCallback& callback)
{
    onDomainSignalInitCallback = callback;
}

void StreamingClient::onStreamingAvailableSignals(const OnAvailableSignalsCallback& callback)
{
    onAvailableStreamingSignalsCb = callback;
}

void StreamingClient::onDeviceAvailableSignals(const OnAvailableSignalsCallback& callback)
{
    onAvailableDeviceSignalsCb = callback;
}

void StreamingClient::onStreamingUnavailableSignals(const OnAvailableSignalsCallback& callback)
{
    onUnavailableStreamingSignalsCb = callback;
}

void StreamingClient::onDeviceUnavailableSignals(const OnAvailableSignalsCallback& callback)
{
    onUnavailableDeviceSignalsCb = callback;
}

void StreamingClient::onStreamingHiddenSignal(const OnSignalCallback& callback)
{
    onHiddenStreamingSignalCb = callback;
}

void StreamingClient::onDeviceHiddenSignal(const OnSignalCallback& callback)
{
    onHiddenDeviceSignalInitCb = callback;
}

void StreamingClient::onDeviceSignalsInitDone(const OnSignalsInitDoneCallback& callback)
{
    onSignalsInitDone = callback;
}

void StreamingClient::onSubscriptionAck(const OnSubsciptionAckCallback& callback)
{
    onSubscriptionAckCallback = callback;
}

std::string StreamingClient::getHost()
{
    return host;
}

uint16_t StreamingClient::getPort()
{
    return port;
}

std::string StreamingClient::getTarget()
{
    return target;
}

bool StreamingClient::isConnected()
{
    return connected;
}

void StreamingClient::setConnectTimeout(std::chrono::milliseconds timeout)
{
    this->connectTimeout = timeout;
}

void StreamingClient::parseConnectionString(const std::string& url)
{
    // this is not great but it is convenient until we have a way to pass configuration parameters to a client device

    host = "";
    port = 7414;
    target = "/";

    std::smatch match;

    bool parsed = false;
    parsed = std::regex_search(url, match, RegexIpv6Hostname);
    if (!parsed)
        parsed = std::regex_search(url, match, RegexIpv4Hostname);

    if (parsed)
    {
        host = match[2];
        if (match[3].matched)
            port = std::stoi(match[3]);
        if (match[4].matched)
            target = match[4];
    }
}

void StreamingClient::onSignalMeta(const SubscribedSignal& subscribedSignal, const std::string& method, const nlohmann::json& params)
{
    if (method == daq::streaming_protocol::META_METHOD_SIGNAL)
        onSignal(subscribedSignal, params);

    std::string signalId = subscribedSignal.signalId();

    // triggers ack only for available signals, but not for hidden ones
    if (method == daq::streaming_protocol::META_METHOD_SUBSCRIBE)
    {
        if (auto it = availableSignals.find(signalId); it != availableSignals.end())
        {
            auto inputSignal = it->second;
            // forwards ACK to upper level only if signal is explicitly subscribed
            // and doesn't if just temporary subscribed for descriptors initialization
            // i.e. skips the first subscribe ACK from server if signal is not explicitly subscribed by streaming
            if (inputSignal && inputSignal->getSubscribed())
            {
                // ignores ACKs for domain signals
                if (!inputSignal->isDomainSignal())
                    onSubscriptionAckCallback(subscribedSignal.signalId(), true);
            }
        }
    }
    else if (method == daq::streaming_protocol::META_METHOD_UNSUBSCRIBE)
    {
        if (auto it = availableSigInitStatus.find(signalId); it != availableSigInitStatus.end())
        {
            // skips the first unsubscribe ACK from server
            if (std::get<2>(it->second))
            {
                // ignores ACKs for domain signals
                if (!subscribedSignal.isTimeSignal())
                    onSubscriptionAckCallback(subscribedSignal.signalId(), false);
            }
            else
            {
                std::get<2>(it->second) = true;
            }
        }
    }
}

void StreamingClient::onProtocolMeta(daq::streaming_protocol::ProtocolHandler& protocolHandler,
                                     const std::string& method,
                                     const nlohmann::json& params)
{
    if (method == daq::streaming_protocol::META_METHOD_AVAILABLE)
    {
        auto availableSignalsArray = params.find(META_SIGNALIDS);
        if (availableSignalsArray != params.end() && availableSignalsArray->is_array())
        {
            availableSignalsHandler(availableSignalsArray);
        }
    }
    else if (method == daq::streaming_protocol::META_METHOD_UNAVAILABLE)
    {
        auto unavailableSignalsArray = params.find(META_SIGNALIDS);
        if (unavailableSignalsArray != params.end() && unavailableSignalsArray->is_array())
        {
            unavailableSignalsHandler(unavailableSignalsArray);
        }
    }
}

void StreamingClient::availableSignalsHandler(const nlohmann::json::const_iterator& availableSignalsArray)
{
    std::vector<std::string> signalIds;
    for (const auto& arrayItem : *availableSignalsArray)
    {
        std::string signalId = arrayItem;
        signalIds.push_back(signalId);

        if (auto signalIt = availableSignals.find(signalId); signalIt == availableSignals.end())
        {
            availableSignals.insert({signalId, InputPlaceHolderSignal(signalId, logCallback)});
        }
        else
        {
            LOG_E("Received duplicate of available signal. ID is {}.", signalId);
        }
    }

    onAvailableDeviceSignalsCb(signalIds);
    onAvailableStreamingSignalsCb(signalIds);

    std::unique_lock<std::mutex> lock(clientMutex);

    for (const auto& signalId : signalIds)
    {
        tmpSubscribedSignalIds.insert(signalId);

        std::promise<void> signalInitPromise;
        std::future<void> signalInitFuture = signalInitPromise.get_future();
        availableSigInitStatus.insert_or_assign(
            signalId,
            std::make_tuple(
                std::move(signalInitPromise),
                std::move(signalInitFuture),
                false
            )
        );
    }

    // signal meta-information (signal description, tableId, related signals, etc.)
    // is published only for subscribed signals.
    // as workaround we temporarily subscribe all signals to receive signal meta-info
    // and initialize signal descriptors
    this->protocolHandler->subscribe(signalIds);

    if (connected)
    {
        // wait for signals initialization done in a separate thread
        backgroundContext.dispatch(
            [this]()
            {
                std::unique_lock<std::mutex> lock(clientMutex);
                checkTmpSubscribedSignalsInit();
            }
        );
    }
    else
    {
        connected = true;
        conditionVariable.notify_all();
    }
}

void StreamingClient::unavailableSignalsHandler(const nlohmann::json::const_iterator& unavailableSignalsArray)
{
    std::vector<std::string> signalIds;
    for (const auto& arrayItem : *unavailableSignalsArray)
    {
        std::string signalId = arrayItem;

        if (auto signalIt = availableSignals.find(signalId); signalIt != availableSignals.end())
        {
            availableSignals.erase(signalIt);
        }
        else
        {
            LOG_E("Received unavailable signal which were not available before. ID is {}.", signalId);
        }

        signalIds.push_back(signalId);
    }

    onUnavailableStreamingSignalsCb(signalIds);
    onUnavailableDeviceSignalsCb(signalIds);
}

void StreamingClient::subscribeSignal(const std::string& signalId)
{
    if (auto it = availableSignals.find(signalId); it != availableSignals.end())
    {
        if (auto inputSignal = it->second)
            inputSignal->setSubscribed(true);
        protocolHandler->subscribe({signalId});
    }
}

void StreamingClient::unsubscribeSignal(const std::string& signalId)
{
    if (auto it = availableSignals.find(signalId); it != availableSignals.end())
    {
        if (auto inputSignal = it->second)
            inputSignal->setSubscribed(false);
        protocolHandler->unsubscribe({signalId});
    }
}

void StreamingClient::onMessage(const daq::streaming_protocol::SubscribedSignal& subscribedSignal,
                                uint64_t timeStamp,
                                const uint8_t* data,
                                size_t valueCount)
{
    std::string id = subscribedSignal.signalId();
    std::size_t dataSize = subscribedSignal.dataValueSize() * valueCount;

    NumberPtr domainValue = static_cast<Int>(timeStamp);
    InputSignalBasePtr inputSignal = nullptr;

    if (auto availableSigIt = availableSignals.find(id); availableSigIt != availableSignals.end())
        inputSignal = availableSigIt->second;
    else if (auto hiddenSigIt = hiddenSignals.find(id); hiddenSigIt != hiddenSignals.end())
        inputSignal = hiddenSigIt->second;

    if (inputSignal &&
        !isPlaceHolderSignal(inputSignal) &&
        inputSignal->hasDescriptors())
    {
        if (inputSignal->isCountable())
        {
            DataPacketPtr domainPacket;
            if (inputSignal->isDomainSignal())
            {
                domainPacket = inputSignal->generateDataPacket(domainValue, data, dataSize, valueCount, nullptr);
                inputSignal->setLastPacket(domainPacket);
                if (domainPacket.assigned())
                    onPacketCallback(id, domainPacket);
            }
            else
            {
                // If the domain signal is linear-rule, we artificially generate a packet here
                // using the timestamp reported by streaming-protocol-lt. If the domain signal
                // is explicit-rule, we must (by requirement) already have received and cached
                // the domain packet above, and we use that instead.
                DataRuleType domainRuleType = DataRuleType::Other;
                auto domainSignal = inputSignal->getInputDomainSignal();
                if (domainSignal)
                    if (auto domainDescriptor = domainSignal->getSignalDescriptor(); domainDescriptor.assigned())
                        if (auto domainRule = domainDescriptor.getRule(); domainRule.assigned())
                            domainRuleType = domainRule.getType();
                if (domainRuleType == DataRuleType::Explicit)
                {
                    domainPacket = inputSignal->getInputDomainSignal()->getLastPacket();
                }
                else
                {
                    domainPacket =
                        inputSignal->getInputDomainSignal()->generateDataPacket(domainValue, data, dataSize, valueCount, nullptr);
                    if (domainPacket.assigned())
                        onPacketCallback(inputSignal->getInputDomainSignal()->getSignalId(), domainPacket);
                }

                auto packet = inputSignal->generateDataPacket(domainValue, data, dataSize, valueCount, domainPacket);
                inputSignal->setLastPacket(packet);
                if (packet.assigned())
                    onPacketCallback(id, packet);
            }

            auto relatedDataSignals = findDataSignalsByTableId(inputSignal->getTableId());

            // trigger packet generation for each related signal which is not countable (is implicit)
            for (auto& relatedSignal : relatedDataSignals)
            {
                if (!relatedSignal->isCountable())
                {
                    auto packet = relatedSignal->generateDataPacket(domainValue, nullptr, 0, valueCount, domainPacket);
                    if (packet.assigned() && relatedSignal->getSubscribed())
                        onPacketCallback(relatedSignal->getSignalId(), packet);
                }
            }
        }
        else
        {
            inputSignal->processSamples(domainValue, data, valueCount);
        }
    }
}

void StreamingClient::setDataSignal(
    const daq::streaming_protocol::SubscribedSignal& subscribedSignal,
    const daq::ContextPtr& context)
{
    auto sInfo = SignalDescriptorConverter::ToDataDescriptor(subscribedSignal, context);
    const auto signalId = subscribedSignal.signalId();
    const auto tableId = subscribedSignal.tableId();
    bool available = false;

    auto domainInputSignal = findTimeSignalByTableId(tableId);
    if (!domainInputSignal)
        DAQ_THROW_EXCEPTION(NotFoundException, "Unknown domain signal for data signal {}, table {}", signalId, tableId);

    InputSignalBasePtr inputSignal = nullptr;
    if (auto availableSigIt = availableSignals.find(signalId); availableSigIt != availableSignals.end())
    {
        inputSignal = availableSigIt->second;
        available = true;
    }
    else if (auto hiddenSigIt = hiddenSignals.find(signalId); hiddenSigIt != hiddenSignals.end())
    {
        inputSignal = hiddenSigIt->second;
        available = false;
    }

    if (!inputSignal && !available)
    {
        inputSignal = InputSignal(signalId, tableId, sInfo, false, domainInputSignal, logCallback, subscribedSignal.constRuleStartMeta());
        hiddenSignals.insert({signalId, inputSignal});
        onHiddenStreamingSignalCb(signalId, sInfo);
        onHiddenDeviceSignalInitCb(signalId, sInfo);
        onDomainSignalInitCallback(signalId, domainInputSignal->getSignalId());
        publishSignalChanges(inputSignal, true, true);
    }
    else if (available && isPlaceHolderSignal(inputSignal))
    {
        bool subscribed = inputSignal->getSubscribed();
        inputSignal = InputSignal(signalId, tableId, sInfo, false, domainInputSignal, logCallback, subscribedSignal.constRuleStartMeta());
        inputSignal->setSubscribed(subscribed);
        availableSignals[signalId] = inputSignal;
        onAvailableSignalInitCb(signalId, sInfo);
        onDomainSignalInitCallback(signalId, domainInputSignal->getSignalId());
        setSignalInitSatisfied(signalId);
        publishSignalChanges(inputSignal, true, true);
    }
    else
    {
        if (sInfo.dataDescriptor != inputSignal->getSignalDescriptor())
        {
            inputSignal->setDataDescriptor(sInfo.dataDescriptor);
            publishSignalChanges(inputSignal, true, false);
        }
        onSignalUpdatedCallback(signalId, sInfo);
    }
}

void StreamingClient::setTimeSignal(
    const daq::streaming_protocol::SubscribedSignal& subscribedSignal,
    const daq::ContextPtr& context)
{
    auto sInfo = SignalDescriptorConverter::ToDataDescriptor(subscribedSignal, context);
    const std::string tableId = subscribedSignal.tableId();
    const std::string timeSignalId = subscribedSignal.signalId();
    bool available = false;

    InputSignalBasePtr inputSignal = nullptr;
    if (auto availableSigIt = availableSignals.find(timeSignalId); availableSigIt != availableSignals.end())
    {
        inputSignal = availableSigIt->second;
        available = true;
    }
    else if (auto hiddenSigIt = hiddenSignals.find(timeSignalId); hiddenSigIt != hiddenSignals.end())
    {
        inputSignal = hiddenSigIt->second;
        available = false;
    }

    if (!inputSignal && !available)
    {
        // the time signal was not published as available by server, add as hidden
        inputSignal = InputSignal(timeSignalId, tableId, sInfo, true, nullptr, logCallback, subscribedSignal.constRuleStartMeta());
        hiddenSignals.insert({timeSignalId, inputSignal});
        onHiddenStreamingSignalCb(timeSignalId, sInfo);
        onHiddenDeviceSignalInitCb(timeSignalId, sInfo);
    }
    else if (available && isPlaceHolderSignal(inputSignal))
    {
        bool subscribed = inputSignal->getSubscribed();
        inputSignal = InputSignal(timeSignalId, tableId, sInfo, true, nullptr, logCallback, subscribedSignal.constRuleStartMeta());
        inputSignal->setSubscribed(subscribed);
        availableSignals[timeSignalId] = inputSignal;
        // the time signal is published as available by server,
        // so do the initialization of its mirrored copy
        onAvailableSignalInitCb(timeSignalId, sInfo);
        setSignalInitSatisfied(timeSignalId);
    }
    else
    {
        if (sInfo.dataDescriptor != inputSignal->getSignalDescriptor())
        {
            inputSignal->setDataDescriptor(sInfo.dataDescriptor);

            // publish new domain descriptor for all input data signals with known tableId
            for (const auto& inputDataSignal : findDataSignalsByTableId(tableId))
            {
                publishSignalChanges(inputDataSignal, false, true);
            }
        }
        if (auto constRuleSignal = std::dynamic_pointer_cast<InputConstantDataSignal>(inputSignal))
        {
            constRuleSignal->updateStartValue(subscribedSignal.constRuleStartMeta());
        }
        onSignalUpdatedCallback(timeSignalId, sInfo);
    }
}

void StreamingClient::publishSignalChanges(const InputSignalBasePtr& signal, bool valueChanged, bool domainChanged)
{
    // signal meta information is always received by pairs of META_METHOD_SIGNAL:
    // one is meta for data signal, another is meta for time signal.
    // we generate event packet only after both meta are received
    // and all signal descriptors are assigned.
    if (!signal->hasDescriptors())
        return;

    auto eventPacket = signal->createDecriptorChangedPacket(valueChanged, domainChanged);
    onPacketCallback(signal->getSignalId(), eventPacket);
}

std::vector<InputSignalBasePtr> StreamingClient::findDataSignalsByTableId(const std::string& tableId)
{
    std::vector<InputSignalBasePtr> result;
    for (const auto& [_, inputSignal] : availableSignals)
    {
        if (inputSignal && !isPlaceHolderSignal(inputSignal) && tableId == inputSignal->getTableId() && !inputSignal->isDomainSignal())
        {
            result.push_back(inputSignal);
        }
    }
    for (const auto& [_, inputSignal] : hiddenSignals)
    {
        if (inputSignal && !isPlaceHolderSignal(inputSignal) && tableId == inputSignal->getTableId() && !inputSignal->isDomainSignal())
        {
            result.push_back(inputSignal);
        }
    }
    return result;
}

InputSignalBasePtr StreamingClient::findTimeSignalByTableId(const std::string& tableId)
{
    std::vector<std::pair<std::string, InputSignalPtr>> result;
    for (const auto& [_, inputSignal] : availableSignals)
    {
        if (inputSignal && tableId == inputSignal->getTableId() && inputSignal->isDomainSignal())
        {
            return inputSignal;
        }
    }
    for (const auto& [_, inputSignal] : hiddenSignals)
    {
        if (inputSignal && tableId == inputSignal->getTableId() && inputSignal->isDomainSignal())
        {
            return inputSignal;
        }
    }
    return nullptr;
}

void StreamingClient::onSignal(const daq::streaming_protocol::SubscribedSignal& subscribedSignal, const nlohmann::json& params)
{
    try
    {
        {
            LOG_I("Signal #{}; signalId {}; tableId {}; name {}; value type {}; Json parameters: \n\n{}\n",
                  subscribedSignal.signalNumber(),
                  subscribedSignal.signalId(),
                  subscribedSignal.tableId(),
                  subscribedSignal.memberName(),
                  static_cast<int>(subscribedSignal.dataValueType()),
                  params.dump());
        }

        if (subscribedSignal.isTimeSignal())
        {
            setTimeSignal(subscribedSignal, context);
        }
        else
        {
            setDataSignal(subscribedSignal, context);
        }
    }
    catch (const DaqException& e)
    {
        LOG_W("Failed to interpret received input signal: {}.", e.what());        
    }
}

void StreamingClient::setSignalInitSatisfied(const std::string& signalId)
{
    if (auto iterator = availableSigInitStatus.find(signalId); iterator != availableSigInitStatus.end())
    {
        try
        {
            std::get<0>(iterator->second).set_value();
        }
        catch (std::future_error& e)
        {
            if (e.code() == std::make_error_code(std::future_errc::promise_already_satisfied))
            {
                LOG_D("signal {} is already initialized", signalId);
            }
            else
            {
                LOG_E("signal {} initialization error {}", signalId, e.what());
            }
        }
    }
}

void StreamingClient::checkTmpSubscribedSignalsInit()
{
    if (tmpSubscribedSignalIds.empty())
        return;

    const auto timeout = std::chrono::seconds(1);
    auto timeoutExpired = std::chrono::system_clock::now() + timeout;

    for (const auto& [id, params] : availableSigInitStatus)
    {
        if (tmpSubscribedSignalIds.count(id) != 0)
        {
            auto status = std::get<1>(params).wait_until(timeoutExpired);
            if (status != std::future_status::ready)
            {
                LOG_W("signal {} has incomplete descriptors", id);

                // publish signal descriptor changes as event packet if signal is subscribed by streaming
                if (auto availableSigIt = availableSignals.find(id); availableSigIt != availableSignals.end())
                {
                    auto inputSignal = availableSigIt->second;
                    publishSignalChanges(inputSignal, true, true);
                }
            }
        }
    }

    // unsubscribe previously subscribed signals
    std::vector<std::string> signalIdsToUnsubscribe;
    signalIdsToUnsubscribe.reserve(tmpSubscribedSignalIds.size());
    std::copy_if(
        tmpSubscribedSignalIds.begin(),
        tmpSubscribedSignalIds.end(),
        std::back_inserter(signalIdsToUnsubscribe),
        [this](std::string signalId)
        {
            if (auto availableSigIt = availableSignals.find(signalId); availableSigIt != availableSignals.end())
            {
                if (auto inputSignal = availableSigIt->second; inputSignal && inputSignal->getSubscribed())
                    return false;
            }
            return true;
        }
    );
    protocolHandler->unsubscribe(signalIdsToUnsubscribe);
    tmpSubscribedSignalIds.clear();

    onSignalsInitDone();
}

END_NAMESPACE_OPENDAQ_WEBSOCKET_STREAMING
