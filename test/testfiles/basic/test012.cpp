struct Foo
{
	int bar();
};

int main()
{
	int (Foo::*pf)() = &Foo::bar;
}

void function(int (Foo::*pf)())
{
}

