//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (PythonGenerator).
// </auto-generated>
//------------------------------------------------------------------------------

/*
 * Copyright 2022-2024 openDAQ d. o. o.
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

#include "py_opendaq/py_opendaq.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::ITailReaderStatus, daq::IReaderStatus> declareITailReaderStatus(pybind11::module_ m)
{
    return wrapInterface<daq::ITailReaderStatus, daq::IReaderStatus>(m, "ITailReaderStatus");
}

void defineITailReaderStatus(pybind11::module_ m, PyDaqIntf<daq::ITailReaderStatus, daq::IReaderStatus> cls)
{
    cls.doc() = "ITailReaderStatus inherits from IReaderStatus to expand information returned read function";

    m.def("TailReaderStatus", &daq::TailReaderStatus_Create);

    cls.def_property_readonly("sufficient_history",
        [](daq::ITailReaderStatus *object)
        {
            const auto objectPtr = daq::TailReaderStatusPtr::Borrow(object);
            return objectPtr.getSufficientHistory();
        },
        "");
}
