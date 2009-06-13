template<typename T>
struct foo{};

template<typename T = foo<double>>
struct bar{};

foo<bar<int>> f;
