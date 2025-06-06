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
#include <opendaq/sample_type.h>
#include <opendaq/signal_ptr.h>
#include <opendaq/data_descriptor_ptr.h>

BEGIN_NAMESPACE_OPENDAQ

inline daq::ErrCode getSignalSampleType(const daq::SignalPtr& signal, daq::SampleType* sampleType)
{
    OPENDAQ_PARAM_NOT_NULL(sampleType);

    DataDescriptorPtr descriptor;
    ErrCode errCode = signal->getDescriptor(&descriptor);
    OPENDAQ_RETURN_IF_FAILED(errCode);

    if (descriptor.isStructDescriptor())
    {
        return DAQ_MAKE_ERROR_INFO(OPENDAQ_ERR_INVALIDTYPE, "Struct values are not supported", nullptr);
    }

    return descriptor->getSampleType(sampleType);
}

END_NAMESPACE_OPENDAQ
