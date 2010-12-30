using namespace std;

namespace A
{
	int name;
	namespace N
	{
		class name;
		void f();
	}
}

namespace B = A::N;

int name;

void A::N::f()
{
}

