namespace n1
{
	bool a, b, c, d;

	void foo()
	{
		a < b || c > d; //boolean expression
	}
}

namespace n2
{
	template<bool B>
	class a
	{
	};

	const bool b = true, c = true;

	void foo()
	{
		a < b || c > d; //declaration of variable d
	}
}
