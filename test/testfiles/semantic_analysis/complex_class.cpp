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

class test: public n::n2::super_test, virtual virtual_base, protected virtual virtual_base2
{
	public:
		explicit
		test(int i);

		test(const test& t);

		virtual
		~test();

		const test&
		operator=(const test& t);

		bool
		operator==(const test& t) const;

		void*
		operator new[](long unsigned int, void*);

		void
		operator delete[](void*);

		operator int() const;

		static
		bool
		static_function();

		inline
		int
		value() const;

		virtual
		void
		pure_virtual() ;//= 0;

	protected:
		void
		update();

	private:
		int value_;
		static const bool b = false;
};

test::test(int)
{
}

test::test(const test&)
{
}

test::~test()
{
}

const test&
test::operator=(const test& rhs)
{
	value_ = rhs.value_;
	return *this;
}

bool
test::operator==(const test& rhs) const
{
	return value_ == rhs.value_;
}

void*
test::operator new[](long unsigned int, void*)
{
	return 0;
}

void
test::operator delete[](void*)
{
}

test::operator int() const
{
	return value_;
}

bool
test::static_function()
{
	return b;
}

int
test::value() const
{
	return value_;
}

void
test::pure_virtual()
{
}

void
test::update()
{
}

