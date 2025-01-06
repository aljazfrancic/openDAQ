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

#include "py_core_types/py_core_types.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::IEnumerationType, daq::IType> declareIEnumerationType(pybind11::module_ m)
{
    return wrapInterface<daq::IEnumerationType, daq::IType>(m, "IEnumerationType", py::dynamic_attr());
}

void defineIEnumerationType(pybind11::module_ m, PyDaqIntf<daq::IEnumerationType, daq::IType> cls)
{
    cls.doc() = "Enumeration types define the enumerator names and values of Enumerations with a name matching that of the Enumeration type.";

    m.def("EnumerationType", &daq::EnumerationType_Create);
    m.def("EnumerationTypeWithValues", &daq::EnumerationTypeWithValues_Create);

    cls.def_property_readonly("enumerator_names",
        [](daq::IEnumerationType *object)
        {
            const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);
            return objectPtr.getEnumeratorNames().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the list of enumerator names.");
    cls.def_property_readonly("as_dictionary",
        [](daq::IEnumerationType *object)
        {
            const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);
            return objectPtr.getAsDictionary().detach();
        },
        py::return_value_policy::take_ownership,
        "Gets the enumerator names and values as a Dictionary.");
    cls.def("get_enumerator_int_value",
        [](daq::IEnumerationType *object, const std::string& name)
        {
            const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);
            return objectPtr.getEnumeratorIntValue(name);
        },
        py::arg("name"),
        "Gets the value of enumerator with the specified name.");
    cls.def_property_readonly("count",
        [](daq::IEnumerationType *object)
        {
            const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);
            return objectPtr.getCount();
        },
        "Gets the number of enumerators within the Enumeration Type.");
    cls.def("__getattr__", [](daq::IEnumerationType *object, const std::string &value) {
        const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);
        
        daq::DictPtr<daq::IString, daq::IInteger> dict = objectPtr.getAsDictionary();
        if(!dict.hasKey(value)) {
            throw py::attribute_error("EnumType has no value named " + value);
        }

        auto pyObject = py::cast(InterfaceWrapper<daq::IEnumerationType>(objectPtr.addRefAndReturn()));
        auto typeManager = pyObject.attr("__type_manager").cast<daq::ITypeManager*>();
        const auto typeManagerPtr = daq::TypeManagerPtr::Borrow(typeManager);
        const auto enumName = objectPtr.getName();

        return daq::Enumeration_Create(enumName, daq::String(value), typeManagerPtr);
    });
    cls.def("__dir__", [](daq::IEnumerationType *object) {
        const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);
        auto keys = objectPtr.getAsDictionary().getKeyList();

        // Add method names to the list of keys
        keys->pushBack(daq::String("enumerator_names"));
        keys->pushBack(daq::String("as_dictionary"));
        keys->pushBack(daq::String("get_enumerator_int_value"));
        keys->pushBack(daq::String("count"));

        return baseObjectToPyObject(keys);
    });
    cls.def("__getitem__", [](daq::IEnumerationType *object, const std::string &value) {
        const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);

        daq::DictPtr<daq::IString, daq::IInteger> dict = objectPtr.getAsDictionary();
        if(!dict.hasKey(value)) {
            throw py::key_error("EnumType has no value named " + value);
        }

        auto pyObject = py::cast(InterfaceWrapper<daq::IEnumerationType>(objectPtr.addRefAndReturn()));
        auto typeManager = pyObject.attr("__type_manager").cast<daq::ITypeManager*>();
        const auto typeManagerPtr = daq::TypeManagerPtr::Borrow(typeManager);
        const auto enumName = objectPtr.getName();

        return daq::Enumeration_Create(enumName, daq::String(value), typeManagerPtr);
    });
    cls.def("__call__", [](daq::IEnumerationType *object, int value) {
        const auto objectPtr = daq::EnumerationTypePtr::Borrow(object);

        daq::DictPtr<daq::IString, daq::IInteger> dict = objectPtr.getAsDictionary();
        for(const auto& pair : dict) {
            if(pair.second == value) {
                auto pyObject = py::cast(InterfaceWrapper<daq::IEnumerationType>(objectPtr.addRefAndReturn()));
                auto typeManager = pyObject.attr("__type_manager").cast<daq::ITypeManager*>();
                const auto typeManagerPtr = daq::TypeManagerPtr::Borrow(typeManager);
                const auto enumName = objectPtr.getName();

                return daq::Enumeration_Create(enumName, pair.first, typeManagerPtr);
            }
        }

        throw py::value_error("EnumType has no value with value " + std::to_string(value));
    });
}
