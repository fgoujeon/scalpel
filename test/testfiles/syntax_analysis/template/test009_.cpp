template<bool B>
struct foo{};

const bool a = true, b = true;
const int i = 2, j = 3;

foo < a && b > f1;
foo < (i > j) > f2;
foo < i < j > f3;
foo < i < j && (i > j) > f4;
