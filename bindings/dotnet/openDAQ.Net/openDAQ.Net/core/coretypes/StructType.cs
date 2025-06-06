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
//     RTGen (CSharpGenerator v1.0.0) on 04.09.2024 17:45:25.
// </auto-generated>
//------------------------------------------------------------------------------


namespace Daq.Core.Types;


[StructLayout(LayoutKind.Sequential)]
internal unsafe class RawStructType : RawDaqType
{
    //ErrorCode getFieldNames(daq.IList** names); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out IntPtr, ErrorCode> GetFieldNames;
    //ErrorCode getFieldDefaultValues(daq.IList** defaultValues); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out IntPtr, ErrorCode> GetFieldDefaultValues;
    //ErrorCode getFieldTypes(daq.IList** types); stdcall;
    public delegate* unmanaged[Stdcall]<IntPtr, out IntPtr, ErrorCode> GetFieldTypes;
}

/// <summary>
/// Struct types define the fields (names and value types, as well as optional default values) of Structs with a name
/// matching that of the Struct type.
/// </summary>
/// <remarks>
/// A Struct type contains a String-type name, a list of field names (list of Strings), a list of field types (list of Type objects),
/// and an optional list of Default values (list of Base objects). The Struct types should be added to the Type manager to be used
/// for Struct validation on creation. Alternatively, if a Struct is created with no matching Struct type in the manager, a default
/// Struct type is created based on the field names and types of the Created struct. Said Struct type is then added to the manager.
/// <para/>
/// The field types are a list of Type objects. These determine the types of values that should be used to fill in the corresponding
/// field value. The Type objects at the moment available in openDAQ are Simple types and Struct types. When adding any field other
/// than a Struct type, the Simple type corresponding to the Core type of the value should be created. When adding Struct fields, a
/// Struct type should be added to the field types.
/// <para/>
/// A Struct can only have fields of Core type: <c>ctBool</c>, <c>ctInt</c>, <c>ctFloat</c>, <c>ctString</c>, <c>ctList</c>, <c>ctDict</c>, <c>ctRatio</c>, <c>ctComplexNumber</c>,
/// <c>ctStruct</c>, or <c>ctUndefined</c>. Additionally, all Container types (<c>ctList</c>, <c>ctDict</c>) should only have values of the aforementioned
/// types.
/// </remarks>
[Guid("2ac3d9fa-7059-5bef-8439-351258ddbe72")]
public class StructType : DaqType
{
    //type-casted base._virtualTable
    private readonly RawStructType _rawStructType;

    internal StructType(IntPtr nativePointer, bool incrementReference)
        : base(nativePointer, incrementReference)
    {
        IntPtr objVirtualTable = Marshal.ReadIntPtr(nativePointer, 0); //read the pointer from the given address
        base._virtualTable =
            _rawStructType = Marshal.PtrToStructure<RawStructType>(objVirtualTable);
    }

    #region properties

    /// <summary>Gets the list of field names.</summary>
    public IListObject<StringObject> FieldNames
    {
        get
        {
            //native output argument
            IntPtr namesPtr;

            unsafe //use native function pointer
            {
                //call native function
                ErrorCode errorCode = (ErrorCode)_rawStructType.GetFieldNames(base.NativePointer, out namesPtr);

                if (Result.Failed(errorCode))
                {
                    throw new OpenDaqException(errorCode);
                }
            }

            // validate pointer
            if (namesPtr == IntPtr.Zero)
            {
                return default;
            }

            return new ListObject<StringObject>(namesPtr, incrementReference: false);
        }
    }

    /// <summary>Gets the list of field default values.</summary>
    public IListObject<BaseObject> FieldDefaultValues
    {
        get
        {
            //native output argument
            IntPtr defaultValuesPtr;

            unsafe //use native function pointer
            {
                //call native function
                ErrorCode errorCode = (ErrorCode)_rawStructType.GetFieldDefaultValues(base.NativePointer, out defaultValuesPtr);

                if (Result.Failed(errorCode))
                {
                    throw new OpenDaqException(errorCode);
                }
            }

            // validate pointer
            if (defaultValuesPtr == IntPtr.Zero)
            {
                return default;
            }

            return new ListObject<BaseObject>(defaultValuesPtr, incrementReference: false);
        }
    }

