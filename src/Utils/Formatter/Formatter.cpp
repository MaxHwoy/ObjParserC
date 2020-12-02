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
		/*
		Several case:
		1. NaN value
		2. Positive infinity like 
		3. Negative infinity like
		4. With a + symbol in front
		5. With a - symbol in front
		6. Has decimal . separator
		7. Has scientific E or e with + or -
		*/

		if (str.length() == 0 || str == "NaN") return NaN;


		return 0.0f;
	}

	float Formatter::ParseSingle(const std::wstring& str)
	{


		return 0.0f;
	}

	double Formatter::ParseDouble(const std::string& str)
	{


		return 0.0;
	}

	double Formatter::ParseDouble(const std::wstring& str)
	{


		return 0.0;
	}
}
