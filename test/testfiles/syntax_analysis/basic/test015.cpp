int main()
{
	int t [ 5  ] ;
	t [ 0 ] = 45;
	t[1 ] = 54;

	int t2 [ ] = { 0, 4, 45, 42 };
	int t3 [4] = {};

	int (&t_ref)[5] = t;

	int* dt = new int  [ 10 ] ;
	delete [  ] dt;

	return 0;
}
