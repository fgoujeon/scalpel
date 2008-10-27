struct B
{
    template <typename T>
    class C
    {
    };
};

namespace N
{
    class Y: public B
    {
        class X
        {
            C<int> c;
        };
    };
}
