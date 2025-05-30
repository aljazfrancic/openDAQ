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

enum class SampleType : EnumType
{
    Invalid = 0,
    Undefined = 0,
    Float32,
    Float64,
    UInt8,
    Int8,
    UInt16,
    Int16,
    UInt32,
    Int32,
    UInt64,
    Int64,
    RangeInt64,
    ComplexFloat32,
    ComplexFloat64,
    Binary,
    String,
    Struct,
    Null,
    // ReSharper disable once CppInconsistentNaming
    _count
};

#define SAMPLE_TYPE_COUNT (EnumType) SampleType::_count

#define INVALID_SAMPLE_TYPE SampleType::Invalid

enum class ScaledSampleType : EnumType
{
    Invalid = 0,
    Float32,
    Float64,
};

#define INVALID_SCALED_SAMPLE_TYPE ScaledSampleType::Invalid

/////////////////////

END_NAMESPACE_OPENDAQ
