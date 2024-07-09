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

#include "py_core_objects/py_core_objects.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::IPropertyBuilder, daq::IBaseObject> declareIPropertyBuilder(pybind11::module_ m)
{
    return wrapInterface<daq::IPropertyBuilder, daq::IBaseObject>(m, "IPropertyBuilder");
}

void defineIPropertyBuilder(pybind11::module_ m, PyDaqIntf<daq::IPropertyBuilder, daq::IBaseObject> cls)
{
    cls.doc() = "The builder interface of Properties. Allows for construction of Properties through the `build` method.";

    m.def("PropertyBuilder", &daq::PropertyBuilder_Create);
    m.def("BoolPropertyBuilder", &daq::BoolPropertyBuilder_Create);
    m.def("IntPropertyBuilder", &daq::IntPropertyBuilder_Create);
    m.def("FloatPropertyBuilder", &daq::FloatPropertyBuilder_Create);
    m.def("StringPropertyBuilder", &daq::StringPropertyBuilder_Create);
    m.def("ListPropertyBuilder", &daq::ListPropertyBuilder_Create);
    m.def("DictPropertyBuilder", &daq::DictPropertyBuilder_Create);
    m.def("RatioPropertyBuilder", &daq::RatioPropertyBuilder_Create);
    m.def("ObjectPropertyBuilder", &daq::ObjectPropertyBuilder_Create);
    m.def("ReferencePropertyBuilder", &daq::ReferencePropertyBuilder_Create);
    m.def("FunctionPropertyBuilder", &daq::FunctionPropertyBuilder_Create);
    m.def("SelectionPropertyBuilder", &daq::SelectionPropertyBuilder_Create);
    m.def("SparseSelectionPropertyBuilder", &daq::SparseSelectionPropertyBuilder_Create);
    m.def("StructPropertyBuilder", &daq::StructPropertyBuilder_Create);
    m.def("EnumerationPropertyBuilder", &daq::EnumerationPropertyBuilder_Create);

    cls.def("build",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.build().detach();
        },
        "Builds and returns a Property using the currently set values of the Builder.");
    cls.def_property("value_type",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getValueType();
        },
        [](daq::IPropertyBuilder *object, daq::CoreType type)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setValueType(type);
        },
        "Gets the Value type of the Property. / Sets the Value type of the Property. Values written to the corresponding Property value must be of the same type.");
    cls.def_property("name",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getName().toStdString();
        },
        [](daq::IPropertyBuilder *object, const std::string& name)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setName(name);
        },
        "Gets the Name of the Property. / Sets the Name of the Property. The names of Properties in a Property object must be unique. The name is used as the key to the corresponding Property value when getting/setting the value.");
    cls.def_property("description",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getDescription().toStdString();
        },
        [](daq::IPropertyBuilder *object, const std::string& description)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setDescription(description);
        },
        "Gets the short string Description of the Property. / Sets the short string Description of the Property.");
    cls.def_property("unit",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getUnit().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& unit)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setUnit(pyObjectToBaseObject(unit));
        },
        py::return_value_policy::take_ownership,
        "Gets the Unit of the Property. / Sets the Unit of the Property.");
    cls.def_property("min_value",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getMinValue().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& min)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setMinValue(pyObjectToBaseObject(min));
        },
        py::return_value_policy::take_ownership,
        "Gets the Minimum value of the Property. Available only if the Value type is `ctInt` or `ctFloat`. / Sets the Minimum value of the Property. Available only if the Value type is `ctInt` or `ctFloat`.");
    cls.def_property("max_value",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getMaxValue().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& max)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setMaxValue(pyObjectToBaseObject(max));
        },
        py::return_value_policy::take_ownership,
        "Gets the Maximum value of the Property. Available only if the Value type is `ctInt` or `ctFloat`. / Sets the Maximum value of the Property. Available only if the Value type is `ctInt` or `ctFloat`.");
    cls.def_property("default_value",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return baseObjectToPyObject(objectPtr.getDefaultValue());
        },
        [](daq::IPropertyBuilder *object, const py::object& value)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setDefaultValue(pyObjectToBaseObject(value));
        },
        py::return_value_policy::take_ownership,
        "Gets the Default value of the Property. / Sets the Default value of the Property. The Default value must always be configured for a Property to be in a valid state. Exceptions are Function/Procedure and Reference properties. The function will freeze default value if it is freezable.");
    cls.def_property("suggested_values",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getSuggestedValues().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& values)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setSuggestedValues(pyObjectToBaseObject(values));
        },
        py::return_value_policy::take_ownership,
        "Gets the list of Suggested values. Contains values that are the optimal gettings for the corresponding Property value. These values, however, are not enforced when getting a new Property value. / Sets the list of Suggested values. Contains values that are the optimal settings for the corresponding Property value. These values, however, are not enforced when setting a new Property value.");
    cls.def_property("visible",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getVisible().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& visible)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setVisible(pyObjectToBaseObject(visible));
        },
        py::return_value_policy::take_ownership,
        "Used to determine whether the property is visible or not. / Used to determine whether the property is visible or not.");
    cls.def_property("read_only",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getReadOnly().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& readOnly)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setReadOnly(pyObjectToBaseObject(readOnly));
        },
        py::return_value_policy::take_ownership,
        "Used to determine whether the Property is a read-only property or not. / Used to determine whether the Property is a read-only property or not.");
    cls.def_property("selection_values",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return baseObjectToPyObject(objectPtr.getSelectionValues());
        },
        [](daq::IPropertyBuilder *object, const py::object& values)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setSelectionValues(pyObjectToBaseObject(values));
        },
        py::return_value_policy::take_ownership,
        "Gets the list or dictionary of selection values. / Sets the list or dictionary of selection values. If the list/dictionary is not empty, the property is a Selection property, and must have the Value type `ctInt`.");
    cls.def_property("referenced_property",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getReferencedProperty().detach();
        },
        [](daq::IPropertyBuilder *object, daq::IEvalValue* propertyEval)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setReferencedProperty(propertyEval);
        },
        py::return_value_policy::take_ownership,
        "Gets the referenced property. / Sets the referenced property. If set, all getters except for the `Name`, `Referenced property`, and `Is referenced` getters will return the value of the `Referenced property`.");
    cls.def_property("validator",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getValidator().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& validator)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setValidator(pyObjectToBaseObject(validator));
        },
        py::return_value_policy::take_ownership,
        "Gets the validator of the Property. / Sets the validator of the Property.");
    cls.def_property("coercer",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getCoercer().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& coercer)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setCoercer(pyObjectToBaseObject(coercer));
        },
        py::return_value_policy::take_ownership,
        "Gets the coercer of the Property. / Sets the coercer of the Property.");
    cls.def_property("callable_info",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getCallableInfo().detach();
        },
        [](daq::IPropertyBuilder *object, const py::object& callable)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setCallableInfo(pyObjectToBaseObject(callable));
        },
        py::return_value_policy::take_ownership,
        "Gets the Callable information objects of the Property that specifies the argument and return types of the callable object stored as the Property value. / Sets the Callable information objects of the Property that specifies the argument and return types of the callable object stored as the Property value.");
    /*
    cls.def_property("on_property_value_write",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getOnPropertyValueWrite().detach();
        },
        [](daq::IPropertyBuilder *object, daq::IEvent* event)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setOnPropertyValueWrite(event);
        },
        py::return_value_policy::take_ownership,
        "Gets a custom on-write event. Used mostly when cloning properties. / Sets a custom on-write event. Used mostly when cloning properties.");
    */
    /*
    cls.def_property("on_property_value_read",
        [](daq::IPropertyBuilder *object)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            return objectPtr.getOnPropertyValueRead().detach();
        },
        [](daq::IPropertyBuilder *object, daq::IEvent* event)
        {
            const auto objectPtr = daq::PropertyBuilderPtr::Borrow(object);
            objectPtr.setOnPropertyValueRead(event);
        },
        py::return_value_policy::take_ownership,
        "Gets a custom on-read event. Used mostly when cloning properties. / Sets a custom on-read event. Used mostly when cloning properties.");
    */
}
