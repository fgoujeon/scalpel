template<bool B>
struct foo{};

const bool a = true, b = true;
const int i = 2, j = 3, k = 6;
typedef int t;
namespace n{typedef int t;}

foo < t * > f1;
foo < n::t * > f1;
foo < t ** > f1;
foo < i * j > f1;
foo < i * j * k > f1;
foo < i * j + k > f1;
foo < foo < t * > > f1;
foo < foo < t > * > f1;
foo < foo < t * > * > f1;
foo < t & > f1;
foo < a & b > f1;
foo < a || b > f1;
foo < a && b > f1;
foo < (i > j) > f2;
foo < i < j > f3;
foo < i < j + k > f3;
foo < i < j && (i > j) > f4;
