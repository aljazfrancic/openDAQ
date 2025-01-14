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

#define OPENDAQ__EXPAND(x) x
#define OPENDAQ__STRIP_PAR(...) __VA_ARGS__

#define FOR_EACH_1_0(what, intf, T, x)
#define FOR_EACH_1_1(what, intf, T, x)      what(intf, T, x)
#define FOR_EACH_1_2(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_1(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_3(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_2(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_4(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_3(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_5(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_4(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_6(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_5(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_7(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_6(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_8(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_7(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_9(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_8(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_10(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_9(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_11(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_10(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_12(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_11(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_13(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_12(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_14(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_13(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_15(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_14(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_16(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_15(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_17(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_16(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_18(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_17(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_19(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_18(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_20(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_19(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_21(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_20(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_22(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_21(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_23(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_22(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_24(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_23(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_25(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_24(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_26(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_25(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_27(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_26(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_28(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_27(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_29(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_28(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_30(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_29(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_31(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_30(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_32(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_31(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_33(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_32(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_34(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_33(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_35(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_34(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_36(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_35(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_37(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_36(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_38(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_37(what, intf, T, __VA_ARGS__))
#define FOR_EACH_1_39(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_38(what, intf, T, __VA_ARGS__))

#define _FOR_EACH_1_0(what, intf, T, x)
#define _FOR_EACH_1_1(what, intf, T, x)      what(intf, T, x)
#define _FOR_EACH_1_2(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_1(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_3(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_2(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_4(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_3(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_5(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_4(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_6(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_5(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_7(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_6(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_8(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_7(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_9(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_8(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_10(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_9(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_11(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_10(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_12(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_11(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_13(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_12(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_14(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_13(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_15(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_14(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_16(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_15(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_17(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_16(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_18(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_17(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_19(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_18(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_20(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_19(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_21(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_20(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_22(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_21(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_23(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_22(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_24(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_23(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_25(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_24(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_26(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_25(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_27(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_26(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_28(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_27(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_29(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_28(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_30(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_29(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_31(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_30(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_32(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_31(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_33(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_32(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_34(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_33(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_35(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_34(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_36(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_35(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_37(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_36(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_38(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_37(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1_39(what, intf, T, x, ...) what(intf, T, x) OPENDAQ__EXPAND(FOR_EACH_1_38(what, intf, T, __VA_ARGS__))

#define FOR_EACH_0(what, delim, intf, T1, T2, x, y)
#define FOR_EACH_2(what, delim, intf, T1, T2, x, y)       what(intf, T1, T2, x, y)
#define FOR_EACH_4(what, delim, intf, T1, T2, x, y, ...)  what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_2(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_6(what, delim, intf, T1, T2, x, y, ...)  what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_4(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_8(what, delim, intf, T1, T2, x, y, ...)  what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_6(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_10(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_8(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_12(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_10(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_14(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_12(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_16(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_14(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_18(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_16(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_20(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_18(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_22(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_20(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_24(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_22(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_26(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_24(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_28(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_26(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_30(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_28(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_32(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_30(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_34(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_32(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_36(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_34(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_38(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_36(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_40(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_38(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_42(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_40(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_44(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_42(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_46(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_44(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_48(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_46(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_50(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_48(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_52(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_50(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_54(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_52(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_56(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_54(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_58(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_56(what, delim, intf, T1, T2, __VA_ARGS__))
#define FOR_EACH_60(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(FOR_EACH_58(what, delim, intf, T1, T2, __VA_ARGS__))

#define _FOR_EACH_0(what, delim, intf, T1, T2, x, y)
#define _FOR_EACH_2(what, delim, intf, T1, T2, x, y)       what(intf, T1, T2, x, y)
#define _FOR_EACH_4(what, delim, intf, T1, T2, x, y, ...)  what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_2(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_6(what, delim, intf, T1, T2, x, y, ...)  what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_4(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_8(what, delim, intf, T1, T2, x, y, ...)  what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_6(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_10(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_8(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_12(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_10(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_14(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_12(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_16(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_14(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_18(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_16(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_20(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_18(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_22(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_20(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_24(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_22(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_26(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_24(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_28(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_26(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_30(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_28(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_32(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_30(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_34(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_32(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_36(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_34(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_38(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_36(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_40(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_38(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_42(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_40(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_44(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_42(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_46(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_44(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_48(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_46(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_50(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_48(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_52(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_50(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_54(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_52(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_56(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_54(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_58(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_56(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_60(what, delim, intf, T1, T2, x, y, ...) what(intf, T1, T2, x, y) OPENDAQ__STRIP_PAR delim OPENDAQ__EXPAND(_FOR_EACH_58(what, delim, intf, T1, T2, __VA_ARGS__))

#define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
#define FOR_EACH_NARG_(...) OPENDAQ__EXPAND(FOR_EACH_ARG_N(__VA_ARGS__))
#define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, N, ...) N
#define FOR_EACH_RSEQ_N() 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

#define OPENDAQ__CONCATENATE_(x, y) x##y
#define OPENDAQ__CONCATENATE(x, y) OPENDAQ__CONCATENATE_(x, y)
#define OPENDAQ_CONCATENATE_DELIM(delim, x, y) OPENDAQ__CONCATENATE(OPENDAQ__CONCATENATE(x, delim), y)

#define  FOR_EACH_1P_(N, what, intf, T, ...) OPENDAQ__EXPAND(OPENDAQ__CONCATENATE(FOR_EACH_1_ , N)(what, intf, T, __VA_ARGS__))
#define _FOR_EACH_1P_(N, what, intf, T, ...) OPENDAQ__EXPAND(OPENDAQ__CONCATENATE(_FOR_EACH_1_, N)(what, intf, T, __VA_ARGS__))

#define FOR_EACH_2P_(N, what, delim, intf, T1, T2, ...)  OPENDAQ__EXPAND(OPENDAQ__CONCATENATE(FOR_EACH_ , N)(what, delim, intf, T1, T2, __VA_ARGS__))
#define _FOR_EACH_2P_(N, what, delim, intf, T1, T2, ...) OPENDAQ__EXPAND(OPENDAQ__CONCATENATE(_FOR_EACH_, N)(what, delim, intf, T1, T2, __VA_ARGS__))

#define  FOR_EACH_1P(what, intf, T, ...)  FOR_EACH_1P_(FOR_EACH_NARG(__VA_ARGS__), what, intf, T, __VA_ARGS__)
#define _FOR_EACH_1P(what, intf, T, ...) _FOR_EACH_1P_(FOR_EACH_NARG(__VA_ARGS__), what, intf, T, __VA_ARGS__)

#define  FOR_EACH_2P(what, delim, intf, T1, T2, ...)  FOR_EACH_2P_(FOR_EACH_NARG(__VA_ARGS__), what, delim, intf, T1, T2, __VA_ARGS__)
#define _FOR_EACH_2P(what, delim, intf, T1, T2, ...) _FOR_EACH_2P_(FOR_EACH_NARG(__VA_ARGS__), what, delim, intf, T1, T2, __VA_ARGS__)

#define OPENDAQ__NO_DELIM ()
#define OPENDAQ__COMMA_DELIM (,)

#define OPENDAQ__COMMA OPENDAQ__STRIP_PAR (,)
