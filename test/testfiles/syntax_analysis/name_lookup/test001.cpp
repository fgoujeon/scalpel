namespace A
{
	class name;
	namespace N
	{
		void f();
	}
}

int name;

void A::N::f()
{
	name<int> c;
}

