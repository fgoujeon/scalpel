int foo()
{
	goto end_label;
	return 1;
	end_label  : return 0;
}

int bar()
{
	goto end_label2 ;
	return 1;
	end_label2  : ;
	return 0;
}
