#include <pch.hpp>
#include <LineReader/LineReader.hpp>



namespace ObjParserC
{
	wstrings LineReader::empty = wstrings();

	LineReader::LineReader(const std::wstring& file)
	{
		this->_is_ready = false;
		this->_origin = 0;
		this->_length = 0;
		this->_position = 0;
		this->_splitPos = 0;
		this->_currentLine = 0;
		this->_filename = WStringEmpty;
		this->_current = WStringEmpty;
		this->_splits = empty;
		this->_encoding = Encoding::ANSI;
		this->_handle = nullptr;

		if (!std::filesystem::exists(file)) return;

		this->_filename = file;
		if (::_wfopen_s(&this->_handle, file.c_str(), L"rb") || !this->_handle) return;

		struct _stat32 stat32;
		if (::_wstat32(file.c_str(), &stat32)) return;

		this->_length = stat32.st_size;
		this->_is_ready = true;

		this->DetectEncoding();
	}

	LineReader::~LineReader()
	{
		if (!this->IsValid()) return;
		::fclose(this->_handle);
		this->_handle = nullptr;
	}



	std::wstring& LineReader::Current()
	{
		return this->_current;
	}

	bool LineReader::EndOfStream()
	{
		return this->_position == this->_length;
	}

	bool LineReader::IsOutOfBounds()
	{
		return this->_splitPos >= this->_splits.Length();
	}

	bool LineReader::IsValid()
	{
		return this->_is_ready && this->_handle;
	}

	void LineReader::Position(int64_t position)
	{
		if (position < 0) position = 0;
		else if (position > this->_length) position = this->_length;

		::fseek(this->_handle, (int32_t)(this->_origin + position), SEEK_SET);
		this->_position = position;
	}

	wstrings& LineReader::Splits()
	{
		return this->_splits;
	}



	void LineReader::DetectEncoding()
	{
		if (this->_length < 2) return;

		char encoding[4];
		::fread_s(encoding, 4, 1, 2, this->_handle);

		// First, check if UTF32 little endian
		if (encoding[0] == 0xFF && encoding[1] == 0xFE)
		{

			this->_encoding = Encoding::UTF16LE;
			this->_origin = 2;
			this->_length -= 2;
			return;

		}

		// Second, check if UTF32 big endian
		if (encoding[0] == 0xFE && encoding[1] == 0xFF)
		{

			this->_encoding = Encoding::UTF16BE;
			this->_origin = 2;
			this->_length -= 2;
			return;

		}

		::fread_s(encoding + 2, 2, 1, 1, this->_handle);

		// Finally, check if it is UTF8 with BOM flag
		if (encoding[0] == 0xEF && encoding[1] == 0xBB && encoding[2] == 0xBF)
		{

			this->_encoding = Encoding::UTF8;
			this->_origin = 3;
			this->_length -= 3;
			return;

		}

		// Technically if there is not mask it is ANSI vs UTF8 (No BOM), but we choose
		// ANSI for simplicity
		::fseek(this->_handle, 0, SEEK_SET);
		this->_encoding = Encoding::ANSI;
		this->_origin = 0;
	}

	void LineReader::ReadANSIString(std::vector<wchar_t>* string)
	{
		char c;

		while (!this->EndOfStream())
		{

			::fread_s(&c, 1, 1, 1, this->_handle);
			++this->_position;

			if (c == '\r')
			{

				string->push_back(0);
				::fread_s(&c, 1, 1, 1, this->_handle);
				if (c == '\n') { ++this->_position; return; }
				this->Position(this->_position);
				return;

			}
			if (c == '\n')
			{

				string->push_back(0);
				return;

			}

			string->push_back(c);

		}
	}

	void LineReader::ReadUTF8String(std::vector<wchar_t>* string)
	{
		// implement later
		this->ReadANSIString(string);
	}

