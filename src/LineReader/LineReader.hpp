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
		static wstrings empty;
		std::wstring _filename;
		Encoding _encoding;
		bool _is_ready;

		// File position
		FILE* _handle;
		int64_t _origin;
		int64_t _position;
		int64_t _length;

		// Buffer position
		uint8_t* _buffer;
		int32_t _bufLen;
		int32_t _bufPos;
		int32_t _bufAlloc;

		// Current line and splits
		std::wstring _current;
		int32_t _currentLine;
		int32_t _splitPos;
		wstrings _splits;

		// Privates
		void DetectEncoding();
		int64_t Position();
		void Position(int64_t position);
		void ReadANSIString(std::vector<wchar_t>* string);
		void ReadUTF8String(std::vector<wchar_t>* string);
		void ReadUTF16LEString(std::vector<wchar_t>* string);
		void ReadUTF16BEString(std::vector<wchar_t>* string);
		void InitBuffer();
		bool UpdateBuffer();
		void CleanBuffer();

	public:
		// Main
		LineReader(const std::wstring& file);
		LineReader(const LineReader& lr) = delete;
		LineReader& operator =(const LineReader& lr) = delete;
		~LineReader();

		// Properties
		std::wstring& Current();
		bool EndOfStream();
		bool IsOutOfBounds();
		bool IsValid();
		wstrings& Splits();

		// Functions
		bool ReadNext();
		std::wstring ReadString();
		int32_t ReadInt32();
		uint32_t ReadUInt32();
		float ReadSingle();
		double ReadDouble();
		Vector2 ReadVector2();
		Vector3 ReadVector3();
		Vector4 ReadVector4();
	};
}
