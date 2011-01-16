class c
{
};

namespace n
{
	class c
	{
	};

	void (c::*fun_ptr)(int);
	void (::c::*fun_ptr2)(int);
}

