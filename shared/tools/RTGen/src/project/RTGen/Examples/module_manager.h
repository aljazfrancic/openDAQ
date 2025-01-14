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
#include "coretypes/coretypes.h"
#include "module_driver_enumerator.h"

BEGIN_NAMESPACE_DEWESOFT_RT_CORE

static const IntfID ModuleManagerGuid = { 0xAA17416E, 0x4293, 0x592E, { 0xA4, 0xC6, 0x0C, 0xD4, 0x70, 0x54, 0x9F, 0x7E } };

/*#
 * [includeHeader("module_driver_ptr.h")]
 * [interfaceNamespace(IModuleManager, "Dewesoft::RT::Core::")]
 */
DECLARE_RT_INTERFACE(IModuleManager, IBaseObject)
{
    DEFINE_INTFID(ModuleManagerGuid)

    //[elementType(moduleDrivers, IModuleDriver)]
    virtual ErrCode INTERFACE_FUNC enumerateModuleDrivers(IList** moduleDrivers) = 0;
    virtual ErrCode INTERFACE_FUNC freeAllUnusedModuleDrivers() = 0;
};

OPENDAQ_DECLARE_CLASS_FACTORY(LIBRARY_FACTORY, ModuleManager, IModuleDriverEnumerator*, enumerator)

END_NAMESPACE_DEWESOFT_RT_CORE
