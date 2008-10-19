template<int i>
class bitset
{
};

template<class T, size_t Size>
class Array
{
	private:
		T* data;
};

template<size_t Size>
class Array<bool, Size>
{
	private:
		bitset<Size> data;
};

template<>
class Array<bool, 8>
{
	private:
		short data;
};

