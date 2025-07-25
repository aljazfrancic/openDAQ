//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CGenerator v0.7.0) on 03.06.2025 22:07:46.
// </auto-generated>
//------------------------------------------------------------------------------

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

#ifdef __cplusplus
extern "C"
{
#endif

#include <ccommon.h>

    typedef struct daqInputPortConfig daqInputPortConfig;
    typedef struct daqInputPortNotifications daqInputPortNotifications;
    typedef struct daqContext daqContext;
    typedef struct daqComponent daqComponent;
    typedef struct daqString daqString;

    EXPORTED extern const daqIntfID DAQ_INPUT_PORT_CONFIG_INTF_ID;

    daqErrCode EXPORTED daqInputPortConfig_setNotificationMethod(daqInputPortConfig* self, daqPacketReadyNotification method);
    daqErrCode EXPORTED daqInputPortConfig_notifyPacketEnqueued(daqInputPortConfig* self, daqBool queueWasEmpty);
    daqErrCode EXPORTED daqInputPortConfig_notifyPacketEnqueuedOnThisThread(daqInputPortConfig* self);
    daqErrCode EXPORTED daqInputPortConfig_setListener(daqInputPortConfig* self, daqInputPortNotifications* port);
    daqErrCode EXPORTED daqInputPortConfig_getCustomData(daqInputPortConfig* self, daqBaseObject** customData);
    daqErrCode EXPORTED daqInputPortConfig_setCustomData(daqInputPortConfig* self, daqBaseObject* customData);
    daqErrCode EXPORTED daqInputPortConfig_setRequiresSignal(daqInputPortConfig* self, daqBool requiresSignal);
    daqErrCode EXPORTED daqInputPortConfig_getGapCheckingEnabled(daqInputPortConfig* self, daqBool* gapCheckingEnabled);
    daqErrCode EXPORTED daqInputPortConfig_createInputPort(daqInputPortConfig** obj, daqContext* context, daqComponent* parent, daqString* localId, daqBool gapChecking);

#ifdef __cplusplus
}
#endif
