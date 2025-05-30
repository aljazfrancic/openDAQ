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
#include <opcuatms_client/objects/tms_client_context.h>
#include <opcuatms_client/objects/tms_client_property_impl.h>

BEGIN_NAMESPACE_OPENDAQ_OPCUA_TMS

OPENDAQ_DECLARE_CLASS_FACTORY_WITH_INTERFACE(INLINE_FACTORY,
    TmsClientProperty, IProperty,
    const daq::ContextPtr&, daqContext,
    const daq::opcua::tms::TmsClientContextPtr&, ctx,
    const opcua::OpcUaNodeId&, nodeId,
    const daq::StringPtr&, propertyName)

OPENDAQ_DEFINE_CLASS_FACTORY_WITH_INTERFACE(INLINE_FACTORY,
    TmsClientProperty, IProperty,
    const daq::ContextPtr&, daqContext,
    const daq::opcua::tms::TmsClientContextPtr&, client,
    const opcua::OpcUaNodeId&, nodeId,
    const daq::StringPtr&, propertyName)

inline PropertyPtr TmsClientProperty(const ContextPtr& daqContext, const TmsClientContextPtr& ctx, const OpcUaNodeId& nodeId, const StringPtr& propertyName = nullptr)
{
    PropertyPtr obj(TmsClientProperty_Create(daqContext, ctx, nodeId, propertyName));
    return obj;
}

END_NAMESPACE_OPENDAQ_OPCUA_TMS
