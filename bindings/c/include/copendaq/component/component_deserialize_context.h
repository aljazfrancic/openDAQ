//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CGenerator v0.7.0) on 03.06.2025 22:06:51.
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

    typedef struct daqComponentDeserializeContext daqComponentDeserializeContext;
    typedef struct daqComponent daqComponent;
    typedef struct daqString daqString;
    typedef struct daqContext daqContext;
    typedef struct daqProcedure daqProcedure;

    EXPORTED extern const daqIntfID DAQ_COMPONENT_DESERIALIZE_CONTEXT_INTF_ID;

    daqErrCode EXPORTED daqComponentDeserializeContext_getParent(daqComponentDeserializeContext* self, daqComponent** parent);
    daqErrCode EXPORTED daqComponentDeserializeContext_getRoot(daqComponentDeserializeContext* self, daqComponent** root);
    daqErrCode EXPORTED daqComponentDeserializeContext_getLocalId(daqComponentDeserializeContext* self, daqString** localId);
    daqErrCode EXPORTED daqComponentDeserializeContext_getContext(daqComponentDeserializeContext* self, daqContext** context);
    daqErrCode EXPORTED daqComponentDeserializeContext_getIntfID(daqComponentDeserializeContext* self, daqIntfID* intfID);
    daqErrCode EXPORTED daqComponentDeserializeContext_getTriggerCoreEvent(daqComponentDeserializeContext* self, daqProcedure** triggerCoreEvent);
    daqErrCode EXPORTED daqComponentDeserializeContext_clone(daqComponentDeserializeContext* self, daqComponent* newParent, daqString* newLocalId, daqComponentDeserializeContext** newComponentDeserializeContext, daqIntfID* newIntfID, daqProcedure* newTriggerCoreEvent);
    daqErrCode EXPORTED daqComponentDeserializeContext_createComponentDeserializeContext(daqComponentDeserializeContext** obj, daqContext* context, daqComponent* root, daqComponent* parent, daqString* localId, daqIntfID* intfID, daqProcedure* triggerCoreEvent);

#ifdef __cplusplus
}
#endif
