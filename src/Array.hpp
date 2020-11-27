#pragma once



namespace ObjParserC
{
	template <typename T> class Array final
	{
	private:
		T* ptr_;
		int32_t length_;

	public:
		Array(int32_t count)
		{
			if (count <= 0) count = 0;
			this->ptr_ = new T[count];
			this->length_ = count;

		}
		Array(const Array& safeArray)
		{
			this->length_ = safeArray.length_;
			this->ptr_ = new T[this->length_];
			std::copy_n(safeArray.ptr_, this->length_, this->ptr_);
		}
		Array(const std::vector<T>& vector)
		{
			this->length_ = vector.size();
			this->ptr_ = new T[this->length_];
			std::copy_n(vector.begin(), this->length_, this->ptr_);
		}
		Array& operator=(const Array& safeArray)
		{
			if (this != &safeArray)
			{

				this->length_ = safeArray.length_;
				this->ptr_ = new T[this->length_];
				std::copy_n(safeArray.ptr_, this->length_, this->ptr_);

			}

			return *this;
		}
		T& operator[](int32_t index)
		{
			return this->ptr_[index];
		}
		~Array()
		{
			delete[] this->ptr_;
		}

		int32_t Length()
		{
			return this->length_;
		}
		void Resize(int32_t size)
		{
			if (size < this->length_)
			{

				auto ptr = new T[size];
				std::copy_n(this->ptr_, size, ptr);
				delete[] this->ptr_;
				this->ptr_ = ptr;
				this->length_ = size;

			}
			else if (size > this->length_)
			{

				auto ptr = new T[size];
				std::copy_n(this->ptr_, this->length_, ptr);
				delete[] this->ptr_;
				this->ptr_ = ptr;
				this->length_ = size;

			}
		}
	};
}

using bools = ObjParserC::Array<bool>;
using chars = ObjParserC::Array<char>;
using wchars = ObjParserC::Array<wchar_t>;
using int8s = ObjParserC::Array<int8_t>;
using uint8s = ObjParserC::Array<uint8_t>;
using int16s = ObjParserC::Array<int16_t>;
using uint16s = ObjParserC::Array<uint16_t>;
using int32s = ObjParserC::Array<int32_t>;
using uint32s = ObjParserC::Array<uint32_t>;
using int64s = ObjParserC::Array<int64_t>;
using uint64s = ObjParserC::Array<uint64_t>;
using strings = ObjParserC::Array<std::string>;
using wstrings = ObjParserC::Array<std::wstring>;
