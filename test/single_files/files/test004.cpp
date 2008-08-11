int main(int argc, char** argv)
{
	if(argc <= 1)
	{
		std::cout << "There's no argument";
	}
	else
	{
		std::cout << "There's ";
		
		switch(argc - 1)
		{
			case 1:
				std::cout << "one";
			case 2:
				std::cout << "two";
			case 3:
			case 4:
			case 5:
				std::cout << "more than two";
			default:
				std::cout << "a lot of";
		}

		std::cout << " argument";

		if(argc > 2) std::cout << "s";
	}

	return 0;
}
