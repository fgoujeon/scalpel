int main(int argc, char** argv)
{
	std::vector<unsigned int> v;

	v.push_back(23);
	v.push_back(663);

	for(std::vector<unsigned int>::iterator i = v.begin(); i != v.end(); ++i)
	{
		std::cout << *i << '\n';
	}

	return 0;
}
