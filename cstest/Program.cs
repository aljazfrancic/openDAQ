using Daq.Core.Types;
using Daq.Core.Objects;
using Daq.Core.OpenDAQ;


var instance = OpenDAQFactory.Instance();
var dev = instance.AddDevice("daq://openDAQ_007");
var myStructProp = dev.GetProperty("MyStructProp");
var mySymbol = myStructProp.Unit.Symbol;
Console.WriteLine(mySymbol);
Console.ReadLine();
