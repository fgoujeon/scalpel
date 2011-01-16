class c
{
};

namespace n
{
	class c
	{
	};

	void (c::*fun_ptr)(int);
	int ::c::* int_ptr;
}

void f(int c::* int_ptr)
{
}

