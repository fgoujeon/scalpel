struct Test
{
	Test(int n);
};

Test::Test(int n)
try :
	number(n)
{

}
catch(const std::exception& e)
{
	throw e;
}

