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

PyDaqIntf<daq::IInputPort, daq::IComponent> declareIInputPort(pybind11::module_ m)
{
    return wrapInterface<daq::IInputPort, daq::IComponent>(m, "IInputPort");
}

void defineIInputPort(pybind11::module_ m, PyDaqIntf<daq::IInputPort, daq::IComponent> cls)
{
    cls.doc() = "Signals accepted by input ports can be connected, forming a connection between the input port and signal, through which Packets can be sent.";

    cls.def("accepts_signal",
        [](daq::IInputPort *object, daq::ISignal* signal)
        {
            const auto objectPtr = daq::InputPortPtr::Borrow(object);
            return objectPtr.acceptsSignal(signal);
        },
        py::arg("signal"),
        "Returns true if the signal can be connected to the input port; false otherwise.");
    cls.def("connect",
        [](daq::IInputPort *object, daq::ISignal* signal)
        {
            const auto objectPtr = daq::InputPortPtr::Borrow(object);
            objectPtr.connect(signal);
        },
        py::arg("signal"),
        "Connects the signal to the input port, forming a Connection.");
    cls.def("disconnect",
        [](daq::IInputPort *object)
        {
            const auto objectPtr = daq::InputPortPtr::Borrow(object);
            objectPtr.disconnect();
        },
        "Disconnects the signal from the input port.");
    cls.def_property_readonly("signal",
        [](daq::IInputPort *object)
        {
            const auto objectPtr = daq::InputPortPtr::Borrow(object);
            return objectPtr.getSignal().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the signal connected to the input port.");
    cls.def_property_readonly("requires_signal",
        [](daq::IInputPort *object)
        {
            const auto objectPtr = daq::InputPortPtr::Borrow(object);
            return objectPtr.getRequiresSignal();
        },
        "Returns true if the input port requires a signal to be connected; false otherwise.");
    cls.def_property_readonly("connection",
        [](daq::IInputPort *object)
        {
            const auto objectPtr = daq::InputPortPtr::Borrow(object);
            return objectPtr.getConnection().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the Connection object formed between the Signal and Input port.");
}
