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

PyDaqIntf<daq::IServer, daq::IBaseObject> declareIServer(pybind11::module_ m)
{
    return wrapInterface<daq::IServer, daq::IBaseObject>(m, "IServer");
}

void defineIServer(pybind11::module_ m, PyDaqIntf<daq::IServer, daq::IBaseObject> cls)
{
    cls.doc() = "Represents a server. The server provides access to the openDAQ device. Depend of the implementation, it can support configuring the device, reading configuration, and data streaming.";

    cls.def("stop",
        [](daq::IServer *object)
        {
            const auto objectPtr = daq::ServerPtr::Borrow(object);
            objectPtr.stop();
        },
        "Stops the server. This is called when we remove the server from the Instance or Instance is closing.");
    cls.def_property_readonly("id",
        [](daq::IServer *object)
        {
            const auto objectPtr = daq::ServerPtr::Borrow(object);
            return objectPtr.getId().toStdString();
        },
        "Gets the server id.");
    cls.def("enable_discovery",
        [](daq::IServer *object)
        {
            const auto objectPtr = daq::ServerPtr::Borrow(object);
            objectPtr.enableDiscovery();
        },
        "Enables the server to be discovered by the clients.");
}
