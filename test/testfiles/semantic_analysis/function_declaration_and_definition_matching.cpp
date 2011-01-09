void f(const int);
void f(volatile int)
{
}

void g(const volatile int);
void g(int)
{
}

void i(int* volatile const);
void i(int*)
{
}

void h(const double* const);
void h(const double ds[5])
{
}

