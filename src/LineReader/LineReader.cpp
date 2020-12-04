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
		this->_buffer = nullptr;
		this->_bufLen = 0;
		this->_bufPos;
		this->_splitPos = 0;
		this->_currentLine = 0;
		this->_filename = WStringEmpty;
		this->_current = WStringEmpty;
		this->_splits = empty;
		this->_encoding = Encoding::ANSI;
		this->_handle = nullptr;

		this->_bufAlloc = 0x500000;

		if (!std::filesystem::exists(file)) return;

		this->_filename = file;
		if (::_wfopen_s(&this->_handle, file.c_str(), L"rb") || !this->_handle) return;

		struct _stat32 stat32;
		if (::_wstat32(file.c_str(), &stat32)) return;

		this->_length = stat32.st_size;
		this->_is_ready = true;
		if (this->_length == 0) return;

		this->DetectEncoding();
		this->InitBuffer();
	}

	LineReader::~LineReader()
	{
		if (!this->IsValid()) return;
		::fclose(this->_handle);
		this->_handle = nullptr;
		this->CleanBuffer();
	}



	std::wstring& LineReader::Current()
	{
		return this->_current;
	}

	bool LineReader::EndOfStream()
	{
		return this->_position == this->_length && this->_bufPos == this->_bufLen;
	}

	bool LineReader::IsOutOfBounds()
	{
		return this->_splitPos >= this->_splits.Length();
	}

	bool LineReader::IsValid()
	{
		return this->_is_ready && this->_handle;
	}

	int64_t LineReader::Position()
	{
		return this->_position - this->_bufAlloc + this->_bufPos;
	}

	void LineReader::Position(int64_t position)
	{
		if (position < 0) position = 0;
		else if (position > this->_length) position = this->_length;

		::fseek(this->_handle, (int32_t)(this->_origin + position), SEEK_SET);
		this->_position = position;
		this->UpdateBuffer();
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
		while (true)
		{

			// Read till we encounter line terminator or end of buffer
			while (this->_bufPos < this->_bufLen)
			{

				// Read current char from buffer
				char c = this->_buffer[this->_bufPos++];

				// If char == '\r' then mark it as the last character so we can skip '\n' in the next line
				if (c == '\r')
				{

					string->push_back(0);
					
					// we need to check whether next char is '\n'
					if (this->_bufPos == this->_bufLen)
					{

						if (!this->UpdateBuffer()) return;

					}

					if (this->_buffer[this->_bufPos] == '\n')
					{

						++this->_bufPos;
						return;

					}

					return;

				}

				// If char == '\n' return current string
				else if (c == '\n')
				{

					string->push_back(0);
					return;

				}

				// Else push current char to the vector
				string->push_back(c);

			}

			// If we reached end of file
			if (!this->UpdateBuffer()) return;

			// Else we continue reading using updated buffer

		}
	}

	void LineReader::ReadUTF8String(std::vector<wchar_t>* string)
	{
		// implement later
		this->ReadANSIString(string);
	}

	void LineReader::ReadUTF16LEString(std::vector<wchar_t>* string)
	{
		while (true)
		{

			// Read till we encounter line terminator or end of buffer
			// Note since we read wchar_t there might be a byte overflow, so _bufPos + 1 < _bufLen
			while (this->_bufPos + 1 < this->_bufLen)
			{

				// Read current char from buffer
				wchar_t c = ((wchar_t*)this->_buffer)[this->_bufPos];
				this->_bufPos += 2;

				// If char == '\r' then mark it as the last character so we can skip '\n' in the next line
				if (c == '\r')
				{

					string->push_back(0);

					// we need to check whether next char is '\n'
					if (this->_bufPos + 2 > this->_bufLen)
					{

						if (!this->UpdateBuffer()) return;

					}

					if (((wchar_t*)this->_buffer)[this->_bufPos] == '\n')
					{

						this->_bufPos += 2;
						return;

					}

					return;

				}

				// If char == '\n' return current string
				else if (c == '\n')
				{

					string->push_back(0);
					return;

				}

				// Else push current char to the vector
				string->push_back(c);

			}

			// If we reached end of file
			if (!this->UpdateBuffer()) return;

			// Else we continue reading using updated buffer

		}
	}

	void LineReader::ReadUTF16BEString(std::vector<wchar_t>* string)
	{
		while (true)
		{

			// Read till we encounter line terminator or end of buffer
			// Note since we read wchar_t there might be a byte overflow, so _bufPos + 1 < _bufLen
			while (this->_bufPos + 1 < this->_bufLen)
			{

				// Read current char from buffer
				wchar_t c = ((wchar_t*)this->_buffer)[this->_bufPos];
				this->_bufPos += 2;

				// Endian swap
				c = (c >> 8) | ((uint8_t)c << 8);

				// If char == '\r' then mark it as the last character so we can skip '\n' in the next line
				if (c == '\r')
				{

					string->push_back(0);

					// we need to check whether next char is '\n'
					if (this->_bufPos + 2 > this->_bufLen)
					{

						if (!this->UpdateBuffer()) return;

					}

					if (((wchar_t*)this->_buffer)[this->_bufPos] == '\n\0')
					{

						this->_bufPos += 2;
						return;

					}

					return;

				}

				// If char == '\n' return current string
				else if (c == '\n')
				{

					string->push_back(0);
					return;

				}

				// Else push current char to the vector
				string->push_back(c);

			}

			// If we reached end of file
			if (!this->UpdateBuffer()) return;

			// Else we continue reading using updated buffer

		}
	}

	void LineReader::InitBuffer()
	{
		if (this->_length <= this->_bufAlloc) // 5 MB
		{

			this->_buffer = reinterpret_cast<uint8_t*>(::malloc((size_t)this->_length));
			if (this->_buffer == nullptr) throw;
			::fread_s(this->_buffer, (size_t)this->_length, 1, (size_t)this->_length, this->_handle);
			this->_bufLen = (int32_t)this->_length;
			this->_bufPos = 0;
			this->_position = this->_length;

		}
		else
		{

			this->_buffer = reinterpret_cast<uint8_t*>(::malloc(this->_bufAlloc));
			if (this->_buffer == nullptr) throw;
			::fread_s(this->_buffer, this->_bufAlloc, 1, this->_bufAlloc, this->_handle);
			this->_bufLen = this->_bufAlloc;
			this->_bufPos = 0;
			this->_position = this->_bufAlloc;

		}
	}

	bool LineReader::UpdateBuffer()
	{
		auto left = this->_length - this->_position;

		if (left <= 0)
		{

			this->_bufPos = this->_bufLen;
			return false;

		}
		else if (left <= this->_bufAlloc) // 5 MB
		{

			::fread_s(this->_buffer, this->_bufLen, 1, (size_t)left, this->_handle);
			this->_bufLen = (size_t)left;
			this->_bufPos = 0;
			this->_position += left;
			return true;

		}
		else
		{

			::fread_s(this->_buffer, this->_bufAlloc, 1, this->_bufAlloc, this->_handle);
			this->_bufPos = 0;
			this->_position += this->_bufAlloc;
			return true;

		}
	}

	void LineReader::CleanBuffer()
	{
		::free(this->_buffer);
	}

	bool LineReader::ReadNext()
	{
		if (this->EndOfStream()) return false; // end of stream

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

	std::wstring LineReader::ReadString()
	{
		if (this->IsOutOfBounds()) return WStringEmpty;
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
