namespace n1
{
	int a, b, c, d;

	bool bool_ = a < b || c > (d); //boolean expression
}

namespace n2
{
	template<bool B>
	bool
	a(bool b)
	{
		return b && B;
	}

	const bool b = true, c = true, d = true;

	bool bool_ = a < b || c > (d); //function template call
}
