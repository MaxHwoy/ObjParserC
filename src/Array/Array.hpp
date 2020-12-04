#pragma once



namespace ObjParserC
{
	template <typename T> class Array final
	{
	private:
		T* ptr_;
		int32_t length_;

	public:
		Array() : Array(0)
		{
		}
		Array(int32_t count)
		{
			if (count <= 0)
			{

				this->length_ = 0;
				this->ptr_ = nullptr;
				return;

			}
			this->ptr_ = new T[count];
			this->length_ = count;
			//std::memset(this->ptr_, 0, sizeof(T) * count);
		}
		Array(const Array& arr)
		{
			this->length_ = arr.length_;

			if (this->length_ == 0)
			{
				
				this->ptr_ = nullptr;
				return;

			}

			this->ptr_ = new T[this->length_];
			std::copy_n(arr.ptr_, this->length_, this->ptr_);
		}
		Array(const std::vector<T>& vector)
		{
			this->length_ = vector.size();

			if (this->length_ == 0)
			{

				this->ptr_ = nullptr;
				return;

			}

			this->ptr_ = new T[this->length_];
			std::copy_n(vector.begin(), this->length_, this->ptr_);
		}
		Array& operator=(const Array& arr)
		{
			if (this != &arr)
			{

				if (this->length_ != 0)
				{

					delete[] this->ptr_;

				}

				this->length_ = arr.length_;

				if (this->length_ == 0)
				{

					this->ptr_ = nullptr;
					return *this;

				}

				this->ptr_ = new T[this->length_];
				std::copy_n(arr.ptr_, this->length_, this->ptr_);

			}

			return *this;
		}
		Array(Array&& arr) noexcept
		{
			this->length_ = arr.length_;
			this->ptr_ = arr.ptr_;
			arr.length_ = 0;
			arr.ptr_ = nullptr;
		}
		T& operator[](int32_t index)
		{
			return this->ptr_[index];
		}
		~Array()
		{
			if (this->length_ != 0)
			{

				delete[] this->ptr_;

			}
		}

		int32_t Length()
		{
			return this->length_;
		}
		void Resize(int32_t size)
		{
			if (size <= 0)
			{

				delete[] this->ptr_;
				this->ptr_ = nullptr;
				this->length_ = 0;

			}
			else if (size < this->length_)
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
				std::memset(ptr, 0, sizeof(T) * size);
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
