#pragma once



namespace ObjParserC
{
	enum class Encoding
	{
		ANSI,
		UTF8,
		UTF16LE,
		UTF16BE,
	};

	class LineReader final
	{
	private:
		// Fields
		FILE* _handle;
		std::wstring _filename;
		static wstrings empty;
		Encoding _encoding;
		bool _is_ready;

		int64_t _origin;
		int64_t _position;
		int64_t _length;

		std::wstring _current;
		int32_t _currentLine;
		int32_t _splitPos;
		wstrings _splits;

		// Privates
		void DetectEncoding();
		void Position(int64_t position);
		void ReadANSIString(std::vector<wchar_t>* string);
		void ReadUTF8String(std::vector<wchar_t>* string);
		void ReadUTF16LEString(std::vector<wchar_t>* string);
		void ReadUTF16BEString(std::vector<wchar_t>* string);

	public:
		// Main
		LineReader(const std::wstring& file);
		LineReader(const LineReader& lr) = delete;
		~LineReader();

		// Properties
		std::wstring Current();
		bool EndOfStream();
		bool IsOutOfBounds();
		bool IsValid();
		wstrings Splits();

		// Functions
		bool ReadNext();
		std::wstring ReadString();
		int32_t ReadInt32();
		uint32_t ReadUInt32();
		float ReadSingle();
		double ReadDouble();
		LinearC::Vectors::Vector2 ReadVector2();
		LinearC::Vectors::Vector3 ReadVector3();
		LinearC::Vectors::Vector4 ReadVector4();
	};
}
