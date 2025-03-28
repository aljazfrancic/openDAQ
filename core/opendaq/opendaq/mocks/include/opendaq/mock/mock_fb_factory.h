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
#include <opendaq/function_block_ptr.h>
#include <opendaq/function_block_type_ptr.h>
#include <opendaq/mock/mock_fb.h>
#include <opendaq/mock/mock_fb_dynamic_input_ports.h>
#include <opendaq/mock/mock_fb_dynamic_output_ports.h>

BEGIN_NAMESPACE_OPENDAQ

inline FunctionBlockPtr MockFunctionBlock(
    const FunctionBlockTypePtr& type,
    const daq::ContextPtr& ctx,
    const ComponentPtr& parent,
    const StringPtr& localId,
    const PropertyObjectPtr& config = nullptr
    )
{
    FunctionBlockPtr obj(MockFunctionBlock_Create(type, ctx, parent, localId, config));
    return obj;
}

inline FunctionBlockPtr MockFunctionBlockDynamicInputPort(
    const FunctionBlockTypePtr& type,
    const daq::ContextPtr& ctx,
    const ComponentPtr& parent,
    const StringPtr& localId,
    const PropertyObjectPtr& config = nullptr
    )
{
    FunctionBlockPtr obj(MockFunctionBlockDynamicInputPort_Create(type, ctx, parent, localId, config));
    return obj;
}

inline FunctionBlockPtr MockFunctionBlockDynamicOutputPort(
    const FunctionBlockTypePtr& type,
    const daq::ContextPtr& ctx,
    const ComponentPtr& parent,
    const StringPtr& localId,
    const PropertyObjectPtr& config = nullptr
    )
{
    FunctionBlockPtr obj(MockFunctionBlockDynamicOutputPort_Create(type, ctx, parent, localId, config));
    return obj;
}

END_NAMESPACE_OPENDAQ
