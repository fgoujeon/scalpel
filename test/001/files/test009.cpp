#ifndef VIRTUAL_H
#define VIRTUAL_H

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

#endif
