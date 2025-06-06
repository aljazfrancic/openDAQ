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
#include <coretypes/common.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @ingroup opendaq_utility
 * @addtogroup opendaq_core_events Core Event IDs
 * @{
 */

enum class CoreEventId : EnumType
{
    PropertyValueChanged = 0,
    PropertyObjectUpdateEnd = 10,
    PropertyAdded = 20,
    PropertyRemoved = 30,
    ComponentAdded = 40,
    ComponentRemoved = 50,
    SignalConnected = 60,
    SignalDisconnected = 70,
    DataDescriptorChanged = 80,
    ComponentUpdateEnd = 90,
    AttributeChanged = 100,
    TagsChanged = 110,
    StatusChanged = 120,
    TypeAdded = 130,
    TypeRemoved = 140,
    DeviceDomainChanged = 150,
    DeviceLockStateChanged = 160,
    ConnectionStatusChanged = 170,
    DeviceOperationModeChanged = 180,
    PropertyOrderChanged = 190,
};

/*!@}*/

END_NAMESPACE_OPENDAQ
