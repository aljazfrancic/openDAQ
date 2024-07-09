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

PyDaqIntf<daq::IComponentPrivate, daq::IBaseObject> declareIComponentPrivate(pybind11::module_ m)
{
    return wrapInterface<daq::IComponentPrivate, daq::IBaseObject>(m, "IComponentPrivate");
}

void defineIComponentPrivate(pybind11::module_ m, PyDaqIntf<daq::IComponentPrivate, daq::IBaseObject> cls)
{
    cls.doc() = "Provides access to private methods of the component.";

    cls.def("lock_attributes",
        [](daq::IComponentPrivate *object, daq::IList* attributes)
        {
            const auto objectPtr = daq::ComponentPrivatePtr::Borrow(object);
            objectPtr.lockAttributes(attributes);
        },
        py::arg("attributes"),
        "Locks the attributes contained in the provided list.");
    cls.def("lock_all_attributes",
        [](daq::IComponentPrivate *object)
        {
            const auto objectPtr = daq::ComponentPrivatePtr::Borrow(object);
            objectPtr.lockAllAttributes();
        },
        "Locks all attributes of the component.");
    cls.def("unlock_attributes",
        [](daq::IComponentPrivate *object, daq::IList* attributes)
        {
            const auto objectPtr = daq::ComponentPrivatePtr::Borrow(object);
            objectPtr.unlockAttributes(attributes);
        },
        py::arg("attributes"),
        "Unlocks the attributes contained in the provided list.");
    cls.def("unlock_all_attributes",
        [](daq::IComponentPrivate *object)
        {
            const auto objectPtr = daq::ComponentPrivatePtr::Borrow(object);
            objectPtr.unlockAllAttributes();
        },
        "Unlocks all attributes of the component.");
    cls.def("trigger_component_core_event",
        [](daq::IComponentPrivate *object, daq::ICoreEventArgs* args)
        {
            const auto objectPtr = daq::ComponentPrivatePtr::Borrow(object);
            objectPtr.triggerComponentCoreEvent(args);
        },
        py::arg("args"),
        "Triggers the component-specific core event with the provided arguments.");
}
