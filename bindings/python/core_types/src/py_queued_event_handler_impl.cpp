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

#include "py_core_types/py_queued_event_handler_impl.h"
#include "py_core_types/py_core_types.h"

PyDaqIntf<daq::IPythonQueuedEventHandler, daq::IEventHandler> declareIPythonQueuedEventHandler(pybind11::module_ m)
{
    return wrapInterface<daq::IPythonQueuedEventHandler, daq::IEventHandler>(m, "IPythonQueuedEventHandler");
}

void defineIPythonQueuedEventHandler(pybind11::module_ m, PyDaqIntf<daq::IPythonQueuedEventHandler, daq::IEventHandler> cls)
{
    cls.doc() = "";

    m.def("QueuedEventHandler", [](const pybind11::object& object)
    {
        return PyQueuedEventHandler_Create<PyConverter>(object);
    }, py::arg("event_handler"));
}

