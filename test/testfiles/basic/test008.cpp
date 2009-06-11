class test : public super_test , virtual public virtual_base, protected virtual virtual_base2
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

