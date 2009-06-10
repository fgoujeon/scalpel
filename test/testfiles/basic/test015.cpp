int main()
{
	int t [ 5  ] ;
	t [ 0 ] = 45;
	t[1 ] = 54;

	int (&t_ref)[5] = t;

	int* dt = new int  [ 10 ] ;
	delete [  ] dt;

	return 0;
}
