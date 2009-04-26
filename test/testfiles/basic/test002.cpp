class int_vector
{
} ;

int main(int argc, char * *argv)
{
	int_vector v;

	v. push_back( 23);
	v .push_back (663 ) ;

	for(int_vector::iterator i = v.begin(); i != v.end ( ) ; ++i)
	{
		cout << *i << '\n';
	}

	return 0;
}
