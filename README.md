## StrToNum
* [Introduction](#introduction)
* [Aliases](#aliases)
* [Example](#example)

### Introduction
**StrToNum** is a header-only library for converting `char` and `wchar_t` strings to numbers. The library is fully `constexpr`, which means that conversions can be done at compile time if a converting string is a `constexpr` string.

**StrToNum** is completely based on the Microsoft's `std::from_chars` implementation from the `<charconv>` standard header. The one significant difference though is the ability to work with `wchar_t` strings, because the C++ standard doesn't provide such functionality at the moment.  

**StrToNum** features `std::(w)string_view` as an input, so you are no longer obliged to have only null-terminated strings, which is mandatory in all `std::strto*` functions family.  

The library also recognizes `0x` and `0X` prefixes as hex strings, when `iBase` is `0` or `16`, which `std::from_chars` doesn't.

As a return type **StrToNum** uses either `std::optional` (by default) or a newish and very convenient `std::expected`, which either holds converted number or a `from_chars_result` struct in case of converting error. Both these types are very similar.  
To use the `std::expected` version put the `#define STN_USE_EXPECTED` line before `#include "StrToNum.h"`

```cpp
template<typename IntegralT> requires std::is_integral_v<IntegralT>
[[nodiscard]] constexpr auto StrToNum(std::string_view sv, int iBase = 0)noexcept
->std::expected<IntegralT, from_chars_result<char>>
```
```cpp
template<typename IntegralT> requires std::is_integral_v<IntegralT>
[[nodiscard]] constexpr auto StrToNum(std::wstring_view wsv, int iBase = 0)noexcept
->std::expected<IntegralT, from_chars_result<wchar_t>>
```
```cpp
template<typename FloatingT> requires std::is_floating_point_v<FloatingT>
[[nodiscard]] constexpr auto StrToNum(std::string_view sv, chars_format fmt = chars_format::general)noexcept
->std::expected<FloatingT, from_chars_result<char>>
```
```cpp
template<typename FloatingT> requires std::is_floating_point_v<FloatingT>
[[nodiscard]] constexpr auto StrToNum(std::wstring_view wsv, chars_format fmt = chars_format::general)noexcept
->std::expected<FloatingT, from_chars_result<wchar_t>>
```

Basically **StrToNum** is a thin wrapper over the `std::from_chars` machinery with the convenient interface and the ability to work with `wchar_t` strings. **Non-allocating, non-throwing, locale-independent**.

### Aliases
`StrToNum` is the main templated method which is very easy to use. But there are also a predefined wrappers for convenience, for all integral and floating types:
```cpp
[[nodiscard]] inline constexpr auto StrToInt8(std::string_view sv, int iBase = 0)noexcept
->std::expected<std::int8_t, from_chars_result<char>>;
```
```cpp		
[[nodiscard]] inline constexpr auto StrToUInt8(std::string_view sv, int iBase = 0)noexcept
->std::expected<std::uint8_t, from_chars_result<char>>;
```
```cpp		
[[nodiscard]] inline constexpr auto StrToInt16(std::string_view sv, int iBase = 0)noexcept
->std::expected<short, from_chars_result<char>>;
```
```cpp		
[[nodiscard]] inline constexpr auto StrToUInt16(std::string_view sv, int iBase = 0)noexcept
->std::expected<unsigned short, from_chars_result<char>>;
```
```cpp
[[nodiscard]] inline constexpr auto StrToInt32(std::string_view sv, int iBase = 0)noexcept
->std::expected<int, from_chars_result<char>>;
```
```cpp
[[nodiscard]] inline constexpr auto StrToUInt32(std::string_view sv, int iBase = 0)noexcept
->std::expected<unsigned int, from_chars_result<char>>;
```
```cpp
[[nodiscard]] inline constexpr auto StrToInt64(std::string_view sv, int iBase = 0)noexcept
->std::expected<long long, from_chars_result<char>>;
```
```cpp
[[nodiscard]] inline constexpr auto StrToUInt64(std::string_view sv, int iBase = 0)noexcept
->std::expected<unsigned long long, from_chars_result<char>>;
```
```cpp
[[nodiscard]] inline constexpr auto StrToFloat(std::string_view sv, chars_format fmt = chars_format::general)noexcept
->std::expected<float, from_chars_result<char>>;
```
```cpp
[[nodiscard]] inline constexpr auto StrToDouble(std::string_view sv, chars_format fmt = chars_format::general)noexcept
->std::expected<double, from_chars_result<char>>;
```

### Example
```cpp
#include <iomanip>
#include <iostream>
#include "StrToNum.h"

int main()
{
    constexpr auto str = "1234567890";
    constexpr auto wstr = L"1234567890";

    constexpr auto Int1 = stn::StrToInt32(std::string_view(str).substr(0, 5));
    static_assert(Int1 == 12345);
    std::cout << "Int1 = " << Int1.value_or(-1) << "\n";

    constexpr auto Int2 = stn::StrToInt32(std::wstring_view(wstr).substr(5));
    static_assert(Int2 == 67890);
    std::cout << "Int2 = " << Int2.value_or(-1) << "\n";

    constexpr auto LL1 = stn::StrToInt64("0xABCDEF");
    static_assert(LL1 == 0xABCDEF);
    std::cout << std::hex << "LL1 = " << LL1.value_or(-1) << "\n";

    constexpr auto LL2 = stn::StrToInt64(L"0xFEDCBA");
    static_assert(LL2 == 0xFEDCBA);
    std::cout << std::hex << "LL2 = " << LL2.value_or(-1) << "\n";

    constexpr auto LL3 = stn::StrToInt64(L"-0xACE987");
    static_assert(LL3 == -0xACE987);
    std::cout << std::dec << "LL3 = " << LL3.value_or(-1) << "\n";

    constexpr auto Dbl1 = stn::StrToDouble("3.14159265358979");
    static_assert(Dbl1 == 3.14159265358979);
    std::cout << std::fixed << std::setprecision(14) << "Dbl1 = " << Dbl1.value_or(-1.) << "\n";

    constexpr auto Dbl2 = stn::StrToDouble(L"-987.654321");
    static_assert(Dbl2 == -987.654321);
    std::cout << std::fixed << std::setprecision(6) << "Dbl2 = " << Dbl2.value_or(-1.) << "\n";

    constexpr auto flHex = stn::StrToFloat(L"0x1.Fp-2", stn::chars_format::hex);
    static_assert(flHex == 0x1.Fp-2);
    std::cout << std::fixed << std::setprecision(6) << "flHex = " << flHex.value_or(-1.) << "\n";
}
```