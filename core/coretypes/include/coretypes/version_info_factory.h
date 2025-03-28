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
#include <coretypes/version_info_ptr.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @brief Creates a new Version Info object.
 * @param major The major version component.
 * @param minor The minor version component.
 * @param patch The patch version component.
 * @return The Version Info object.
 */

inline VersionInfoPtr VersionInfo(SizeT major, SizeT minor, SizeT patch)
{
    return VersionInfoPtr{VersionInfo_Create(major, minor, patch)};
}

/*!
 * @brief Creates the Struct type object that defines the Version Info struct.
 */
inline StructTypePtr VersionInfoStructType()
{
    return StructType("VersionInfo",
                      List<IString>("Major", "Minor", "Patch"),
                      List<IBaseObject>(0, 0, 0),
                      List<IType>(SimpleType(ctInt), SimpleType(ctInt), SimpleType(ctInt)));
}

/*!@}*/

END_NAMESPACE_OPENDAQ
