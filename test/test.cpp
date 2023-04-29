#include <iomanip>
#include <iostream>

//#define STN_USE_EXPECTED
#include "../StrToNum/StrToNum.h"

int main()
{
	constexpr auto str = "1234567890";
	constexpr auto wstr = L"1234567890";

	constexpr auto Int1 = stn::StrToInt(std::string_view(str).substr(0, 5));
	static_assert(Int1 == 12345);
	std::cout << "Int1 = " << Int1.value_or(-1) << "\n";

	constexpr auto Int2 = stn::StrToInt(std::wstring_view(wstr).substr(5));
	static_assert(Int2 == 67890);
	std::cout << "Int2 = " << Int2.value_or(-1) << "\n";

	constexpr auto LL1 = stn::StrToLL("0xABCDEF");
	static_assert(LL1 == 0xABCDEF);
	std::cout << std::hex << "LL1 = " << LL1.value_or(-1) << "\n";

	constexpr auto LL2 = stn::StrToLL(L"0xFEDCBA");
	static_assert(LL2 == 0xFEDCBA);
	std::cout << std::hex << "LL2 = " << LL2.value_or(-1) << "\n";

	constexpr auto LL3 = stn::StrToLL(L"-0xACE987");
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