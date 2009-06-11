template < class T  >
struct a_class
{
	typedef typename T::type type;

	a_class(const T& mem);

	T member_;
	type t_;
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
