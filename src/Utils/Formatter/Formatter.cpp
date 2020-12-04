#include <pch.hpp>
#include <Utils/Formatter/Formatter.hpp>



namespace ObjParserC::Utils
{
	int32_t Formatter::ParseInt32(const std::string& str)
	{
		if (str.length() == 0) return 0;

		bool isNegative = str[0] == '-';
		int32_t result = 0;

		for (uint32_t i = isNegative ? 1 : 0; i < str.length(); i++)
		{

			result *= 10;
			result += str[i] - '0';

		}

		return isNegative ? -result : result;
	}

	int32_t Formatter::ParseInt32(const std::wstring& str)
	{
		if (str.length() == 0) return 0;

		bool isNegative = str[0] == '-';
		int32_t result = 0;

		for (uint32_t i = isNegative ? 1 : 0; i < str.length(); i++)
		{

			result *= 10;
			result += str[i] - '0';

		}

		return isNegative ? -result : result;
	}

	uint32_t Formatter::ParseUInt32(const std::string& str)
	{
		if (str.length() == 0) return 0;

		uint32_t result = 0;

		for (uint32_t i = 0; i < str.length(); i++)
		{

			result *= 10;
			result += str[i] - '0';

		}

		return result;
	}

	uint32_t Formatter::ParseUInt32(const std::wstring& str)
	{
		if (str.length() == 0) return 0;

		uint32_t result = 0;

		for (uint32_t i = 0; i < str.length(); i++)
		{

			result *= 10;
			result += str[i] - '0';

		}

		return result;
	}

	float Formatter::ParseSingle(const std::string& str)
	{
		return ::strtof(str.c_str(), nullptr);
	}

	float Formatter::ParseSingle(const std::wstring& str)
	{
		return ::wcstof(str.c_str(), nullptr);
	}

	double Formatter::ParseDouble(const std::string& str)
	{
		return ::strtod(str.c_str(), nullptr);
	}

	double Formatter::ParseDouble(const std::wstring& str)
	{
		return ::wcstod(str.c_str(), nullptr);
	}

	std::size_t Formatter::CombineHashes(std::size_t h1, std::size_t h2)
	{
		std::size_t num = (h1 << 5) | (h1 >> 27);
		return (num + h1) ^ h2;
	}
}
