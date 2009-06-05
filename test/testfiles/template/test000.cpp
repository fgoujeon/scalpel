template < class T  >
struct a_class
{
	a_class(const T& mem);

	T member_;
};

template < class T>
a_class< T >  :: a_class (const T & mem ):
	member_ (mem )
{
}

class simple_class;

int
main()
{
	a_class<simple_class> a;

	return 0;
}
