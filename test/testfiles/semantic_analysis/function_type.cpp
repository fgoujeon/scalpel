typedef int fun_t();

fun_t f;
fun_t* f_ptr;

class c
{
	typedef int const_fun_t() const;

	fun_t f;
	static fun_t g;
	const_fun_t h;
};

int
c::f()
{
	return 0;
}

