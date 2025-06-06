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
#include <opendaq/packet.h>
#include <opendaq/data_descriptor.h>
#include <coretypes/number.h>
#include <coretypes/type_manager.h>

BEGIN_NAMESPACE_OPENDAQ

/*#
 * [templated(defaultAliasName: DataPacketPtr)]
 * [interfaceSmartPtr(IDataPacket, GenericDataPacketPtr)]
 * [interfaceSmartPtr(IPacket, GenericPacketPtr)]
 * [interfaceLibrary(INumber, CoreTypes)]
 * [interfaceLibrary(ITypeManager, CoreTypes)]
 */

/*!
 * @ingroup opendaq_packets
 * @addtogroup opendaq_data_packet Data packet
 * @{
 */

/*!
 * @brief Packet that contains data sent by a signal. The data can be either explicit, or implicit.
 *
 * Explicit data is contained within a signal's buffer, accessible through `getRawData`, while implicit
 * packets do not carry any data. Their values are calculated given a rule, packet offset, and the index of
 * a sample within the data buffer.
 *
 * To obtain implicitly calculated, or scaled values, `getData` should be used. The data descriptor and sample
 * count provide information about the type and amount of data available at the obtained address.
 */
DECLARE_OPENDAQ_INTERFACE(IDataPacket, IPacket)
{
    /*!
     * @brief Gets the signal descriptor of the signal that sent the packet at the time of sending.
     * @param[out] descriptor The signal descriptor.
     */
    virtual ErrCode INTERFACE_FUNC getDataDescriptor(IDataDescriptor** descriptor) = 0;

    /*!
     * @brief Gets the number of samples in the packet.
     * @param[out] sampleCount the number of samples.
     */
    virtual ErrCode INTERFACE_FUNC getSampleCount(SizeT* sampleCount) = 0;

    /*!
     * @brief Gets current packet offset. This offset is later applied to the data rule used by a signal to calculate
     * actual data value. This value is usually a time or other domain value. Packet offset is particularly useful when
     * one wants to transfer a gap in otherwise equidistant samples.
     * If we have a linear data rule, defined by equation f(x) = k*x + n, then the data value will be calculated
     * by the equation g(x) = offset + f(x).
     *
     * @param[out] offset The packet offset
     */
    virtual ErrCode INTERFACE_FUNC getOffset(INumber** offset) = 0;

    // [rawBuffer(address, getDataSize)]
    /*!
     * @brief Gets the calculated/scaled data address of the packet.
     * @param[out] address The address of the data.
     *
     * `getData` uses the packet's data descriptor to calculate the values as follows:
     *   1. If the data rule is implicit, it uses the packet offset and sample count to calculate the data according to the rule.
     *   2. If the data rule is explicit:
     *      - If the data is a Struct, it returns a pointer to the raw data.
     *      - If no Post scaling is defined, it simply returns a pointer to the raw data.
     *      - If the Post scaling is defined, it scales the data and returns a pointer to the scaled data.
     *
     * The data should be cast to the appropriate type, as defined by the data descriptor, and read while keeping the
     * data dimensions in mind.
     */
    virtual ErrCode INTERFACE_FUNC getData(void** address) = 0;

    // [rawBuffer(address, getRawDataSize)]
    /*!
     * @brief Gets a pointer to the raw packet data. `nullptr` if the signal's data rule is implicit.
     * @param[out] address Pointer to the raw packet data.
     */
    virtual ErrCode INTERFACE_FUNC getRawData(void** address) = 0;

    /*!
     * @brief Gets size of data buffer in bytes.
     * @param[out] dataSize the size of data buffer in bytes.
     */
    virtual ErrCode INTERFACE_FUNC getDataSize(SizeT* dataSize) = 0;

    /*!
     * @brief Gets size of raw data buffer in bytes.
     * @param[out] dataSize the size of raw data buffer in bytes.
     *
     * Raw data size is 0 if signal's data rule is implicit.
     */
    virtual ErrCode INTERFACE_FUNC getRawDataSize(SizeT* rawDataSize) = 0;

    // [templateType(packet, IDataPacket)]
    /*!
     * @brief Gets the associated domain Data packet.
     * @param[out] packet The domain data packet.
     */
    virtual ErrCode INTERFACE_FUNC getDomainPacket(IDataPacket** packet) = 0;

    /*!
     * @brief Gets the unique packet id.
     * @param[out] packetId The packet unique id.
     *
     * The packet id is automatically created on packet construction.
     */
    virtual ErrCode INTERFACE_FUNC getPacketId(Int* packetId) = 0;

    /*!
     * @brief Gets the data packet last value.
     * @param[out] value The IBaseObject value can be a nullptr if there is no value, or if the data type is not supported by the function.
     * @param typeManager Optional ITypeManager value can be provided to enable getLastValue for IStruct.
     *
     * If a value is assigned, it can be cast based on the signal description to IFloat if the type is Float32 or Float64,
     * to IInteger if the type is Int8 through Int64 or UInt8 through UInt64, to IComplexNumber if the type is ComplexFloat32 or ComplexFloat64,
     * to IRange if the type is RangeInt64, to IStruct if the type is Struct, and to IList of the forementioned types if there is exactly
     * one dimension.
     */
    virtual ErrCode INTERFACE_FUNC getLastValue(IBaseObject** value, ITypeManager* typeManager = nullptr) = 0;

    /*!
     * @brief Gets the data packet last value.
     * @param[out] value The IBaseObject value can be a nullptr if there is no value, or if the data type is not supported by the function.
     * @param[in] index Index of the sample to obtain.
     * @param typeManager Optional ITypeManager value can be provided to enable getLastValue for IStruct.
     *
     * If a value is assigned, it can be cast based on the signal description to IFloat if the type is Float32 or Float64,
     * to IInteger if the type is Int8 through Int64 or UInt8 through UInt64, to IComplexNumber if the type is ComplexFloat32 or
     * ComplexFloat64, to IRange if the type is RangeInt64, to IStruct if the type is Struct, and to IList of the forementioned types if
     * there is exactly one dimension.
     */
    virtual ErrCode INTERFACE_FUNC getValueByIndex(IBaseObject** value, SizeT index, ITypeManager* typeManager = nullptr) = 0;

    /*!
     * @brief Gets the last raw value of the data packet.
     * @param[out] value A pointer to a memory location where the raw value will be stored.
     *
     * This method writes the raw value of the last sample to the provided memory location.
     * It does not allocate memory and assumes that sufficient memory has already been allocated.
     * The value is not cast to any specific type; it remains a raw data pointer.
     * The method does not verify whether the allocated memory size matches the sample size.
     */
    virtual ErrCode INTERFACE_FUNC getRawLastValue(void** value) = 0;

    /*!
     * @brief Gets the raw value of the data packet at the specified index.
     * @param[out] value A pointer to a memory location where the raw value will be stored.
     * @param[in] index The index of the sample to retrieve.
     *
     * This method writes the raw value of the sample at the specified index to the provided memory location.
     * It does not allocate memory and assumes that sufficient memory has already been allocated.
     * The value is not cast to any specific type; it remains a raw data pointer.
     * The method does not verify whether the allocated memory size matches the sample size.
     */
    virtual ErrCode INTERFACE_FUNC getRawValueByIndex(void** value, SizeT index) = 0;
};

