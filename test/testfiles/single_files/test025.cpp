bool
fun(bool a, bool b, bool c, bool d)
{
    return a < b || c > d;
}



template <bool value>
class a
{
};

const bool b = true;
const bool c = false;

a<b || c>
fun2()
{
    a < b || c > d;
    return d;
}
