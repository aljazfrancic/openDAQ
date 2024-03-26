/*
 * Copyright 2022-2024 Blueberry d.o.o.
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
#include <coretypes/integer.h>
#include <coretypes/number_impl.h>

BEGIN_NAMESPACE_OPENDAQ

template <>
inline ErrCode OrdinalObjectImpl<Int, IInteger, INumber>::serialize(ISerializer* serializer)
{
    if (serializer == nullptr)
        return OPENDAQ_ERR_ARGUMENT_NULL;

    serializer->writeInt(value);

    return OPENDAQ_SUCCESS;
}

using IntegerImpl = NumberImpl<Int, IInteger>;

END_NAMESPACE_OPENDAQ