/*!@}*/

/*!
 * @brief Creates a Data packet with a given descriptor, sample count, memory size of each sample,
 * and an optional packet offset.
 * @param descriptor The descriptor of the signal sending the data.
 * @param sampleCount The number of samples in the packet.
 * @param offset Optional packet offset parameter, used to calculate the data of the packet
 * if the Data rule of the Signal descriptor is not explicit.
 */
OPENDAQ_DECLARE_CLASS_FACTORY_WITH_INTERFACE(
    LIBRARY_FACTORY, DataPacket, IDataPacket,
    IDataDescriptor*, descriptor,
    SizeT, sampleCount,
    INumber*, offset
)

/*!
 * @brief Creates a Data packet with a given descriptor, sample count, an optional packet offset,
 * external memory location for data, custom deleter function and buffer size of external memory.
 * 
 * @param descriptor The descriptor of the signal sending the data.
 * @param sampleCount The number of samples in the packet.
 * @param offset Optional packet offset parameter, used to calculate the data of the packet
 * if the Data rule of the Signal descriptor is not explicit.
 * @param externalMemory The pointer to the location of buffer data.
 * @param deleter Custom deleter callback that is called when the packet is destroyed
 * @param bufferSize The size of the external memory.
 *
 * Use this factory when pointer to create a packet which uses an existing memory. The memory should not be
 * freed or written until the packet is destroyed. A deleter callback should be passed as a parameter that
 * is called when the packet is destroyed. The callback should free the memory provided. If bufferSize parameter
 * is equal to SizeT max, the buffer size will be calculated from the descriptor.
 */
OPENDAQ_DECLARE_CLASS_FACTORY_WITH_INTERFACE(
    LIBRARY_FACTORY, DataPacketWithExternalMemory, IDataPacket,
    IDataPacket*, domainPacket,
    IDataDescriptor*, descriptor,
    SizeT, sampleCount,
    INumber*, offset,
    void*, externalMemory,
    IDeleter*, deleter,
    SizeT, bufferSize
)

/*!
 * @brief Creates a Data packet with a given descriptor, sample count, memory size of each sample,
 * and an optional implicit value.
 * @param domainPacket The Data packet carrying domain data.
 * @param descriptor The descriptor of the signal sending the data.
 * @param sampleCount The number of samples in the packet.
 * @param offset Optional packet offset parameter, used to calculate the data of the packet
 * if the Data rule of the Signal descriptor is not explicit.
 *
 */
OPENDAQ_DECLARE_CLASS_FACTORY_WITH_INTERFACE(
    LIBRARY_FACTORY, DataPacketWithDomain, IDataPacket,
    IDataPacket*, domainPacket,
    IDataDescriptor*, descriptor,
    SizeT, sampleCount,
    INumber*, offset
)

/*!
 * @brief Creates a Data packet with a given constat rule descriptor, initial constant value,
 * and other constant values.
 * @param domainPacket The Data packet carrying domain data.
 * @param descriptor The descriptor of the signal sending the data.
 * @param sampleCount The number of samples in the packet.
 * @param initialValue The initial constant value.
 * @param otherValues The other constant values. 
 * @param otherValueCount The number of other constant values.
 *
 * The values in the packet are calculated by constant rule. The initial value is taken as a constant.
 * Other values are used to change the constant value within the packet. Any number of other constant values
 * can be used. Other values are passed as an array of struct with uint32_t sample position field and value field.
 * Value field (as well as initial value) are of type defined as sample type in the descriptor.
 */
OPENDAQ_DECLARE_CLASS_FACTORY_WITH_INTERFACE(
    LIBRARY_FACTORY, ConstantDataPacketWithDomain, IDataPacket,
    IDataPacket*, domainPacket,
    IDataDescriptor*, descriptor,
    SizeT, sampleCount,
    void*, initialValue,
    void*, otherValues,
    SizeT, otherValueCount)

END_NAMESPACE_OPENDAQ
