using Daq.Core.Types;
using Daq.Core.Objects;
using Daq.Core.OpenDAQ;


var instance = OpenDAQFactory.Instance();
var dev = instance.AddDevice("daq://openDAQ_007");

var myStructProp = dev.GetPropertyValue("MyStructProp");
var myStruct = myStructProp.Cast<Struct>();
String myString = myStruct.Get("FieldName");
Console.WriteLine(myString);
Console.ReadLine();