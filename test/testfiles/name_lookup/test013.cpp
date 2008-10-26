template<bool B>
class boolean
{
};
const bool a = true, b = true;

template<int I>
class number
{
};
const int i = 0, j = 1;
const int i001 = (i + j > 0) + i;

template<char C>
class character
{
};

template<class T>
class container
{
};

template<class T = boolean<i < j>, class U>
class pair
{
};


boolean<a || b> b001;
boolean<(a || b)> b002;

number<(i + j > 0) + i> n001;
number<i < j> n002;

character<'('> ch001;

container<boolean<true>> c001;

pair<boolean<a && b && i < 2>, number<3 + (-4) / j < (1 >> i)>> p001;

void foo(pair<boolean<a && b && i < 2>, number<3 + (-4) / j < (1 >> i)>> p)
{
}
