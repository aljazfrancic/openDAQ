/*
 * Copyright 2022-2024 openDAQ d.o.o.
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
#include <coretypes/struct_type_factory.h>
#include <coretypes/simple_type_factory.h>
#include <opendaq/device_domain_ptr.h>
#include <coreobjects/unit_factory.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @ingroup opendaq_device_domain
 * @addtogroup opendaq_device_domain_factories Factories
 * @{
 */

inline DeviceDomainPtr DeviceDomain(const RatioPtr& tickResolution,
                                    const StringPtr& origin,
                                    const UnitPtr& unit,
                                    const StringPtr& referenceDomainId = nullptr,
                                    const NumberPtr& referenceDomainOffset = nullptr,
                                    const BoolPtr& referenceDomainIsAbsolute = nullptr)
{
    DeviceDomainPtr obj(
        DeviceDomain_Create(tickResolution, origin, unit, referenceDomainId, referenceDomainOffset, referenceDomainIsAbsolute));
    return obj;
}

inline StructTypePtr DeviceDomainStructType()
{
    return StructType(
        "DeviceDomain",
        List<IString>("TickResolution", "Origin", "Unit", "ReferenceDomainId", "ReferenceDomainOffset", "ReferenceDomainIsAbsolute"),
        List<IBaseObject>(Ratio(1, 1), "", Unit("s", -1, "second", "time"), nullptr, nullptr, nullptr),
        List<IType>(RatioStructType(), SimpleType(ctString), UnitStructType(), SimpleType(ctString), SimpleType(ctFloat), SimpleType(ctBool)));
}

/*!@}*/

END_NAMESPACE_OPENDAQ
