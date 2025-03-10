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
#include <opendaq/context_ptr.h>
#include <opendaq/logger_factory.h>
#include <opendaq/module_manager_ptr.h>
#include <coretypes/type_manager_ptr.h>
#include <opendaq/discovery_server_ptr.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @ingroup opendaq_context
 * @addtogroup opendaq_context_factories Factories
 * @{
 */

/*!
 * @brief Creates a Context with the given Scheduler, Logger, Property Object Class Manager, and Module Manager.
 * @param scheduler The scheduler the context has access to.
 * @param logger The logger the context has access to.
 * @param moduleManager The module manager.
 * @param typeManager The type manager.
 */
inline ContextPtr Context(const SchedulerPtr& scheduler,
                          const LoggerPtr& logger,
                          const TypeManagerPtr& typeManager,
                          const ModuleManagerPtr& moduleManager,
                          const AuthenticationProviderPtr& authenticationProvider = nullptr,
                          const DictPtr<IString, IBaseObject> options = Dict<IString, IBaseObject>(),
                          const DictPtr<IString, IDiscoveryServer> discoveryServers = Dict<IString, IDiscoveryServer>())
{
    ContextPtr obj(Context_Create(scheduler, logger, typeManager, moduleManager, authenticationProvider, options, discoveryServers));
    return obj;
}

/*!
 * @brief Creates a Context with the given logger, type manager and options and all other parameters set to nullptr.
 * @param logger The logger the context has access to.
 * @param typeManager The type manager.
 */
inline ContextPtr NullContext(const LoggerPtr& logger = Logger(), 
                              const TypeManagerPtr& typeManager = TypeManager(),
                              const DictPtr<IString, IBaseObject> options = Dict<IString, IBaseObject>())
{
    ContextPtr obj(Context_Create(nullptr, logger, typeManager, nullptr, nullptr, options, Dict<IString, IDiscoveryServer>()));
    return obj;
}


/*!@}*/
END_NAMESPACE_OPENDAQ
