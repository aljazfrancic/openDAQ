//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CGenerator v0.7.0) on 03.06.2025 22:07:58.
// </auto-generated>
//------------------------------------------------------------------------------

#include <copendaq/streaming/mirrored_signal_private.h>

#include <opendaq/opendaq.h>

#include <copendaq_private.h>

const daqIntfID DAQ_MIRRORED_SIGNAL_PRIVATE_INTF_ID = { daq::IMirroredSignalPrivate::Id.Data1, daq::IMirroredSignalPrivate::Id.Data2, daq::IMirroredSignalPrivate::Id.Data3, daq::IMirroredSignalPrivate::Id.Data4_UInt64 };

daqErrCode daqMirroredSignalPrivate_triggerEvent(daqMirroredSignalPrivate* self, daqEventPacket* eventPacket, daqBool* forward)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->triggerEvent(reinterpret_cast<daq::IEventPacket*>(eventPacket), forward);
}

daqErrCode daqMirroredSignalPrivate_addStreamingSource(daqMirroredSignalPrivate* self, daqStreaming* streaming)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->addStreamingSource(reinterpret_cast<daq::IStreaming*>(streaming));
}

daqErrCode daqMirroredSignalPrivate_removeStreamingSource(daqMirroredSignalPrivate* self, daqString* streamingConnectionString)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->removeStreamingSource(reinterpret_cast<daq::IString*>(streamingConnectionString));
}

daqErrCode daqMirroredSignalPrivate_subscribeCompleted(daqMirroredSignalPrivate* self, daqString* streamingConnectionString)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->subscribeCompleted(reinterpret_cast<daq::IString*>(streamingConnectionString));
}

daqErrCode daqMirroredSignalPrivate_unsubscribeCompleted(daqMirroredSignalPrivate* self, daqString* streamingConnectionString)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->unsubscribeCompleted(reinterpret_cast<daq::IString*>(streamingConnectionString));
}

daqErrCode daqMirroredSignalPrivate_unsubscribeCompletedNoLock(daqMirroredSignalPrivate* self, daqString* streamingConnectionString)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->unsubscribeCompletedNoLock(reinterpret_cast<daq::IString*>(streamingConnectionString));
}

daqErrCode daqMirroredSignalPrivate_getMirroredDataDescriptor(daqMirroredSignalPrivate* self, daqDataDescriptor** descriptor)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->getMirroredDataDescriptor(reinterpret_cast<daq::IDataDescriptor**>(descriptor));
}

daqErrCode daqMirroredSignalPrivate_setMirroredDataDescriptor(daqMirroredSignalPrivate* self, daqDataDescriptor* descriptor)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->setMirroredDataDescriptor(reinterpret_cast<daq::IDataDescriptor*>(descriptor));
}

daqErrCode daqMirroredSignalPrivate_getMirroredDomainSignal(daqMirroredSignalPrivate* self, daqMirroredSignalConfig** domainSignals)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->getMirroredDomainSignal(reinterpret_cast<daq::IMirroredSignalConfig**>(domainSignals));
}

daqErrCode daqMirroredSignalPrivate_setMirroredDomainSignal(daqMirroredSignalPrivate* self, daqMirroredSignalConfig* domainSignal)
{
    return reinterpret_cast<daq::IMirroredSignalPrivate*>(self)->setMirroredDomainSignal(reinterpret_cast<daq::IMirroredSignalConfig*>(domainSignal));
}
