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
#include <opendaq/component_type_impl.h>
#include <opendaq/component_type_builder_ptr.h>
#include <opendaq/device_type.h>

BEGIN_NAMESPACE_OPENDAQ

class DeviceTypeImpl : public GenericComponentTypeImpl<IDeviceType>
{
public:
    using Self = DeviceTypeImpl;
    using Super = GenericComponentTypeImpl<IDeviceType>;
    explicit DeviceTypeImpl(const StringPtr& id,
                            const StringPtr& name,
                            const StringPtr& description,
                            const PropertyObjectPtr& defaultConfig,
                            const StringPtr& prefix);

    explicit DeviceTypeImpl(const ComponentTypeBuilderPtr& builder);

    ErrCode INTERFACE_FUNC getConnectionStringPrefix(IString** prefix) override;

    // ISerializable
    ErrCode INTERFACE_FUNC serialize(ISerializer* serializer) override;
    ErrCode INTERFACE_FUNC getSerializeId(ConstCharPtr* serializedId) const override;

    static ConstCharPtr SerializeId();
    static ErrCode Deserialize(ISerializedObject* serialized, IBaseObject* context, IFunction* factoryCallback, IBaseObject** obj);
};


END_NAMESPACE_OPENDAQ
