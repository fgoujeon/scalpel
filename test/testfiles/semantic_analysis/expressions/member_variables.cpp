struct A
{
	char c: 3;
};

struct B: A
{
};

struct C
{
	double d;
};

struct test
{
	struct inner: B, C
	{
		int i: 5;
	};
};

struct test2: B, C
{
	int i: 5;
};

test::inner v0;
int v1 = v0.i;
char v2 = v0.c;
double v3 = v0.d;

test2 v4;
int v5 = v4.i;
char v6 = v4.c;
double v7 = v4.d;

