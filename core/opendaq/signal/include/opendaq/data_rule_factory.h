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
#include <opendaq/data_rule_ptr.h>
#include <opendaq/data_rule_builder_ptr.h>
#include <coretypes/struct_type_factory.h>
#include <coretypes/simple_type_factory.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @ingroup opendaq_data_rule
 * @addtogroup opendaq_data_rule_factories Factories
 * @{
 */

/*!
 * @brief Creates a DataRuleConfig with no parameters.
 */
inline DataRulePtr DataRule(DataRuleType type, const DictPtr<IString, IBaseObject>& parameters)
{
    DataRulePtr obj(DataRule_Create(type, parameters));
    return obj;
}

/*!
 * @brief Creates a DataRulePtr from Builder.
 * @param builder DataRule Builder
 */
inline DataRulePtr DataRuleFromBuilder(const DataRuleBuilderPtr& builder)
{
    DataRulePtr obj(DataRuleFromBuilder_Create(builder));
    return obj;
}

/*!
 * @brief Creates a DataRule with a Linear rule type configuration.
 *
 * @param delta Coefficient by which the input data is to be multiplied.
 * @param start Constant that is added to the <em>scale * value</em> multiplication result.
 *
 * The scale and offset are stored within the `parameters` member of the Rule object
 * with the scale being at the first position of the list, and the offset at the second.
 */
inline DataRulePtr LinearDataRule(const NumberPtr& delta, const NumberPtr& start)
{
    DataRulePtr obj(LinearDataRule_Create(delta, start));
    return obj;
}

/*!
 * @brief Creates a DataRule with a Constant rule type configuration.
 */
inline DataRulePtr ConstantDataRule()
{
    DataRulePtr obj(ConstantDataRule_Create());
    return obj;
}

/*!
 * @brief Creates a DataRule with an Explicit rule type configuration and no parameters.
 */
inline DataRulePtr ExplicitDataRule()
{
    DataRulePtr obj(ExplicitDataRule_Create());
    return obj;
}

/*!
 * @brief Creates a DataRule with an Explicit rule type configuration two optional parameters.
 * @param minExpectedDelta The lowest expected distance between two samples.
 * @param maxExpectedDelta The highest expected distance between two samples.
 *
 * Most often used for domain signals to specify estimates on how close together/far apart two
 * subsequent samples might be.
 */
inline DataRulePtr ExplicitDomainDataRule(const NumberPtr& minExpectedDelta = 0, const NumberPtr& maxExpectedDelta = 0)
{
    DataRulePtr obj(ExplicitDomainDataRule_Create(minExpectedDelta, maxExpectedDelta));
    return obj;
}

/*!
 * @brief Creates a Data rule builder with no parameters.
 */
inline DataRuleBuilderPtr DataRuleBuilder()
{
    DataRuleBuilderPtr obj(DataRuleBuilder_Create());
    return obj;
}

/*!
 * @brief Dat rule copy factory that creates a Data rule builder object from a
 * non-configurable Data rule.
 * @param rule The rule of which configuration should be copied.
 */
inline DataRuleBuilderPtr DataRuleBuilderCopy(const DataRulePtr& rule)
{
    DataRuleBuilderPtr obj(DataRuleBuilderFromExisting_Create(rule));
    return obj;
}

/*!
 * @brief Creates the Struct type object that defines the Data rule struct.
 */
inline StructTypePtr DataRuleStructType()
{
    return StructType("DataRule",
                   List<IString>("Type", "Parameters"),
                   List<IBaseObject>(0, Dict<IString, IBaseObject>()),
                   List<IType>(SimpleType(ctInt), SimpleType(ctDict)));
}

/*!@}*/

END_NAMESPACE_OPENDAQ
