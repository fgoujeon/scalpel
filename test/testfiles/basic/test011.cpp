int main()
{
	test* a_test = new test(53);
	test -> value(42);
	delete test;

	test another_test ( 12 ) ;
	another_test . value ( 34 ) ;

    char memory[sizeof(test)]; 
    void* place = memory;   
    
    test* f = new(place) test(); 

	return 0;
}
