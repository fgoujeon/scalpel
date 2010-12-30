namespace n
{
	namespace n2
	{
		class super_test
		{
		};
	}
}

class virtual_base
{
};

class virtual_base2
{
};

class test : public n::n2::super_test, virtual virtual_base, protected virtual virtual_base2
{
	public:
		explicit
		test ( int i ) ;

		test ( const test & t ) ;

		virtual
		~ test ( ) ;

		const test &
		operator = ( const test& t );

		operator int ( );

		void*
		operator new [ ] (unsigned int, void * ){}

		void
		operator delete [ ] (void * ){}

		int
		value() const;

		virtual
		void
		pure_virtual() = 0 ;

	protected :
		void
		update();

	private:
		int value_;
		static const bool b_ = true ;
		static const bool b2_ = 0 == 1;
};

test :: test(int i):
	super_test(i) ,
	value_(i)
{
}

test::test ( const test& t ) :
	value_ ( t . value_ )
{
}

const test&
test::operator=(const test& t)
{
	value_ = t.value_;
}

test::operator int ()
{
	return value_;
}

int
test::value () const
{
	return value_;
}

void
update()
{
}

