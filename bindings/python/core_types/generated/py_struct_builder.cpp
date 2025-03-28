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

#include <pybind11/gil.h>

#include "py_core_types/py_core_types.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::IStructBuilder, daq::IBaseObject> declareIStructBuilder(pybind11::module_ m)
{
    return wrapInterface<daq::IStructBuilder, daq::IBaseObject>(m, "IStructBuilder");
}

void defineIStructBuilder(pybind11::module_ m, PyDaqIntf<daq::IStructBuilder, daq::IBaseObject> cls)
{
    cls.doc() = "Builder component of Struct objects. Contains setter methods to configure the Struct parameters, and a `build` method that builds the Struct object.";

    m.def("StructBuilder", &daq::StructBuilder_Create);
    m.def("StructBuilderFromStruct", &daq::StructBuilderFromStruct_Create);

    cls.def("build",
        [](daq::IStructBuilder *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return objectPtr.build().detach();
        },
        "Builds and returns a Struct object using the currently set values of the Builder.");
    cls.def_property_readonly("struct_type",
        [](daq::IStructBuilder *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return objectPtr.getStructType().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the Struct's type.");
    cls.def_property_readonly("field_names",
        [](daq::IStructBuilder *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return objectPtr.getFieldNames().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets a list of all Struct field names.");
    cls.def_property("field_values",
        [](daq::IStructBuilder *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return objectPtr.getFieldValues().detach();
        },
        [](daq::IStructBuilder *object, daq::IList* values)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            objectPtr.setFieldValues(values);
        },
        py::return_value_policy::take_ownership,
        "Gets a list of all Struct field values. / Gets a list of all Struct field values.");
    cls.def("set",
        [](daq::IStructBuilder *object, const std::string& name, const py::object& field)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            objectPtr.set(name, pyObjectToBaseObject(field));
        },
        py::arg("name"), py::arg("field"),
        "Sets the value of a field with the given name.");
    cls.def("get",
        [](daq::IStructBuilder *object, const std::string& name)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return baseObjectToPyObject(objectPtr.get(name));
        },
        py::arg("name"),
        "Gets the value of a field with the given name.");
    cls.def("has_field",
        [](daq::IStructBuilder *object, const std::string& name)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return objectPtr.hasField(name);
        },
        py::arg("name"),
        "Checks whether a field with the given name exists in the Struct");
    cls.def_property_readonly("as_dictionary",
        [](daq::IStructBuilder *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::StructBuilderPtr::Borrow(object);
            return objectPtr.getAsDictionary().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the field names and values of the Struct as a Dictionary.");
}
