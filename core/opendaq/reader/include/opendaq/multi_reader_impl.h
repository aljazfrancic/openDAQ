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
#include <opendaq/multi_reader.h>
#include <opendaq/read_info.h>
#include <opendaq/reader_config_ptr.h>
#include <opendaq/signal_reader.h>
#include <coreobjects/property_object_factory.h>
#include <opendaq/multi_reader_builder_ptr.h>
#include <opendaq/reader_factory.h>

BEGIN_NAMESPACE_OPENDAQ

class MultiReaderImpl : public ImplementationOfWeak<IMultiReader, IReaderConfig, IInputPortNotifications>
{
public:
    MultiReaderImpl(const ListPtr<IComponent>& list,
                    SampleType valueReadType,
                    SampleType domainReadType,
                    ReadMode mode,
                    ReadTimeoutType timeoutType,
                    Int requiredCommonSampleRate = -1,
                    Bool startOnFullUnitOfDomain = false,
                    SizeT minReadCount = 1);

    MultiReaderImpl(MultiReaderImpl* old,
                    SampleType valueReadType,
                    SampleType domainReadType);

    MultiReaderImpl(const ReaderConfigPtr& readerConfig,
                    SampleType valueReadType,
                    SampleType domainReadType,
                    ReadMode mode);

    MultiReaderImpl(const MultiReaderBuilderPtr& builder);

    ~MultiReaderImpl() override;

    ErrCode INTERFACE_FUNC setOnDataAvailable(IProcedure* callback) override;
    ErrCode INTERFACE_FUNC getValueReadType(SampleType* sampleType) override;
    ErrCode INTERFACE_FUNC getDomainReadType(SampleType* sampleType) override;
    ErrCode INTERFACE_FUNC setValueTransformFunction(IFunction* transform) override;
    ErrCode INTERFACE_FUNC setDomainTransformFunction(IFunction* transform) override;
    ErrCode INTERFACE_FUNC getReadMode(ReadMode* mode) override;
    ErrCode INTERFACE_FUNC getEmpty(Bool* empty) override;

    ErrCode INTERFACE_FUNC getAvailableCount(SizeT* count) override;
    ErrCode INTERFACE_FUNC read(void* samples, SizeT* count, SizeT timeoutMs, IMultiReaderStatus** status) override;
    ErrCode INTERFACE_FUNC readWithDomain(void* samples, void* domain, SizeT* count, SizeT timeoutMs, IMultiReaderStatus** status) override;
    ErrCode INTERFACE_FUNC skipSamples(SizeT* count, IMultiReaderStatus** status) override;

    // IInputPortNotifications
    ErrCode INTERFACE_FUNC acceptsSignal(IInputPort* port, ISignal* signal, Bool* accept) override;
    ErrCode INTERFACE_FUNC connected(IInputPort* port) override;
    ErrCode INTERFACE_FUNC disconnected(IInputPort* port) override;
    ErrCode INTERFACE_FUNC packetReceived(IInputPort* inputPort) override;

    // IReaderConfig
    ErrCode INTERFACE_FUNC getValueTransformFunction(IFunction** transform) override;
    ErrCode INTERFACE_FUNC getDomainTransformFunction(IFunction** transform) override;
    ErrCode INTERFACE_FUNC getInputPorts(IList** ports) override;
    ErrCode INTERFACE_FUNC getReadTimeoutType(ReadTimeoutType* timeoutType) override;
    ErrCode INTERFACE_FUNC markAsInvalid() override;

    ErrCode INTERFACE_FUNC getTickResolution(IRatio** resolution) override;
    ErrCode INTERFACE_FUNC getOrigin(IString** origin) override;
    ErrCode INTERFACE_FUNC getOffset(void* domainStart) override;
    ErrCode INTERFACE_FUNC getCommonSampleRate(Int* commonSampleRate) override;

    ErrCode INTERFACE_FUNC getIsSynchronized(Bool* isSynchronized) override;

    ErrCode INTERFACE_FUNC setActive(Bool isActive) override;
    ErrCode INTERFACE_FUNC getActive(Bool* isActive) override;

private:
    using Clock = std::chrono::steady_clock;
    using Duration = Clock::duration;

    ListPtr<IInputPortConfig> checkPreconditions(const ListPtr<IComponent>& list, bool overrideMethod, bool& fromInputPorts);
    void updateCommonSampleRateAndDividers();
    ListPtr<ISignal> getSignals() const;

    void setStartInfo();
    void connectPorts(const ListPtr<IInputPortConfig>& inputPorts, 
                      SampleType valueRead, 
                      SampleType domainRead, 
                      ReadMode mode,
                      bool fromInputPorts);
    SizeT getMinSamplesAvailable(bool acrossDescriptorChanges = false) const;
    DictPtr<IString, IEventPacket> readUntilFirstDataPacket();
    ErrCode synchronize(SizeT& min, SyncStatus& syncStatus);
    bool hasEventOrGapInQueue();

    SyncStatus getSyncStatus() const;

    MultiReaderStatusPtr readPackets();

    void prepare(void** outValues, SizeT count, std::chrono::milliseconds timeoutTime);
    void prepareWithDomain(void** outValues, void** domain, SizeT count, std::chrono::milliseconds timeoutTime);

    [[nodiscard]] Duration durationFromStart() const;
    void readSamples(SizeT samples);

    void readSamplesAndSetRemainingSamples(SizeT samples);

    void readDomainStart();
    void sync();

    void setActiveInternal(Bool isActive);

    MultiReaderStatusPtr createReaderStatus(const DictPtr<IString, IEventPacket>& eventPackets = nullptr, const NumberPtr& offset = nullptr);

    std::mutex mutex;
    bool invalid{false};
    std::string errorMessage;

    SizeT remainingSamplesToRead{};

    void** values{};
    void** domainValues{};

    Clock::duration timeout{};
    Clock::time_point startTime;

    StringPtr readOrigin;
    RatioPtr readResolution;
    RatioPtr tickOffsetTolerance;
    std::unique_ptr<Comparable> commonStart;
    std::int64_t requiredCommonSampleRate = -1;
    std::int64_t commonSampleRate = -1;
    std::int32_t sampleRateDividerLcm = 1;
    bool sameSampleRates = false;

    std::vector<SignalReader> signals;
    PropertyObjectPtr portBinder;
    ProcedurePtr readCallback;

    LoggerComponentPtr loggerComponent;

    bool startOnFullUnitOfDomain;

    NotifyInfo notify{};
    bool portConnected{};
    bool portDisconnected{};

    DataDescriptorPtr mainValueDescriptor;
    DataDescriptorPtr mainDomainDescriptor;

    void isDomainValid(const ListPtr<IInputPortConfig>& list);
    void checkEarlyPreconditionsAndCacheContext(const ListPtr<IComponent>& list);

    ContextPtr context;
    struct ReferenceDomainBin;
    bool isActive{true};

    SizeT minReadCount;
};

END_NAMESPACE_OPENDAQ
