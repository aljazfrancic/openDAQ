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

#include <opendaq/folder_config.h>

BEGIN_NAMESPACE_OPENDAQ

/*!
 * @ingroup opendaq_components
 * @addtogroup opendaq_component IoFolder
 * @{
 */

/*#
 * [interfaceSmartPtr(IFolderConfig, GenericFolderConfigPtr, "<opendaq/folder_config_ptr.h>")]
 */

/*!
 * @brief Acts as a container for channels and other io folders.
 *
 * Every device has an IO folder, which allows only other IO folders and
 * channels as children.
 */
DECLARE_OPENDAQ_INTERFACE(IIoFolderConfig, IFolderConfig)
{
};
/*!@}*/

END_NAMESPACE_OPENDAQ
