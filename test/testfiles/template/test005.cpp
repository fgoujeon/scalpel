template<typename T>
struct foo{};

template<typename T>
struct bar{};

foo<bar<int>> f;
