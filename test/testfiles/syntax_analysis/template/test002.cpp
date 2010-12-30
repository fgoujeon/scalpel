template < typename T  >
const T &
max(const T& a, const T & b)
{
	return a > b ? a : b ;
}

int main()
{
	max<int>(3, 4);
}
