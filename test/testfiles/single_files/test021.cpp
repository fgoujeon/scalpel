void foo()
{
    if(__position > __s.size())
        __throw_out_of_range(("bitset::bitset initial position " "not valid"));
}
