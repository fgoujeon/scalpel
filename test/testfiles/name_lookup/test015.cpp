template<bool b>
class Foo
{
};

Foo<a && b>
bar()
{
    return 0;
}

Foo<(a > b)>
bar2()
{
    return 0;
}
