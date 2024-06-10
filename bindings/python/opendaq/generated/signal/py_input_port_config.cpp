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

#include "py_opendaq/py_opendaq.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::IInputPortConfig, daq::IInputPort> declareIInputPortConfig(pybind11::module_ m)
{
    py::enum_<daq::PacketReadyNotification>(m, "PacketReadyNotification")
        .value("None", daq::PacketReadyNotification::None)
        .value("SameThread", daq::PacketReadyNotification::SameThread)
        .value("Scheduler", daq::PacketReadyNotification::Scheduler)
        .value("SchedulerQueueWasEmpty", daq::PacketReadyNotification::SchedulerQueueWasEmpty);

    return wrapInterface<daq::IInputPortConfig, daq::IInputPort>(m, "IInputPortConfig");
}

void defineIInputPortConfig(pybind11::module_ m, PyDaqIntf<daq::IInputPortConfig, daq::IInputPort> cls)
{
    cls.doc() = "The configuration component of input ports. Provides access to Input port owners to internal components of the input port.";

    m.def("InputPort", &daq::InputPort_Create);

    cls.def_property("notification_method",
        nullptr,
        [](daq::IInputPortConfig *object, daq::PacketReadyNotification method)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            objectPtr.setNotificationMethod(method);
        },
        "Sets the input-ports response to the packet enqueued notification.");
    cls.def("notify_packet_enqueued",
        [](daq::IInputPortConfig *object, const bool queueWasEmpty)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            objectPtr.notifyPacketEnqueued(queueWasEmpty);
        },
        py::arg("queue_was_empty"),
        "Gets called when a packet was enqueued in a connection.");
    cls.def("notify_packet_enqueued_on_this_thread",
        [](daq::IInputPortConfig *object)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            objectPtr.notifyPacketEnqueuedOnThisThread();
        },
        "Gets called when a packet was enqueued in a connection.");
    cls.def_property("listener",
        nullptr,
        [](daq::IInputPortConfig *object, daq::IInputPortNotifications* port)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            objectPtr.setListener(port);
        },
        "Set the object receiving input-port related events and notifications.");
    cls.def_property("custom_data",
        [](daq::IInputPortConfig *object)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            return baseObjectToPyObject(objectPtr.getCustomData());
        },
        [](daq::IInputPortConfig *object, const py::object& customData)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            objectPtr.setCustomData(pyObjectToBaseObject(customData));
        },
        py::return_value_policy::take_ownership,
        "Get a custom data attached to the object. / Set a custom data attached to the object.");
    cls.def_property("requires_signal",
        nullptr,
        [](daq::IInputPortConfig *object, const bool requiresSignal)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            objectPtr.setRequiresSignal(requiresSignal);
        },
        "Sets requires signal flag of the input port.");
    cls.def_property_readonly("gap_checking_enabled",
        [](daq::IInputPortConfig *object)
        {
            const auto objectPtr = daq::InputPortConfigPtr::Borrow(object);
            return objectPtr.getGapCheckingEnabled();
        },
        "Returns the state of gap checking requested by the input port.");
}
