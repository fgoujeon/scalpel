namespace M
{
    struct B
    {
        template <typename T>
        class C
        {
        };
    };
}

namespace N
{
    class Y: public M::B
    {
        class X
        {
            C<int> c;
        };
    };
}
