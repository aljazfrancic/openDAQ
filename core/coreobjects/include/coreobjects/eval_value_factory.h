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
#include <coreobjects/eval_value_ptr.h>
#include <coretypes/listobject_factory.h>

BEGIN_NAMESPACE_OPENDAQ

inline EvalValuePtr EvalValue(const StringPtr& eval)
{
    EvalValuePtr obj(EvalValue_Create(eval));
    checkErrorInfo(obj->getParseErrorCode());
    return obj;
}

inline EvalValuePtr EvalValueFunc(const StringPtr& eval, const FunctionPtr& func)
{
    EvalValuePtr obj(EvalValueFunc_Create(eval, func));
    checkErrorInfo(obj->getParseErrorCode());
    return obj;
}

template <typename... TArgs>
EvalValuePtr EvalValue(StringPtr eval, TArgs&&... args)
{
    EvalValuePtr obj(EvalValueArgs_Create(eval, List<IBaseObject>(std::forward<decltype(args)>(args)...)));
    checkErrorInfo(obj->getParseErrorCode());
    return obj;
}

inline EvalValuePtr Bind(const std::string& propertyName, const PropertyObjectPtr& propObj)
{
    return EvalValue(std::string("{0}.$") + propertyName, propObj);
}

inline EvalValuePtr operator""_eval(const char* eval, std::size_t /*size*/)
{
    return EvalValue(eval);
}

END_NAMESPACE_OPENDAQ