    /// <summary>Gets the list of field types.</summary>
    public IListObject<DaqType> FieldTypes
    {
        get
        {
            //native output argument
            IntPtr typesPtr;

            unsafe //use native function pointer
            {
                //call native function
                ErrorCode errorCode = (ErrorCode)_rawStructType.GetFieldTypes(base.NativePointer, out typesPtr);

                if (Result.Failed(errorCode))
                {
                    throw new OpenDaqException(errorCode);
                }
            }

            // validate pointer
            if (typesPtr == IntPtr.Zero)
            {
                return default;
            }

            return new ListObject<DaqType>(typesPtr, incrementReference: false);
        }
    }

    #endregion properties
}


#region Class Factory

// Factory functions of the &apos;CoreTypes&apos; library.
public static partial class CoreTypesFactory
{
    //ErrorCode createStructType(daq.IStructType** obj, daq.IString* name, daq.IList* names, daq.IList* defaultValues, daq.IList* types); cdecl;
    [DllImport(CoreTypesDllInfo.FileName, CallingConvention = CallingConvention.Cdecl)]
    private static extern ErrorCode createStructType(out IntPtr obj, IntPtr name, IntPtr names, IntPtr defaultValues, IntPtr types);

    public static ErrorCode CreateStructType(out StructType obj, string name, IListObject<BaseObject> names, IListObject<BaseObject> defaultValues, IListObject<BaseObject> types)
    {
        //initialize output argument
        obj = default;

        //native output argument
        IntPtr objPtr;

        //cast .NET argument to SDK object
        using var namePtr = (StringObject)name;
        var namesPtr = (ListObject<BaseObject>)names;
        var defaultValuesPtr = (ListObject<BaseObject>)defaultValues;
        var typesPtr = (ListObject<BaseObject>)types;

        //call native function
        ErrorCode errorCode = createStructType(out objPtr, namePtr, namesPtr, defaultValuesPtr, typesPtr);

        if (Result.Succeeded(errorCode))
        {
            //create object
            obj = new StructType(objPtr, incrementReference: false);
        }

        return errorCode;
    }

    public static StructType CreateStructType(string name, IListObject<BaseObject> names, IListObject<BaseObject> defaultValues, IListObject<BaseObject> types)
    {
        //native output argument
        IntPtr objPtr;

        //cast .NET argument to SDK object
        using var namePtr = (StringObject)name;
        var namesPtr = (ListObject<BaseObject>)names;
        var defaultValuesPtr = (ListObject<BaseObject>)defaultValues;
        var typesPtr = (ListObject<BaseObject>)types;

        //call native function
        ErrorCode errorCode = createStructType(out objPtr, namePtr, namesPtr, defaultValuesPtr, typesPtr);

        if (Result.Failed(errorCode))
        {
            throw new OpenDaqException(errorCode);
        }

        //create and return object
        return new StructType(objPtr, incrementReference: false);
    }


    //ErrorCode createStructTypeNoDefaults(daq.IStructType** obj, daq.IString* name, daq.IList* names, daq.IList* types); cdecl;
    [DllImport(CoreTypesDllInfo.FileName, CallingConvention = CallingConvention.Cdecl)]
    private static extern ErrorCode createStructTypeNoDefaults(out IntPtr obj, IntPtr name, IntPtr names, IntPtr types);

    public static ErrorCode CreateStructTypeNoDefaults(out StructType obj, string name, IListObject<BaseObject> names, IListObject<BaseObject> types)
    {
        //initialize output argument
        obj = default;

        //native output argument
        IntPtr objPtr;

        //cast .NET argument to SDK object
        using var namePtr = (StringObject)name;
        var namesPtr = (ListObject<BaseObject>)names;
        var typesPtr = (ListObject<BaseObject>)types;

        //call native function
        ErrorCode errorCode = createStructTypeNoDefaults(out objPtr, namePtr, namesPtr, typesPtr);

        if (Result.Succeeded(errorCode))
        {
            //create object
            obj = new StructType(objPtr, incrementReference: false);
        }

        return errorCode;
    }

    public static StructType CreateStructTypeNoDefaults(string name, IListObject<BaseObject> names, IListObject<BaseObject> types)
    {
        //native output argument
        IntPtr objPtr;

        //cast .NET argument to SDK object
        using var namePtr = (StringObject)name;
        var namesPtr = (ListObject<BaseObject>)names;
        var typesPtr = (ListObject<BaseObject>)types;

        //call native function
        ErrorCode errorCode = createStructTypeNoDefaults(out objPtr, namePtr, namesPtr, typesPtr);

        if (Result.Failed(errorCode))
        {
            throw new OpenDaqException(errorCode);
        }

        //create and return object
        return new StructType(objPtr, incrementReference: false);
    }
}

#endregion Class Factory
