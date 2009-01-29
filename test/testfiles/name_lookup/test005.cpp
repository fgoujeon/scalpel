template<typename T>
class c1;

namespace a
{
	template<typename T>
	class c2
	{
	};

	namespace n
	{
		template<typename T>
		class c3
		{
		};

		c3<int> a_c3;
		c2<int> a_c2;
		c1<int> a_c1;
	}
}

template<typename T>
class c1
{
};
