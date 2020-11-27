#include <pch.hpp>
#include <Utils/StringExtensions.hpp>



namespace ObjParserC::Utils
{
	int32_t StringExtensions::StrLen(const char* str)
	{
		int32_t result = (int32_t)str;
		while (*str++) {}
		return (int32_t)str - result;
	}

	bool StringExtensions::StrComp(const char* str1, const char* str2)
	{
		while (*str1 != NULL && *str2 != NULL)
		{

			if (*str1++ != *str2++) return false;

		}

		return true;
	}

	strings StringExtensions::Split(const std::string& str, chars* separator, StringSplitOptions options)
	{
		if (!separator || separator->Length() == 0)
		{

			strings result = strings(1);
			result[0] = std::string(str);
			return result;

		}
		
		char* ptr = (char*)(&str[0]);
		char* delim = &((*separator)[0]);
		char* next_token = nullptr;

		char* tok = ::strtok_s(ptr, delim, &next_token);
		std::vector<std::string> result;

		while (tok != NULL)
		{

			auto string = std::string(tok);
			tok = ::strtok_s(NULL, delim, &next_token);

			if (options == StringSplitOptions::RemoveEmptyEntries && string == StringEmpty) continue;
			else result.push_back(string);

		}

		return strings(result);
	}

	wstrings StringExtensions::Split(const std::wstring& str, wchars* separator, StringSplitOptions options)
	{
		if (!separator || separator->Length() == 0)
		{

			wstrings result = wstrings(1);
			result[0] = std::wstring(str);
			return result;

		}

		wchar_t* ptr = (wchar_t*)(&str[0]);
		wchar_t* delim = &((*separator)[0]);
		wchar_t* next_token = nullptr;

		wchar_t* tok = ::wcstok_s(ptr, delim, &next_token);
		std::vector<std::wstring> result;

		while (tok != NULL)
		{

			auto string = std::wstring(tok);
			tok = ::wcstok_s(NULL, delim, &next_token);

			if (options == StringSplitOptions::RemoveEmptyEntries && string == WStringEmpty) continue;
			else result.push_back(string);

		}

		return wstrings(result);
	}

	inline bool StringExtensions::IsEmpty(const std::string& str)
	{
		return str.size() == 0;
	}

	inline bool StringExtensions::IsEmpty(const std::wstring& str)
	{
		return str.size() == 0;
	}

	inline bool StringExtensions::IsLatin(wchar_t c)
	{
		return c <= 'ÿ';
	}

	inline bool StringExtensions::IsAscii(wchar_t c)
	{
		return c <= '\u007f';
	}

	inline bool StringExtensions::IsWhiteSpace(char c)
	{
		switch (c)
		{
		default:
			return false;

		case '\u00a0':
		case '\u0085':
		case '\t':
		case '\n':
		case '\v':
		case '\f':
		case '\r':
		case ' ':
			return true;
		}
	}

	inline bool StringExtensions::IsWhiteSpace(wchar_t c)
	{
		switch (c)
		{
		default:
			return false;
			
		case '\u00a0':
		case '\u0085':
		case '\t':
		case '\n':
		case '\v':
		case '\f':
		case '\r':
		case ' ':
			return true;
		}
	}

	inline bool StringExtensions::IsWhiteSpace(const std::string& str)
	{
		for (uint32_t i = 0; i < str.length(); i++)
		{

			if (!StringExtensions::IsWhiteSpace(str[i]))
			{

				return false;

			}

		}

		return true;
	}

	inline bool StringExtensions::IsWhiteSpace(const std::wstring& str)
	{
		for (uint32_t i = 0; i < str.length(); i++)
		{

			if (!StringExtensions::IsWhiteSpace(str[i]))
			{

				return false;

			}
		
		}
		
		return true;
	}

	void StringExtensions::ToLower(const std::string& str)
	{
		if (StringExtensions::IsEmpty(str)) return;
		auto ptr = (char*)&str[0];
		
		while (*ptr++)
		{

			char& c = *ptr;
			if (c >= 'A' && c <= 'Z') c |= 0x20;

		}
	}

	void StringExtensions::ToUpper(const std::string& str)
	{
		if (StringExtensions::IsEmpty(str)) return;
		auto ptr = (char*)&str[0];

		while (*ptr++)
		{

			char& c = *ptr;
			if (c >= 'a' && c <= 'z') c &= 0x5F;

		}
	}

	std::string StringExtensions::ToNarrow(const std::wstring& str)
	{
		return std::string(str.begin(), str.end());
	}

	std::wstring StringExtensions::ToWide(const std::string& str)
	{
		return std::wstring(str.begin(), str.end());
	}

	std::string StringExtensions::Format(const char* format, ...)
	{
		auto args = ::va_list();
		va_start(args, format);
		char buffer[0x100] { };
		return std::string(buffer, std::vsprintf(buffer, format, args));
	}

