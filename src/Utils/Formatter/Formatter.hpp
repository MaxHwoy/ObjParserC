#pragma once



namespace ObjParserC::Utils
{
	struct Formatter
	{
		static int32_t ParseInt32(const std::string& str);
		static int32_t ParseInt32(const std::wstring& str);

		static uint32_t ParseUInt32(const std::string& str);
		static uint32_t ParseUInt32(const std::wstring& str);

		static float ParseSingle(const std::string& str);
		static float ParseSingle(const std::wstring& str);

		static double ParseDouble(const std::string& str);
		static double ParseDouble(const std::wstring& str);
	};
}
