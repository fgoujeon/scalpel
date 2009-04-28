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

	protected :
		void
		update();

	private:
		int value_;
};

test::test(int i):
	value_(i)
{
}

test::test(const test& t):
	value_(t.value_)
{
}

const test&
test::operator=(const test& t)
{
	value_ = t.value_;
}

void
update()
{
}