	std::wstring StringExtensions::Format(const wchar_t* format, ...)
	{
		auto args = ::va_list();
		va_start(args, format);
		wchar_t buffer[0x100]{ };
		return std::wstring(buffer, std::vswprintf(buffer, format, args));
	}

	std::string StringExtensions::Replace(const std::string& str, char oldChar, char newChar)
	{
		chars arr = chars(str.length());
		
		for (uint32_t i = 0; i < str.length(); ++i)
		{

			char c = str[i];
			if (c == oldChar) c = newChar;
			arr[i] = c;

		}

		return std::string(&arr[0]);
	}
	
	std::wstring StringExtensions::Replace(const std::wstring& str, wchar_t oldChar, wchar_t newChar)
	{
		wchars arr = wchars(str.length());

		for (uint32_t i = 0; i < str.length(); ++i)
		{

			wchar_t c = str[i];
			if (c == oldChar) c = newChar;
			arr[i] = c;

		}

		return std::wstring(&arr[0]);
	}

	std::string StringExtensions::Trim(const std::string& str)
	{
		if (str.length() == 0) return str;

		int32_t len = (int32_t)str.length();
		int32_t start;
		int32_t end = len - 1;
		char* ptr = (char*)&str[0];

		for (start = 0; start < len && StringExtensions::IsWhiteSpace(ptr[start]); ++start) {}
		while (end >= start && StringExtensions::IsWhiteSpace(ptr[end])) --end;

		int32_t count = end - start + 1;
		if (count == len) return str;
		if (count == 0) return StringEmpty;
		return str.substr(start, count);
	}

	std::wstring StringExtensions::Trim(const std::wstring& str)
	{
		if (str.length() == 0) return str;

		int32_t len = (int32_t)str.length();
		int32_t start;
		int32_t end = len - 1;
		wchar_t* ptr = (wchar_t*)&str[0];

		for (start = 0; start < len && StringExtensions::IsWhiteSpace(ptr[start]); ++start) {}
		while (end >= start && StringExtensions::IsWhiteSpace(ptr[end])) --end;

		int32_t count = end - start + 1;
		if (count == len) return str;
		if (count == 0) return WStringEmpty;
		return str.substr(start, count);
	}

	bool StringExtensions::StartsWith(const std::string& str, const std::string& prefix)
	{
		if (str.length() < prefix.length()) return false;

		auto strPtr = (char*)&str[0];
		auto prePtr = (char*)&prefix[0];

		for (uint32_t i = 0; i < prefix.length(); ++i)
		{

			if (strPtr[i] != prePtr[i]) return false;
			
		}

		return true;
	}

	bool StringExtensions::StartsWith(const std::wstring& str, const std::wstring& prefix)
	{
		if (str.length() < prefix.length()) return false;

		auto strPtr = (wchar_t*)&str[0];
		auto prePtr = (wchar_t*)&prefix[0];

		for (uint32_t i = 0; i < prefix.length(); ++i)
		{

			if (strPtr[i] != prePtr[i]) return false;

		}

		return true;
	}

	bool StringExtensions::EndsWith(const std::string& str, const std::string& prefix)
	{
		auto len = prefix.length();
		if (str.length() < len) return false;

		auto strPtr = (char*)&str[str.length() - len];
		auto prePtr = (char*)&prefix[0];

		for (uint32_t i = 0; i < len; ++i)
		{

			if (strPtr[i] != prePtr[i]) return false;

		}

		return true;
	}

	bool StringExtensions::EndsWith(const std::wstring& str, const std::wstring& prefix)
	{
		auto len = prefix.length();
		if (str.length() < len) return false;

		auto strPtr = (wchar_t*)&str[str.length() - len];
		auto prePtr = (wchar_t*)&prefix[0];

		for (uint32_t i = 0; i < len; ++i)
		{

			if (strPtr[i] != prePtr[i]) return false;

		}

		return true;
	}

	int32_t StringExtensions::IndexOf(const std::string& str, char c)
	{
		for (uint32_t i = 0; i < str.length(); ++i)
		{

			if (str[i] == c) return i;

		}

		return -1;
	}

	int32_t StringExtensions::IndexOf(const std::wstring& str, wchar_t c)
	{
		for (uint32_t i = 0; i < str.length(); ++i)
		{

			if (str[i] == c) return i;

		}

		return -1;
	}

	int32_t StringExtensions::LastIndexOf(const std::string& str, char c)
	{
		for (int32_t i = (int32_t)str.length() - 1; i >= 0; --i)
		{

			if (str[i] == c) return i;

		}

		return -1;
	}

	int32_t StringExtensions::LastIndexOf(const std::wstring& str, wchar_t c)
	{
		for (int32_t i = (int32_t)str.length() - 1; i >= 0; --i)
		{

			if (str[i] == c) return i;

		}

		return -1;
	}
}