	void LineReader::ReadUTF16LEString(std::vector<wchar_t>* string)
	{
		wchar_t c;

		while (!this->EndOfStream())
		{

			::fread_s(&c, 2, 2, 1, this->_handle);
			this->_position += 2;

			if (c == '\r')
			{

				string->push_back(0);
				::fread_s(&c, 2, 2, 1, this->_handle);
				if (c == '\n') { this->_position += 2; return; }
				this->Position(this->_position);
				return;

			}
			if (c == '\n')
			{

				string->push_back(0);
				return;

			}

			string->push_back(c);

		}
	}

	void LineReader::ReadUTF16BEString(std::vector<wchar_t>* string)
	{
		wchar_t c;

		while (!this->EndOfStream())
		{

			::fread_s(&c, 2, 2, 1, this->_handle);
			this->_position += 2;

			// Endian swap
			c = (c >> 8) | ((uint8_t)c << 8);

			if (c == '\r')
			{

				string->push_back(0);
				::fread_s(&c, 2, 2, 1, this->_handle);
				if (c == '\n') { this->_position += 2; return; }
				this->Position(this->_position);
				return;

			}
			if (c == '\n')
			{

				string->push_back(0);
				return;

			}

			string->push_back(c);

		}
	}

	bool LineReader::ReadNext()
	{
		if (this->_position == this->_length) return false; // end of stream

		// Try to read line based on current encoding
		std::vector<wchar_t> string = std::vector<wchar_t>();

		switch (this->_encoding)
		{

		case Encoding::ANSI:
			this->ReadANSIString(&string);
			break;

		case Encoding::UTF8:
			this->ReadUTF8String(&string);
			break;

		case Encoding::UTF16LE:
			this->ReadUTF16LEString(&string);
			break;

		case Encoding::UTF16BE:
			this->ReadUTF16BEString(&string);
			break;

		default:
			this->ReadANSIString(&string);
			break;

		}

		this->_current = std::wstring(&string[0]);
		++this->_currentLine;

		if (ObjParserC::Utils::StringExtensions::IsWhiteSpace(this->_current))
		{

			this->_splitPos = 0;
			this->_splits = empty;

		}
		else
		{

			wchars separator = wchars(3);
			separator[0] = ' ';
			separator[1] = '\t';
			separator[2] = '\0';
			this->_splitPos = 0;
			this->_splits = ObjParserC::Utils::StringExtensions::Split(this->_current, &separator);

		}

		return true;
	}

	std::wstring& LineReader::ReadString()
	{
		if (this->IsOutOfBounds()) return std::wstring(WStringEmpty);
		return this->_splits[this->_splitPos++];
	}

	int32_t LineReader::ReadInt32()
	{
		if (this->IsOutOfBounds()) return 0;
		return ObjParserC::Utils::Formatter::ParseInt32(this->_splits[this->_splitPos++]);
	}

	uint32_t LineReader::ReadUInt32()
	{
		if (this->IsOutOfBounds()) return 0;
		return ObjParserC::Utils::Formatter::ParseUInt32(this->_splits[this->_splitPos++]);
	}

	float LineReader::ReadSingle()
	{
		if (this->IsOutOfBounds()) return 0.0f;
		return ObjParserC::Utils::Formatter::ParseSingle(this->_splits[this->_splitPos++]);
	}

	double LineReader::ReadDouble()
	{
		if (this->IsOutOfBounds()) return 0.0;
		return ObjParserC::Utils::Formatter::ParseDouble(this->_splits[this->_splitPos++]);
	}

	Vector2 LineReader::ReadVector2()
	{
		auto x = this->ReadSingle();
		auto y = this->ReadSingle();
		return Vector2(x, y);
	}

	Vector3 LineReader::ReadVector3()
	{
		auto x = this->ReadSingle();
		auto y = this->ReadSingle();
		auto z = this->ReadSingle();
		return Vector3(x, y, z);
	}

	Vector4 LineReader::ReadVector4()
	{
		auto x = this->ReadSingle();
		auto y = this->ReadSingle();
		auto z = this->ReadSingle();
		auto w = this->ReadSingle();
		return Vector4(x, y, z, w);
	}
}
