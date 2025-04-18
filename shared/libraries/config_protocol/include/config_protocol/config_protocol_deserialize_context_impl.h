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
#include <config_protocol/config_protocol_deserialize_context.h>
#include <opendaq/component_deserialize_context_impl.h>

namespace daq::config_protocol
{

class ConfigProtocolDeserializeContextImpl : public GenericComponentDeserializeContextImpl<IConfigProtocolDeserializeContext>
{
public:
    ConfigProtocolDeserializeContextImpl(const ConfigProtocolClientCommPtr& clientComm,
                                         const std::string& remoteGlobalId,
                                         const ContextPtr& context,
                                         const ComponentPtr& root,
                                         const ComponentPtr& parent,
                                         const StringPtr& localId,
                                         IntfID* intfID,
                                         const ProcedurePtr& triggerCoreEvent = nullptr,
                                         const TypeManagerPtr& typeManager = nullptr);


    ConfigProtocolClientCommPtr getClientComm() override;
    std::string getRemoteGlobalId() override;
    void setRemoteGlobalId(const std::string& remoteGlobalId) override;
    TypeManagerPtr getTypeManager() override;

    ErrCode INTERFACE_FUNC clone(IComponent* newParent,
                                 IString* newLocalId,
                                 IComponentDeserializeContext** newComponentDeserializeContext,
                                 IntfID* newIntfID,
                                 IProcedure* newTriggerCoreEvent) override;

private:
    ConfigProtocolClientCommPtr clientComm;
    std::string remoteGlobalId;
    TypeManagerPtr typeManager;
};

}
