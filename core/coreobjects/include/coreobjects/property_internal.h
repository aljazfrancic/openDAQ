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

#pragma once
#include <coreobjects/property_object.h>

BEGIN_NAMESPACE_OPENDAQ

struct IEvalValue;

/*!
 * @ingroup objects_property
 * @addtogroup objects_property_obj PropertyInternal
 * @{
 */

/*#
 * [interfaceSmartPtr(IBoolean, BooleanPtr, "<coretypes/boolean_factory.h>")]
 * [interfaceLibrary(INumber, CoreTypes)]
 * [interfaceLibrary(IStructType, CoreTypes)]
 */
DECLARE_OPENDAQ_INTERFACE(IPropertyInternal, IBaseObject)
{
    /*!
     * @brief Clones the property without an owner.
     */
    virtual ErrCode INTERFACE_FUNC clone(IProperty** clonedProperty) = 0;

    /*!
     * @brief Clones the property, setting the passed PropertyObject as its owner.
     *
     * If the provided owner is the same as the current owner of the property, the property is not cloned.
     * Instead the property itself is returned as-is.
     */
    virtual ErrCode INTERFACE_FUNC cloneWithOwner(IPropertyObject* owner, IProperty** clonedProperty) = 0;

    /*!
     * @brief Gets the Property description in an as either a String or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getDescriptionUnresolved(IString** description) = 0;

    /*!
     * @brief Gets the Property unit in an as either a String (TODO: as an IUnit once supported)
     * or unresolved EvalValue. The EvalValue is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getUnitUnresolved(IBaseObject** unit) = 0;

    /*!
     * @brief Gets the Property min value in an as either a Number or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getMinValueUnresolved(INumber** min) = 0;

    /*!
     * @brief Gets the Property max value in an as either a Number or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getMaxValueUnresolved(INumber** max) = 0;

    /*!
     * @brief Gets the Property default value in an as either a BaseObject or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getDefaultValueUnresolved(IBaseObject** value) = 0;

    // [templateType(values, IBaseObject)]
    /*!
     * @brief Gets the Property suggested values in an as either a List of BaseObjects or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getSuggestedValuesUnresolved(IList** values) = 0;

    /*!
     * @brief Gets the Property visible field in an as either a Boolean or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getVisibleUnresolved(IBoolean** visible) = 0;

    /*!
     * @brief Gets the Property read-only field in an as either a Boolean or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getReadOnlyUnresolved(IBoolean** readOnly) = 0;

    /*!
     * @brief Gets the Property selection values in an as either a Dictionary of Int-BaseObject pairs, List of BaseObjects,
     * or unresolved EvalValue. The EvalValue is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getSelectionValuesUnresolved(IBaseObject** values) = 0;

    /*!
     * @brief Gets the Property referenced property in an as either a Property or unresolved EvalValue. The EvalValue
     * is bound to the owner, if the Property has an owner.
     */
    virtual ErrCode INTERFACE_FUNC getReferencedPropertyUnresolved(IEvalValue** propertyEval) = 0;

    /*!
     * @brief Gets the unresolved type of the Property 
     */
    virtual ErrCode INTERFACE_FUNC getValueTypeUnresolved(CoreType* coreType) = 0;
    
    // [templateType(event, IPropertyObject, IPropertyValueEventArgs)]
    virtual ErrCode INTERFACE_FUNC getClassOnPropertyValueRead(IEvent** event) = 0;
    // [templateType(event, IPropertyObject, IPropertyValueEventArgs)]
    virtual ErrCode INTERFACE_FUNC getClassOnPropertyValueWrite(IEvent** event) = 0;

    virtual ErrCode INTERFACE_FUNC getValueTypeNoLock(CoreType* type) = 0;
    virtual ErrCode INTERFACE_FUNC getKeyTypeNoLock(CoreType* type) = 0;
    virtual ErrCode INTERFACE_FUNC getItemTypeNoLock(CoreType* type) = 0;
    virtual ErrCode INTERFACE_FUNC getDescriptionNoLock(IString** description) = 0;
    virtual ErrCode INTERFACE_FUNC getUnitNoLock(IUnit** unit) = 0;
    virtual ErrCode INTERFACE_FUNC getMinValueNoLock(INumber** min) = 0;
    virtual ErrCode INTERFACE_FUNC getMaxValueNoLock(INumber** max) = 0;
    virtual ErrCode INTERFACE_FUNC getDefaultValueNoLock(IBaseObject** value) = 0;
    // [templateType(values, IBaseObject)]
    virtual ErrCode INTERFACE_FUNC getSuggestedValuesNoLock(IList** values) = 0;
    virtual ErrCode INTERFACE_FUNC getVisibleNoLock(Bool* visible) = 0;
    virtual ErrCode INTERFACE_FUNC getReadOnlyNoLock(Bool* readOnly) = 0;
    virtual ErrCode INTERFACE_FUNC getSelectionValuesNoLock(IBaseObject** values) = 0;
    virtual ErrCode INTERFACE_FUNC getReferencedPropertyNoLock(IProperty** propertyEval) = 0;
    virtual ErrCode INTERFACE_FUNC getIsReferencedNoLock(Bool* isReferenced) = 0;
    virtual ErrCode INTERFACE_FUNC getValidatorNoLock(IValidator** validator) = 0;
    virtual ErrCode INTERFACE_FUNC getCoercerNoLock(ICoercer** coercer) = 0;
    virtual ErrCode INTERFACE_FUNC getCallableInfoNoLock(ICallableInfo** callable) = 0;
    virtual ErrCode INTERFACE_FUNC getStructTypeNoLock(IStructType** structType) = 0;

    // Freezes default value
    virtual ErrCode INTERFACE_FUNC overrideDefaultValue(IBaseObject* newDefaultValue) = 0;
    virtual ErrCode INTERFACE_FUNC setValueProtected(IBaseObject* newValue) = 0;
};
/*!@}*/

END_NAMESPACE_OPENDAQ
