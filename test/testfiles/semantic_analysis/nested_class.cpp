class a_class
{
	public:
		class nested_class
		{
			int i;
		};

		class nested_class2: public nested_class
		{
		};
};

a_class::nested_class anc;

