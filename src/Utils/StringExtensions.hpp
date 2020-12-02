#pragma once



namespace ObjParserC::Utils
{
	struct StringExtensions final
	{
		static int32_t StrLen(const char* str);
		static bool StrComp(const char* str1, const char* str2);
		static strings Split(const std::string& str, chars* separator);
		static wstrings Split(const std::wstring& str, wchars* separator);

		static bool IsEmpty(const std::string& str);
		static bool IsEmpty(const std::wstring& str);
		static bool IsLatin(wchar_t c);
		static bool IsAscii(wchar_t c);
		static bool IsWhiteSpace(char c);
		static bool IsWhiteSpace(wchar_t c);
		static bool IsWhiteSpace(const std::string& str);
		static bool IsWhiteSpace(const std::wstring& str);

		static std::string ToLower(const std::string& str);
		static std::wstring ToLower(const std::wstring& str);
		static std::string ToUpper(const std::string& str);
		static std::wstring ToUpper(const std::wstring& str);
		static std::string ToNarrow(const std::wstring& str);
		static std::wstring ToWide(const std::string& str);
		static std::string Format(const char* format, ...);
		static std::wstring Format(const wchar_t* format, ...);
		static std::string Replace(const std::string& str, char oldChar, char newChar);
		static std::wstring Replace(const std::wstring& str, wchar_t oldChar, wchar_t newChar);
		static std::string Trim(const std::string& str);
		static std::wstring Trim(const std::wstring& str);

		static bool StartsWith(const std::string& str, const std::string& prefix);
		static bool StartsWith(const std::wstring& str, const std::wstring& prefix);
		static bool EndsWith(const std::string& str, const std::string& prefix);
		static bool EndsWith(const std::wstring& str, const std::wstring& prefix);

		static int32_t IndexOf(const std::string& str, char c);
		static int32_t IndexOf(const std::wstring& str, wchar_t c);
		static int32_t LastIndexOf(const std::string& str, char c);
		static int32_t LastIndexOf(const std::wstring& str, wchar_t c);
	};
}
