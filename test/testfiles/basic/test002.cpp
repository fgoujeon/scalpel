class vector
{
};

int main(int argc, char** argv)
{
	vector<unsigned int> v;

	v.push_back(23);
	v.push_back(663);

	for(vector<unsigned int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		cout << *i << '\n';
	}

	return 0;
}
