template<class T, size_t size>
class Array
{
	private:
		T* data;
};

template<size_t size>
class Array<bool, size>
{
	private:
		bitset<size> data;
};

template<>
class Array<bool, 8>
{
	private:
		short data;
};

