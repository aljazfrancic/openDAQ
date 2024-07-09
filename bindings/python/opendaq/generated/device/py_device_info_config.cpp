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

#include "py_opendaq/py_opendaq.h"
#include "py_core_types/py_converter.h"

PyDaqIntf<daq::IDeviceInfoConfig, daq::IDeviceInfo> declareIDeviceInfoConfig(pybind11::module_ m)
{
    return wrapInterface<daq::IDeviceInfoConfig, daq::IDeviceInfo>(m, "IDeviceInfoConfig");
}

void defineIDeviceInfoConfig(pybind11::module_ m, PyDaqIntf<daq::IDeviceInfoConfig, daq::IDeviceInfo> cls)
{
    cls.doc() = "Configuration component of Device info objects. Contains setter methods that are available until the object is frozen.";

    m.def("DeviceInfoConfig", &daq::DeviceInfoConfig_Create);
    m.def("DeviceInfoConfigWithCustomSdkVersion", &daq::DeviceInfoConfigWithCustomSdkVersion_Create);

    cls.def_property("name",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& name)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setName(name);
        },
        "Sets the name of the device");
    cls.def_property("connection_string",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& connectionString)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setConnectionString(connectionString);
        },
        "Sets the string representation of a connection address used to connect to the device.");
    cls.def_property("device_type",
        nullptr,
        [](daq::IDeviceInfoConfig *object, daq::IDeviceType* deviceType)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setDeviceType(deviceType);
        },
        "Sets a device type as an object providing type id, name, short description and default device configuration.");
    cls.def_property("manufacturer",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& manufacturer)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setManufacturer(manufacturer);
        },
        "Sets the company that manufactured the device");
    cls.def_property("manufacturer_uri",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& manufacturerUri)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setManufacturerUri(manufacturerUri);
        },
        "Sets the unique identifier of the company that manufactured the device. This identifier should be a fully qualified domain name; however, it may be a GUID or similar construct that ensures global uniqueness.");
    cls.def_property("model",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& model)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setModel(model);
        },
        "Sets the model of the device");
    cls.def_property("product_code",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& productCode)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setProductCode(productCode);
        },
        "Sets the unique combination of numbers and letters used to identify the device.");
    cls.def_property("device_revision",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& deviceRevision)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setDeviceRevision(deviceRevision);
        },
        "Sets the revision level of the device.");
    cls.def_property("hardware_revision",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& hardwareRevision)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setHardwareRevision(hardwareRevision);
        },
        "Sets the revision level of the hardware");
    cls.def_property("software_revision",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& softwareRevision)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setSoftwareRevision(softwareRevision);
        },
        "sets the revision level of the software component");
    cls.def_property("device_manual",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& deviceManual)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setDeviceManual(deviceManual);
        },
        "Sets the address of the user manual. It may be a pathname in the file system or a URL (Web address)");
    cls.def_property("device_class",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& deviceClass)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setDeviceClass(deviceClass);
        },
        "Sets the purpose of the device. For example \"TestMeasurementDevice\".");
    cls.def_property("serial_number",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& serialNumber)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setSerialNumber(serialNumber);
        },
        "Sets the serial number of the device");
    cls.def_property("product_instance_uri",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& productInstanceUri)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setProductInstanceUri(productInstanceUri);
        },
        "Sets the globally unique resource identifier provided by the manufacturer. The recommended syntax of the ProductInstanceUri is: <ManufacturerUri>/<any string> where <any string> is unique among all instances using the same ManufacturerUri.");
    cls.def_property("revision_counter",
        nullptr,
        [](daq::IDeviceInfoConfig *object, daq::Int revisionCounter)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setRevisionCounter(revisionCounter);
        },
        "Sets the incremental counter indicating the number of times the configuration data has been modified.");
    cls.def_property("asset_id",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& id)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setAssetId(id);
        },
        "Sets the asset ID of the device. Represents a user writable alphanumeric character sequence uniquely identifying a component.");
    cls.def_property("mac_address",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& macAddress)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setMacAddress(macAddress);
        },
        "Sets the Mac address of the device.");
    cls.def_property("parent_mac_address",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& macAddress)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setParentMacAddress(macAddress);
        },
        "Sets the Mac address of the device's parent.");
    cls.def_property("platform",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& platform)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setPlatform(platform);
        },
        "Sets the platform of the device. The platform specifies whether real hardware is used or if the device is simulated.");
    cls.def_property("position",
        nullptr,
        [](daq::IDeviceInfoConfig *object, daq::Int position)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setPosition(position);
        },
        "Sets the position of the device. The position specifies the position within a given system. For example in which slot or slice the device is in.");
    cls.def_property("system_type",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& type)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setSystemType(type);
        },
        "Sets the system type. The system type can, for example, be LayeredSystem, StandaloneSystem, or RackSystem.");
    cls.def_property("system_uuid",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& uuid)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setSystemUuid(uuid);
        },
        "Sets the system UUID that represents a unique ID of a system. All devices in a system share this UUID.");
    cls.def_property("location",
        nullptr,
        [](daq::IDeviceInfoConfig *object, const std::string& location)
        {
            const auto objectPtr = daq::DeviceInfoConfigPtr::Borrow(object);
            objectPtr.setLocation(location);
        },
        "Sets the device's location.");
}
