namespace std
{
	class ostringstream;
	class string;
	class vector;
}

std::string dump(const std::vector& v)
{
	std::ostringstream oss;

	for(std::vector<unsigned int>::const_iterator i = v.begin(); i != v.end(); ++i)
	{
		oss << *i << '\n';
	}
	
	return oss.str();
}

int main(int argc, char** argv)
{
	std::vector<unsigned int> v;

	v.push_back(23);
	v.push_back(663);

	std::cout << dump(v);

	return 0;
}
