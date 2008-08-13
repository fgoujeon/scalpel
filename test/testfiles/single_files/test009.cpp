class Foo
{
	class Bar;
	class Babar
	{
		public:
			Babar();
	};
};

class Foo::Bar: public Parent
{
};
