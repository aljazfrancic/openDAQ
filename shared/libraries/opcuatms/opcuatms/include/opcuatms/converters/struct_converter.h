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
#include <opcuatms/opcuatms.h>
#include <opcuashared/opcuavariant.h>
#include <opcuashared/opcuaobject.h>
#include <opendaq/context_ptr.h>

BEGIN_NAMESPACE_OPENDAQ_OPCUA_TMS

template <typename BlueberryType, typename TmsType, class BlueberryTypePtr = typename InterfaceToSmartPtr<BlueberryType>::SmartPtr>
class StructConverter
{
public:
    static BlueberryTypePtr ToDaqObject(const TmsType& tmsStruct, const ContextPtr& context = nullptr);
    static OpcUaObject<TmsType> ToTmsType(const BlueberryTypePtr& object, const ContextPtr& context = nullptr);
};

END_NAMESPACE_OPENDAQ_OPCUA_TMS
