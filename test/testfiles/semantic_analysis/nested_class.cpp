class a_class
{
	public:
		class a_nested_class
		{
			int i;
		};

		class another_nested_class: public a_nested_class
		{
		};
};

a_class::a_nested_class anc;

