int main()
{
	int i = 34;
	do
	{
		foo();
		bar();
		--i;
	} while  ( i >= 0 )   ;

	bool loop_condition = true;
	while( loop_condition  )
	{
		function( & loop_condition);
	}
}

