/*
 * Copyright 2022-2025 openDAQ d.o.o.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <native_streaming_protocol/base_session_handler.h>

#include <opendaq/context_ptr.h>
#include <opendaq/signal_ptr.h>
#include <opendaq/client_type.h>

BEGIN_NAMESPACE_OPENDAQ_NATIVE_STREAMING_PROTOCOL

class ServerSessionHandler : public BaseSessionHandler
{
public:
    ServerSessionHandler(const ContextPtr& daqContext,
                         const std::shared_ptr<boost::asio::io_context>& ioContextPtr,
                         SessionPtr session,
                         const std::string& clientId,
                         OnFindSignalCallback findSignalHandler,
                         OnSignalSubscriptionCallback signalSubscriptionHandler,
                         native_streaming::OnSessionErrorCallback errorHandler,
                         SizeT streamingPacketSendTimeout);

    void sendSignalAvailable(const SignalNumericIdType& signalNumericId, const SignalPtr& signal);
    void sendSignalUnavailable(const SignalNumericIdType& signalNumericId, const SignalPtr& signal);
    void sendStreamingInitDone();
    void sendSubscribingDone(const SignalNumericIdType signalNumericId);
    void sendUnsubscribingDone(const SignalNumericIdType signalNumericId);

    void setTransportLayerPropsHandler(const OnTrasportLayerPropertiesCallback& transportLayerPropsHandler);
    void setStreamingInitHandler(const OnStreamingRequestCallback& streamingInitHandler);

    void setClientId(const std::string& clientId);
    std::string getClientId();

    void setClientHostName(const std::string& hostName);
    std::string getClientHostName();

    void setReconnected(bool reconnected);
    bool getReconnected();
    UserPtr getUser();
    void setClientType(ClientType clientType);
    ClientType getClientType();
    void setExclusiveControlDropOthers(bool enabled);
    bool isExclusiveControlDropOthersEnabled();

    bool isConfigProtocolUsed();
    void triggerUseConfigProtocol();

private:
    daq::native_streaming::ReadTask readHeader(const void* data, size_t size) override;
    daq::native_streaming::ReadTask readSignalSubscribe(const void* data, size_t size);
    daq::native_streaming::ReadTask readSignalUnsubscribe(const void* data, size_t size);
    daq::native_streaming::ReadTask readTransportLayerProperties(const void* data, size_t size);

    bool hasUserAccessToSignal(const SignalPtr& signal);

    OnStreamingRequestCallback streamingInitHandler;
    OnFindSignalCallback findSignalHandler;
    OnSignalSubscriptionCallback signalSubscriptionHandler;
    OnTrasportLayerPropertiesCallback transportLayerPropsHandler;

    std::string clientId;
    std::string clientHostName;
    bool reconnected;
    bool useConfigProtocol;
    ClientType clientType = ClientType::Control;
    bool exclusiveControlDropOthers = false;
};
END_NAMESPACE_OPENDAQ_NATIVE_STREAMING_PROTOCOL
