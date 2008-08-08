#ifndef VIRTUAL_H
#define VIRTUAL_H

class Virtual
{
	protected:
		virtual void virtual_function() = 0;

	private:
		int number: 42;
		static int foo;
};

Virtual::foo = 2;

#endif
