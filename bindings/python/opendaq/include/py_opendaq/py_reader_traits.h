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

#include <cstddef>
#include <utility>

template <typename ReaderType, typename = void>
struct ReaderHasReadWithTimeout : std::false_type
{
};

template <typename ReaderType>
struct ReaderHasReadWithTimeout<
    ReaderType,
    std::void_t<decltype(std::declval<ReaderType>().read(std::declval<void*>(), std::declval<size_t*>(), std::declval<size_t>()))>>
    : std::true_type
{
};
