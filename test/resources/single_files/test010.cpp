template<typename T>
class Complex
{
	public:
		Complex();
		Complex(T r, T i);

	private:
		T r;
		T i;
};

template<typename T>
Complex<T>::Complex():
	r(0),
	i(0)
{
}

template<typename T>
Complex<T>::Complex(T r, T i):
	r(r),
	i(i)
{
}

