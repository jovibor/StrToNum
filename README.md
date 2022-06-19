## StrToNum
* [Introduction](#introduction)
* [Aliases](#aliases)
* [Example](#example)

### Introduction
A header-only library to convert `char` and `wchar_t` text strings to numbers.  

It is completely based on the Microsoft's `std::from_chars` implementation from the `<charconv>` standard header. The one significant difference though is that the ability to work with `wchar_t` type was added, because the C++ standard doesn't provide this functionality at the moment.  

`StrToNum` features `std::(w)string_view` as an input, so you are no longer obliged to have only null-terminated strings, which is mandatory in all `std::strto*` functions family.  

`StrToNum` also recognizes `0x` and `0X` prefixes as hex strings, when iBase is `0` or `16`, which `std::from_chars` doesn't.

As a return type `StrToNum` uses either `std::optional` (by default) or a newish and very convenient `std::expected` (through **/std:c++latest**), which either holds converted number or a `from_chars_result` struct, in case of converting error. Both these types are very similar.  
To use the `std::expected` version put the `#define STN_USE_EXPECTED` line before `#include "StrToNum.h"`

```cpp
template<typename IntegralT> requires std::is_integral_v<IntegralT>
[[nodiscard]] auto StrToNum(std::string_view str, int iBase = 0)noexcept
->std::expected<IntegralT, from_chars_result<char>>
```
```cpp
template<typename IntegralT> requires std::is_integral_v<IntegralT>
[[nodiscard]] auto StrToNum(std::wstring_view wstr, int iBase = 0)noexcept
->std::expected<IntegralT, from_chars_result<wchar_t>>
```
```cpp
template<typename FloatingT> requires std::is_floating_point_v<FloatingT>
[[nodiscard]] auto StrToNum(std::string_view str, chars_format fmt = chars_format::general)noexcept
->std::expected<FloatingT, from_chars_result<char>>
```
```cpp
template<typename FloatingT> requires std::is_floating_point_v<FloatingT>
[[nodiscard]] auto StrToNum(std::wstring_view wstr, chars_format fmt = chars_format::general)noexcept
->std::expected<FloatingT, from_chars_result<wchar_t>>
```

Basically `StrToNum` is a thin wrapper over the `std::from_chars` machinery, with the convenient interface and the ability to work with `wchar_t` strings. **Non-allocating, non-throwing, locale-independent**.

### Aliases
`StrToNum` is the main templated method which is very easy to use. But there are also a predefined wrappers for convenience, for all integral and floating types:
```cpp
[[nodiscard]] auto StrToChar(std::string_view str, int iBase = 0)noexcept
->std::expected<char, from_chars_result<char>>;
```
```cpp		
[[nodiscard]] auto StrToUChar(std::string_view str, int iBase = 0)noexcept
->std::expected<unsigned char, from_chars_result<char>>;
```
```cpp		
[[nodiscard]] auto StrToShort(std::string_view str, int iBase = 0)noexcept
->std::expected<short, from_chars_result<char>>;
```
```cpp		
[[nodiscard]] auto StrToUShort(std::string_view str, int iBase = 0)noexcept
->std::expected<unsigned short, from_chars_result<char>>;
```
```cpp
[[nodiscard]] auto StrToInt(std::string_view str, int iBase = 0)noexcept
->std::expected<int, from_chars_result<char>>;
```
```cpp
[[nodiscard]] auto StrToUInt(std::string_view str, int iBase = 0)noexcept
->std::expected<unsigned int, from_chars_result<char>>;
```
```cpp
[[nodiscard]] auto StrToLL(std::string_view str, int iBase = 0)noexcept
->std::expected<long long, from_chars_result<char>>;
```
```cpp
[[nodiscard]] auto StrToULL(std::string_view str, int iBase = 0)noexcept
->std::expected<unsigned long long, from_chars_result<char>>;
```
```cpp
[[nodiscard]] auto StrToFloat(std::string_view str, chars_format fmt = chars_format::general)noexcept
->std::expected<float, from_chars_result<char>>;
```
```cpp
[[nodiscard]] auto StrToDouble(std::string_view str, chars_format fmt = chars_format::general)noexcept
->std::expected<double, from_chars_result<char>>;
```

### Example
```cpp
#include <iomanip>
#include <iostream>
#include "StrToNum.h"

int main()
{
    constexpr const char* const str = "1234567890";
    constexpr const wchar_t* const wstr = L"1234567890";

    const auto Int1 = stn::StrToInt(std::string_view(str).substr(0, 5));
    assert(Int1 == 12345);
    std::cout << "Int1 = " << Int1.value_or(-1) << "\n";

    const auto Int2 = stn::StrToInt(std::wstring_view(wstr).substr(5));
    assert(Int2 == 67890);
    std::cout << "Int2 = " << Int2.value_or(-1) << "\n";

    const auto LL1 = stn::StrToLL("0xABCDEF");
    assert(LL1 == 0xABCDEF);
    std::cout << std::hex << "LL1 = " << LL1.value_or(-1) << "\n";

    const auto LL2 = stn::StrToLL(L"0xFEDCBA");
    assert(LL2 == 0xFEDCBA);
    std::cout << std::hex << "LL2 = " << LL2.value_or(-1) << "\n";

    const auto Dbl1 = stn::StrToDouble("3.1415926535");
    assert(Dbl1 == 3.1415926535);
    std::cout << std::fixed << std::setprecision(10) << "Dbl1 = " << Dbl1.value_or(-1.) << "\n";

    const auto Dbl2 = stn::StrToDouble(L"-987.654");
    assert(Dbl2 == -987.654);
    std::cout << std::fixed << std::setprecision(3) << "Dbl2 = " << Dbl2.value_or(-1.) << "\n";
}
```