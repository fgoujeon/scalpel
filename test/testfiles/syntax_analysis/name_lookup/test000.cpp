namespace A
{
	int name;
	namespace N
	{
		class name;
		void f();
	}
}

int name;

void A::N::f()
{
	name<int> c;
}

