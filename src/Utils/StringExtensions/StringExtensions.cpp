#include <pch.hpp>
#include <Utils/StringExtensions/StringExtensions.hpp>

#pragma warning (disable : 4244)



namespace ObjParserC::Utils
{
	int32_t StringExtensions::StrLen(const char* str)
	{
		int32_t result = (int32_t)str;
		while (*str++) {}
		return (int32_t)str - result - 1;
	}

	bool StringExtensions::StrComp(const char* str1, const char* str2)
	{
		while (*str1 != NULL || *str2 != NULL)
		{

			if (*str1++ != *str2++) return false;

		}

		return true;
	}

	strings StringExtensions::Split(const std::string& str, chars* separator)
	{
		if (!separator || separator->Length() == 0)
		{

			strings result = strings(1);
			result[0] = std::string(str);
			return result;

		}
		
		auto clone = str;
		char* ptr = (char*)(&clone[0]);
		char* delim = &((*separator)[0]);
		char* next_token = nullptr;

		char* tok = ::strtok_s(ptr, delim, &next_token);
		std::vector<std::string> result;

		while (tok != NULL)
		{

			auto string = std::string(tok);
			tok = ::strtok_s(NULL, delim, &next_token);
			result.push_back(string);

		}

		return strings(result);
	}

	wstrings StringExtensions::Split(const std::wstring& str, wchars* separator)
	{
		if (!separator || separator->Length() == 0)
		{

			wstrings result = wstrings(1);
			result[0] = std::wstring(str);
			return result;

		}

		auto clone = str;
		wchar_t* ptr = (wchar_t*)(&clone[0]);
		wchar_t* delim = &((*separator)[0]);
		wchar_t* next_token = nullptr;

		wchar_t* tok = ::wcstok_s(ptr, delim, &next_token);
		std::vector<std::wstring> result;

		while (tok != NULL)
		{

			auto string = std::wstring(tok);
			tok = ::wcstok_s(NULL, delim, &next_token);
			result.push_back(string);

		}

		return wstrings(result);
	}

	bool StringExtensions::IsEmpty(const std::string& str)
	{
		return str.size() == 0;
	}

	bool StringExtensions::IsEmpty(const std::wstring& str)
	{
		return str.size() == 0;
	}

	bool StringExtensions::IsLatin(wchar_t c)
	{
		return c <= 255;
	}

	bool StringExtensions::IsAscii(wchar_t c)
	{
		return c <= 127;
	}

	bool StringExtensions::IsWhiteSpace(char c)
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

	bool StringExtensions::IsWhiteSpace(wchar_t c)
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

	bool StringExtensions::IsWhiteSpace(const std::string& str)
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

	bool StringExtensions::IsWhiteSpace(const std::wstring& str)
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

	std::string StringExtensions::ToLower(const std::string& str)
	{
		if (StringExtensions::IsEmpty(str)) return StringEmpty;
		std::string result = std::string(str);
		auto ptr = (char*)&result[0];

		while (*ptr)
		{

			char& c = *ptr++;
			if (c >= 'A' && c <= 'Z') c |= 0x20;

		}

		return result;
	}

	std::wstring StringExtensions::ToLower(const std::wstring& str)
	{
		if (StringExtensions::IsEmpty(str)) return WStringEmpty;
		std::wstring result = std::wstring(str);
		auto ptr = (wchar_t*)&result[0];

		while (*ptr)
		{

			wchar_t& c = *ptr++;
			if (c >= 'A' && c <= 'Z') c |= 0x20;

		}

		return result;
	}

	std::string StringExtensions::ToUpper(const std::string& str)
	{
		if (StringExtensions::IsEmpty(str)) return StringEmpty;
		std::string result = std::string(str);
		auto ptr = (char*)&result[0];

		while (*ptr)
		{

			char& c = *ptr++;
			if (c >= 'a' && c <= 'z') c &= 0x5F;

		}

		return result;
	}

	std::wstring StringExtensions::ToUpper(const std::wstring& str)
	{
		if (StringExtensions::IsEmpty(str)) return WStringEmpty;
		std::wstring result = std::wstring(str);
		auto ptr = (wchar_t*)&result[0];

		while (*ptr)
		{

			wchar_t& c = *ptr++;
			if (c >= 'a' && c <= 'z') c &= 0x5F;

		}

		return result;
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
		::va_list args;
		int32_t len;

		va_start(args, format);
		len = ::_vscprintf(format, args) + 1;

		char* buffer = reinterpret_cast<char*>(::malloc(len * sizeof(char)));

		if (buffer != nullptr)
		{

			auto count = ::vsprintf_s(buffer, len, format, args);
			std::string result = std::string(buffer, count);
			::free(buffer);
			va_end(args);
			return result;

		}
		else
		{

			va_end(args);
			return StringEmpty;

		}
	}

	std::wstring StringExtensions::Format(const wchar_t* format, ...)
	{
		::va_list args;
		int32_t len;

		va_start(args, format);
		len = ::_vscwprintf(format, args) + 1;

		wchar_t* buffer = reinterpret_cast<wchar_t*>(::malloc(len * sizeof(wchar_t)));

		if (buffer != nullptr)
		{

			auto count = ::vswprintf_s(buffer, len, format, args);
			std::wstring result = std::wstring(buffer, count);
			::free(buffer);
			va_end(args);
			return result;

		}
		else
		{

			va_end(args);
			return WStringEmpty;

		}
	}

	std::string StringExtensions::Replace(const std::string& str, char oldChar, char newChar)
	{
		chars arr = chars(str.length() + 1);
		
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
		wchars arr = wchars(str.length() + 1);

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

