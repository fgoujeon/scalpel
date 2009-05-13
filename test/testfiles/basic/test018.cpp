int main()
{
	const int ci;
	int* pi;
	const int* cpi;
	double d;

	pi = const_cast<int*>(&ci);

	return 0;
}

