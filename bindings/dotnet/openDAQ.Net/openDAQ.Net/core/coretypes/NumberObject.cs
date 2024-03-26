/*
 * Copyright 2022-2024 Blueberry d.o.o.
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


//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CSharpGenerator v1.0.0) on D-E-B-U-G.
// </auto-generated>
//------------------------------------------------------------------------------


namespace Daq.Core.Types;


[StructLayout(LayoutKind.Sequential)]
internal unsafe class RawNumberObject : RawBaseObject
{
    //ErrorCode getFloatValue(daq.Float* value); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out double, ErrorCode> GetFloatValue;
    //ErrorCode getIntValue(daq.Int* value); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out long, ErrorCode> GetIntValue;
}

/// <summary>Represents either a float or an int number.</summary>
/// <remarks>
/// Number is used if data type of the number is not strictly defined, i.e.
/// it can accept a float or an int.
/// </remarks>
[Guid("52711b8d-df25-59b0-af86-1015c7b54603")]
public class NumberObject : BaseObject
{
    //type-casted base._virtualTable
    private readonly RawNumberObject _rawNumberObject;

    internal NumberObject(IntPtr nativePointer, bool incrementReference)
        : base(nativePointer, incrementReference)
    {
        IntPtr objVirtualTable = Marshal.ReadIntPtr(nativePointer, 0); //read the pointer from the given address
        base._virtualTable =
            _rawNumberObject = Marshal.PtrToStructure<RawNumberObject>(objVirtualTable);
    }

    /// <summary>Gets a value stored in the object as a floating point value.</summary>
    /// <returns>Stored value as a floating point.</returns>
    public double GetFloatValue()
    {
        //native output argument
        double value;

        unsafe //use native function pointer
        {
            //call native function
            ErrorCode errorCode = (ErrorCode)_rawNumberObject.GetFloatValue(base.NativePointer, out value);

            if (Result.Failed(errorCode))
            {
                throw new OpenDaqException(errorCode);
            }
        }

        return value;
    }

    /// <summary>Gets a value stored in the object as an integer value.</summary>
    /// <returns>Stored value as an integer.</returns>
    public long GetIntValue()
    {
        //native output argument
        long value;

        unsafe //use native function pointer
        {
            //call native function
            ErrorCode errorCode = (ErrorCode)_rawNumberObject.GetIntValue(base.NativePointer, out value);

            if (Result.Failed(errorCode))
            {
                throw new OpenDaqException(errorCode);
            }
        }

        return value;
    }
}


#region Class Factory

// Factory functions of the &apos;CoreTypes&apos; library.
public static partial class CoreTypesFactory
{
}

#endregion Class Factory
