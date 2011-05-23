namespace n1
{
	bool a, b, c;

	void foo()
	{
		a < b > c; //boolean expression
	}
}

namespace n2
{
	template<bool B>
	class a
	{
	};

	const bool b = true;

	void foo()
	{
		a < b > c; //declaration of variable c
	}
}

