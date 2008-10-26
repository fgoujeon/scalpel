int main(int argc, char** argv)
{
	try
	{
		may_throw_exception();
	}
	catch(const SomeErrorType& e)
	{
		throw e;
	}
	catch(...)
	{
		throw;
	}
}

