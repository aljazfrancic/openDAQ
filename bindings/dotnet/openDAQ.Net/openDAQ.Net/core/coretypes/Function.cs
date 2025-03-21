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


//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//
//     RTGen (CSharpGenerator v1.0.0) on 04.09.2024 17:45:20.
// </auto-generated>
//------------------------------------------------------------------------------


namespace Daq.Core.Types;


[StructLayout(LayoutKind.Sequential)]
internal unsafe class RawFunction : RawBaseObject
{
    //ErrorCode call(daq.IBaseObject* params, daq.IBaseObject** result); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, IntPtr, out IntPtr, ErrorCode> Call;
}

/// <summary>Holds a callback function.</summary>
/// <remarks>
/// Represents a callable object. The openDAQ SDK uses this interface when it needs to make
/// a call back to the client.
/// <para/>
/// Although the implementation of this interface is provided by openDAQ, C++ and other
/// bindings provide their implementation which allows passing function as a lambda
/// functions and other constructs.
/// Available factories:
/// <code>
/// // Creates a new Function object. Throws exception if not successful.
/// IFunction* Function_Create(FuncCall value)
///
/// // Creates a new Function object. Returns error code if not successful.
/// ErrCode createFunction(IFuncObject** obj, FuncCall value)
/// </code>
/// </remarks>
[Guid("2eeacd91-0883-5fc8-8eb8-4f4c80cd8131")]
public class Function : BaseObject
{
    //type-casted base._virtualTable
    private readonly RawFunction _rawFunction;

    internal Function(IntPtr nativePointer, bool incrementReference)
        : base(nativePointer, incrementReference)
    {
        IntPtr objVirtualTable = Marshal.ReadIntPtr(nativePointer, 0); //read the pointer from the given address
        base._virtualTable =
            _rawFunction = Marshal.PtrToStructure<RawFunction>(objVirtualTable);
    }

    /// <summary>Calls the stored callback.</summary>
    /// <remarks>
    /// If the callback expects no parameters, the <c>params</c> parameter has to be <c>null</c>. If it
    /// expects a single parameter, pass any openDAQ object as the <c>params</c> parameter.
    /// If it expects multiple parameters, pass an IList&lt;IBaseObject&gt; as the <c>params</c> parameter.
    /// </remarks>
    /// <param name="params">Parameters passed to the callback.</param>
    /// <returns>Return value of the callback.</returns>
    public BaseObject Call(BaseObject @params)
    {
        //native output argument
        IntPtr resultPtr;

        unsafe //use native function pointer
        {
            //call native function
            ErrorCode errorCode = (ErrorCode)_rawFunction.Call(base.NativePointer, @params, out resultPtr);

            if (Result.Failed(errorCode))
            {
                throw new OpenDaqException(errorCode);
            }
        }

        // validate pointer
        if (resultPtr == IntPtr.Zero)
        {
            return default;
        }

        return new BaseObject(resultPtr, incrementReference: false);
    }
}


#region Class Factory

// Factory functions of the &apos;CoreTypes&apos; library.
public static partial class CoreTypesFactory
{
    //ErrorCode createFunction(daq.IFunction** obj, daq.FuncCall value); cdecl;
    [DllImport(CoreTypesDllInfo.FileName, CallingConvention = CallingConvention.Cdecl)]
    private static extern ErrorCode createFunction(out IntPtr obj, FuncCall value);

    public static ErrorCode CreateFunction(out Function obj, FuncCallDelegate value)
    {
        //initialize output argument
        obj = default;

        //native output argument
        IntPtr objPtr;

        //wrap SDK delegate around .NET delegate
        var wrappedValue = CreateFuncCallWrapper(value);

        //call native function
        ErrorCode errorCode = createFunction(out objPtr, wrappedValue);

        if (Result.Succeeded(errorCode))
        {
            //create object
            obj = new Function(objPtr, incrementReference: false);
        }

        return errorCode;
    }

    public static Function CreateFunction(FuncCallDelegate value)
    {
        //native output argument
        IntPtr objPtr;

        //wrap SDK delegate around .NET delegate
        var wrappedValue = CreateFuncCallWrapper(value);

        //call native function
        ErrorCode errorCode = createFunction(out objPtr, wrappedValue);

        if (Result.Failed(errorCode))
        {
            throw new OpenDaqException(errorCode);
        }

        //create and return object
        return new Function(objPtr, incrementReference: false);
    }
}

#endregion Class Factory
