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
#include <opendaq/component_ptr.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @ingroup opendaq_component
 * @addtogroup opendaq_component_factories Factories
 * @{
 */

/*!
 * @brief Creates a component.
 * @param context The Context. Most often the creating function-block/device passes its own Context to the Folder.
 * @param parent The parent component.
 * @param localId The local ID of the component.
 * @param className The property object class name of the component.
 */
inline ComponentPtr Component(const ContextPtr& context, const ComponentPtr& parent, const StringPtr& localId, const StringPtr& className = "")
{
    ComponentPtr obj(Component_Create(context, parent, localId, className));
    return obj;
}

inline StringPtr OperationModeTypeToString(OperationModeType mode)
{
    switch (mode)
    {
        case OperationModeType::Idle:
            return String("Idle");
        case OperationModeType::Operation:
            return String("Operation");
        case OperationModeType::SafeOperation:
            return String("SafeOperation");
        default:
            return String("Unknown");
    }
}

inline OperationModeType OperationModeTypeFromString(const StringPtr& str)
{
    if (str == "Idle")
        return OperationModeType::Idle;
    if (str == "Operation")
        return OperationModeType::Operation;
    if (str == "SafeOperation")
        return OperationModeType::SafeOperation;
    return OperationModeType::Unknown;
}

/*!@}*/

END_NAMESPACE_OPENDAQ
