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


//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CSharpGenerator v1.0.0) on 25.06.2024 08:46:46.
// </auto-generated>
//------------------------------------------------------------------------------


namespace Daq.Core.Types;


[StructLayout(LayoutKind.Sequential)]
internal unsafe class RawRatio : RawBaseObject
{
    //ErrorCode getNumerator(daq.Int* numerator); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out long, ErrorCode> GetNumerator;
    //ErrorCode getDenominator(daq.Int* denominator); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out long, ErrorCode> GetDenominator;
    //ErrorCode simplify(daq.IRatio** simplifiedRatio); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out IntPtr, ErrorCode> Simplify;
}

[Guid("08d28c13-55a6-5fe5-a0f0-19a3f8707c15")]
public class Ratio : BaseObject
{
    //type-casted base._virtualTable
    private readonly RawRatio _rawRatio;

    internal Ratio(IntPtr nativePointer, bool incrementReference)
        : base(nativePointer, incrementReference)
    {
        IntPtr objVirtualTable = Marshal.ReadIntPtr(nativePointer, 0); //read the pointer from the given address
        base._virtualTable =
            _rawRatio = Marshal.PtrToStructure<RawRatio>(objVirtualTable);
    }

    #region properties

    /// <summary>Gets numerator part.</summary>
    public long Numerator
    {
        get
        {
            //native output argument
            long numerator;

            unsafe //use native function pointer
            {
                //call native function
                ErrorCode errorCode = (ErrorCode)_rawRatio.GetNumerator(base.NativePointer, out numerator);

                if (Result.Failed(errorCode))
                {
                    throw new OpenDaqException(errorCode);
                }
            }

            return numerator;
        }
    }

    /// <summary>Gets denominator part.</summary>
    public long Denominator
    {
        get
        {
            //native output argument
            long denominator;

            unsafe //use native function pointer
            {
                //call native function
                ErrorCode errorCode = (ErrorCode)_rawRatio.GetDenominator(base.NativePointer, out denominator);

                if (Result.Failed(errorCode))
                {
                    throw new OpenDaqException(errorCode);
                }
            }

            return denominator;
        }
    }

    #endregion properties

    /// <summary>Simplifies rational number if possible and returns the simplified ratio as a new object.</summary>
    /// <remarks>
    /// Call this method to reduce stored rational number to the lowest terms possible.
    /// Example: 10/100 is reduced to 1/10.
    /// </remarks>
    /// <returns>the simplified ratio.</returns>
    public Ratio Simplify()
    {
        //native output argument
        IntPtr simplifiedRatioPtr;

        unsafe //use native function pointer
        {
            //call native function
            ErrorCode errorCode = (ErrorCode)_rawRatio.Simplify(base.NativePointer, out simplifiedRatioPtr);

            if (Result.Failed(errorCode))
            {
                throw new OpenDaqException(errorCode);
            }
        }

        // validate pointer
        if (simplifiedRatioPtr == IntPtr.Zero)
        {
            return default;
        }

        return new Ratio(simplifiedRatioPtr, incrementReference: false);
    }
}


#region Class Factory

// Factory functions of the &apos;CoreTypes&apos; library.
public static partial class CoreTypesFactory
{
    //ErrorCode createRatio(daq.IRatio** obj, daq.Int numerator, daq.Int denominator); cdecl;
    [DllImport(CoreTypesDllInfo.FileName, CallingConvention = CallingConvention.Cdecl)]
    private static extern ErrorCode createRatio(out IntPtr obj, long numerator, long denominator);

    public static ErrorCode CreateRatio(out Ratio obj, long numerator, long denominator)
    {
        //initialize output argument
        obj = default;

        //native output argument
        IntPtr objPtr;

        //call native function
        ErrorCode errorCode = createRatio(out objPtr, numerator, denominator);

        if (Result.Succeeded(errorCode))
        {
            //create object
            obj = new Ratio(objPtr, incrementReference: false);
        }

        return errorCode;
    }

    public static Ratio CreateRatio(long numerator, long denominator)
    {
        //native output argument
        IntPtr objPtr;

        //call native function
        ErrorCode errorCode = createRatio(out objPtr, numerator, denominator);

        if (Result.Failed(errorCode))
        {
            throw new OpenDaqException(errorCode);
        }

        //create and return object
        return new Ratio(objPtr, incrementReference: false);
    }
}

#endregion Class Factory
