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

#include <variant>
#include "py_core_types/py_core_types.h"
#include "py_core_types/py_converter.h"
#include <pybind11/stl.h>


PyDaqIntf<daq::ITypeManager, daq::IBaseObject> declareITypeManager(pybind11::module_ m)
{
    return wrapInterface<daq::ITypeManager, daq::IBaseObject>(m, "ITypeManager");
}

void defineITypeManager(pybind11::module_ m, PyDaqIntf<daq::ITypeManager, daq::IBaseObject> cls)
{
    cls.doc() = "Container for Type objects. The Type manager is used when creating certain types of objects (eg. Structs and Property object classes). The Types stored within the manager contain pre-defined fields, as well as constraints specifying how objects should look.";

    m.def("TypeManager", &daq::TypeManager_Create);

    cls.def("add_type",
        [](daq::ITypeManager *object, daq::IType* type)
        {
            const auto objectPtr = daq::TypeManagerPtr::Borrow(object);
            objectPtr.addType(type);

            daq::IEnumerationType* enumType = nullptr;
            auto errCode = type->queryInterface(daq::IEnumerationType::Id, reinterpret_cast<void**>(&enumType));
            if (OPENDAQ_SUCCEEDED(errCode)) {
                auto pyObject = py::cast(InterfaceWrapper<daq::IEnumerationType>(enumType));
                pyObject.attr("__type_manager") = object;
            }
        },
        py::arg("type"),
        "Adds a type to the manager.");
    cls.def("remove_type",
        [](daq::ITypeManager *object, const std::string& typeName)
        {
            const auto objectPtr = daq::TypeManagerPtr::Borrow(object);
            objectPtr.removeType(typeName);
        },
        py::arg("type_name"),
        "Removes the type from the manager.");
    cls.def("get_type",
        [](daq::ITypeManager *object, const std::string& typeName)
        {
            std::variant<daq::IType*, daq::IEnumerationType*> result;
            const auto objectPtr = daq::TypeManagerPtr::Borrow(object);
            auto type = objectPtr.getType(typeName);

            auto enumTypePtr = type.asPtrOrNull<daq::IEnumerationType>();
            if(enumTypePtr.assigned()) {
                auto pyObject = py::cast(InterfaceWrapper<daq::IEnumerationType>(enumTypePtr));
                pyObject.attr("__type_manager") = object;
                result = enumTypePtr.detach();
                return result;
            }

            result = type.detach();
            return result;
        },
        py::arg("type_name"),
        "Gets an added Type by name.");
    cls.def_property_readonly("types",
        [](daq::ITypeManager *object)
        {
            const auto objectPtr = daq::TypeManagerPtr::Borrow(object);
            return objectPtr.getTypes().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets a list of all added Types.");
    cls.def("has_type",
        [](daq::ITypeManager *object, const std::string& typeName)
        {
            const auto objectPtr = daq::TypeManagerPtr::Borrow(object);
            return objectPtr.hasType(typeName);
        },
        py::arg("type_name"),
        "Checks if a type with the specified name is already added.");
}
