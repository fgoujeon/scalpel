unsigned long max(int a, int b) throw()
{
	if(a > b) return a;
	else return b;
}

void function(int i) throw ( std::exception, CustomExceptionType    )
{
	do_something(i);
}
