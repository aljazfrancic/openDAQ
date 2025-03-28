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
#include <opendaq/sync_component_ptr.h>
#include <opendaq/context_ptr.h>
#include <opendaq/component_ptr.h>
#include <coretypes/string_ptr.h>

BEGIN_NAMESPACE_OPENDAQ
/*!
 * @ingroup opendaq_input_port
 * @addtogroup opendaq_input_port_factories Factories
 * @{
 */

/*!
 * @brief Creates an input port.
 * @param typeManager The typeManager
 */
inline SyncComponentPtr SyncComponent(const ContextPtr& context, const ComponentPtr& parent, const StringPtr& localId)
{
    return { SyncComponent_Create(context, parent, localId) };
}

/*!@}*/

END_NAMESPACE_OPENDAQ