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

/*#
 * [interfaceSmartPtr(IPropertyObject, PropertyObjectPtr, "<coreobjects/property_object_ptr.h>")]
 * [interfaceSmartPtr(IUser, UserPtr, "<coreobjects/user_ptr.h>")]
 */

/*!
 * @ingroup opendaq_devices
 * @addtogroup opendaq_device Device private
 * @{
 */

DECLARE_OPENDAQ_INTERFACE(IDevicePrivate, IBaseObject)
{
    virtual ErrCode INTERFACE_FUNC setAsRoot() = 0;
    virtual ErrCode INTERFACE_FUNC setDeviceConfig(IPropertyObject* config) = 0;
    virtual ErrCode INTERFACE_FUNC getDeviceConfig(IPropertyObject** config) = 0;
    virtual ErrCode INTERFACE_FUNC lock(IUser * user) = 0;
    virtual ErrCode INTERFACE_FUNC unlock(IUser * user) = 0;
    virtual ErrCode INTERFACE_FUNC isLockedInternal(Bool * locked) = 0;
    virtual ErrCode INTERFACE_FUNC forceUnlock() = 0;
};
/*!@}*/

END_NAMESPACE_OPENDAQ
