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

PyDaqIntf<daq::IInputPortNotifications, daq::IBaseObject> declareIInputPortNotifications(pybind11::module_ m)
{
    return wrapInterface<daq::IInputPortNotifications, daq::IBaseObject>(m, "IInputPortNotifications");
}

void defineIInputPortNotifications(pybind11::module_ m, PyDaqIntf<daq::IInputPortNotifications, daq::IBaseObject> cls)
{
    cls.doc() = "Notifications object passed to the input port on construction by its owner (listener).";

    cls.def("accepts_signal",
        [](daq::IInputPortNotifications *object, daq::IInputPort* port, daq::ISignal* signal)
        {
            const auto objectPtr = daq::InputPortNotificationsPtr::Borrow(object);
            return objectPtr.acceptsSignal(port, signal);
        },
        py::arg("port"), py::arg("signal"),
        "Called when the Input port method `acceptsSignal` is called. Should return true if the signal is accepted; false otherwise.");
    cls.def("connected",
        [](daq::IInputPortNotifications *object, daq::IInputPort* port)
        {
            const auto objectPtr = daq::InputPortNotificationsPtr::Borrow(object);
            objectPtr.connected(port);
        },
        py::arg("port"),
        "Called when a signal is connected to the input port.");
    cls.def("disconnected",
        [](daq::IInputPortNotifications *object, daq::IInputPort* port)
        {
            const auto objectPtr = daq::InputPortNotificationsPtr::Borrow(object);
            objectPtr.disconnected(port);
        },
        py::arg("port"),
        "Called when a signal is disconnected from the input port.");
    cls.def("packet_received",
        [](daq::IInputPortNotifications *object, daq::IInputPort* port)
        {
            const auto objectPtr = daq::InputPortNotificationsPtr::Borrow(object);
            objectPtr.packetReceived(port);
        },
        py::arg("port"),
        "Notifies the listener of the newly received packet on the specified input-port.");
}
