class c
{
	union inner
	{
		double d;
		int i;
	};
};

union u
{
	union inner
	{
		double d;
		int i;
	};

	char c;
	inner i;
};

u::inner ui;

