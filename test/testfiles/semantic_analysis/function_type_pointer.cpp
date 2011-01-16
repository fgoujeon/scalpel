typedef int (*const fun_ptr_t)();

int (*const fun_ptr)();
fun_ptr_t fun_ptr2;

void f(void (*fun_ptr)(int))
{
}

