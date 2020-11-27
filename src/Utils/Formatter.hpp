#pragma once



namespace ObjParserC::Utils
{
	struct Formatter
	{
		static std::string Clean(const std::string& str);
		static std::wstring Clean(const std::wstring& str);

		static int32_t ParseInt32(const std::string& str);
		static int32_t ParseInt32(const std::wstring& str);

		static float ParseSingle(const std::string& str);
		static float ParseSingle(const std::wstring& str);

	};
}
