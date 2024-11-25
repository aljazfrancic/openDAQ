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

#include <pybind11/gil.h>

#include "py_opendaq/py_opendaq.h"
#include "py_core_types/py_converter.h"


PyDaqIntf<daq::IComponentTypePrivate, daq::IBaseObject> declareIComponentTypePrivate(pybind11::module_ m)
{
    return wrapInterface<daq::IComponentTypePrivate, daq::IBaseObject>(m, "IComponentTypePrivate");
}

void defineIComponentTypePrivate(pybind11::module_ m, PyDaqIntf<daq::IComponentTypePrivate, daq::IBaseObject> cls)
{
    cls.doc() = "Private interface to component type. Allows for setting the module information.";

    cls.def_property("module_info",
        nullptr,
        [](daq::IComponentTypePrivate *object, daq::IModuleInfo* info)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::ComponentTypePrivatePtr::Borrow(object);
            objectPtr.setModuleInfo(info);
        },
        "Sets the module information.");
}
