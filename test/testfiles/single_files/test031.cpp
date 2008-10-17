template<class T>
class crtp
{
};

class foo: public crtp<foo>
{
};


