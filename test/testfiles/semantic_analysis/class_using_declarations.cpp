struct s
{
	struct inner
	{
	};

	enum e{};

	typedef int integer;

	int
	operator[](int) const;

	operator bool() const;

	void f();

	int i;

	int j: 4;
};

struct s2: s
{
	using s::inner;
	using s::e;
	using s::integer;
	using s::operator[];
	using s::operator bool;
	using s::f;
	using s::i;
	using s::j;
};

struct s3
{
	class inner3: s
	{
		using s::inner;
		using s::e;
		using s::integer;
		using s::operator[];
		using s::operator bool;
		using s::f;
		using s::i;
		using s::j;
	};
};

