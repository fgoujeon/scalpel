class Virtual
{
	protected:
		virtual void virtual_function() = 0;

	private:
		int number: 42;
		static int foo;
};

int Virtual::foo = 2;
