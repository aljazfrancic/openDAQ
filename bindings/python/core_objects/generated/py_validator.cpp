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

#include "py_core_objects/py_core_objects.h"
#include "py_core_types/py_converter.h"
#include "py_core_objects/py_variant_extractor.h"

PyDaqIntf<daq::IValidator, daq::IBaseObject> declareIValidator(pybind11::module_ m)
{
    return wrapInterface<daq::IValidator, daq::IBaseObject>(m, "IValidator");
}

void defineIValidator(pybind11::module_ m, PyDaqIntf<daq::IValidator, daq::IBaseObject> cls)
{
    cls.doc() = "Used by openDAQ properties to validate whether a value fits the value restrictions of the Property.";

    m.def("Validator", [](std::variant<daq::IString*, py::str, daq::IEvalValue*>& eval){
        return daq::Validator_Create(getVariantValue<daq::IString*>(eval));
    }, py::arg("eval"));


    cls.def("validate",
        [](daq::IValidator *object, const py::object& propObj, const py::object& value)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::ValidatorPtr::Borrow(object);
            objectPtr.validate(pyObjectToBaseObject(propObj), pyObjectToBaseObject(value));
        },
        py::arg("prop_obj"), py::arg("value"),
        "Checks whether `value` adheres to the validity conditions of the validator.");
    cls.def("validate_no_lock",
        [](daq::IValidator *object, const py::object& propObj, const py::object& value)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::ValidatorPtr::Borrow(object);
            objectPtr.validateNoLock(pyObjectToBaseObject(propObj), pyObjectToBaseObject(value));
        },
        py::arg("prop_obj"), py::arg("value"),
        "");
    cls.def_property_readonly("eval",
        [](daq::IValidator *object)
        {
            py::gil_scoped_release release;
            const auto objectPtr = daq::ValidatorPtr::Borrow(object);
            return objectPtr.getEval().toStdString();
        },
        "Gets the string expression used when creating the validator.");
}
