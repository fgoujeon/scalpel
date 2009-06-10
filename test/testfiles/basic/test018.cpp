class base{};
class derived: public base{};

int main()
{
	int i;
	const int ci;
	int* pi;
	double d = 9.6;

	pi = const_cast<int*>(&ci);
	i = static_cast<int>(d);

	base* b = new derived();
	if(derived* d = dynamic_cast<derived*>(b))
	{
	}

	i = reinterpret_cast<int>(b);

	i = (int)d;

	b2 base = (base)i;

	return 0;
}

