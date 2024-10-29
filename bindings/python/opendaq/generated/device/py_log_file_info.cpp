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


PyDaqIntf<daq::ILogFileInfo, daq::IBaseObject> declareILogFileInfo(pybind11::module_ m)
{
    return wrapInterface<daq::ILogFileInfo, daq::IBaseObject>(m, "ILogFileInfo");
}

void defineILogFileInfo(pybind11::module_ m, PyDaqIntf<daq::ILogFileInfo, daq::IBaseObject> cls)
{
    cls.doc() = "";

    m.def("LogFileInfoFromBuilder", &daq::LogFileInfoFromBuilder_Create);

    cls.def_property_readonly("id",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getId().toStdString();
        },
        "Gets the id of the log file in format `getLocalPath() + \"/\" + getName()`.");
    cls.def_property_readonly("local_path",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getLocalPath().toStdString();
        },
        "Gets the local path of the log file. The local path can be not assigned as it is optional.");
    cls.def_property_readonly("name",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getName().toStdString();
        },
        "Gets the name of the log file.");
    cls.def_property_readonly("description",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getDescription().toStdString();
        },
        "Gets the description of the log file.");
    cls.def_property_readonly("size",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getSize();
        },
        "Gets the size of the log file in bytes.");
    cls.def_property_readonly("encoding",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getEncoding().toStdString();
        },
        "Gets the encoding of the log file.");
    cls.def_property_readonly("last_modified",
        [](daq::ILogFileInfo *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::LogFileInfoPtr::Borrow(object);
            return objectPtr.getLastModified().toStdString();
        },
        "Gets the date of the last modification of the log file in ISO 8601 format.");
}