template < class T  >
struct a_class
{
	typedef typename T::type type;

	a_class(const T& mem);

	type
	get_t() const;

	T member_;
	type t_;
};

template < class T>
a_class< T >  :: a_class (const T & mem ):
	member_ (mem )
{
}

template < class T>
a_class< T >:: type
a_class< T >  :: get_t ( ) const
{
	return typename T::type ();
}

class simple_class;

template class a_class<simple_class>;

int
main()
{
	a_class<simple_class> a;

	return 0;
}
