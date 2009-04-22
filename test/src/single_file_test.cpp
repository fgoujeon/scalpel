/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <fstream>

#include "single_file_test.hpp"

using namespace boost::spirit;
using namespace std;

void
single_file_test::parse_files(const std::string& test_directory)
{
    const std::string directory_name("testfiles/" + test_directory);

    for(unsigned int i = 0; ; ++i)
    {
		//generate file's name
        std::ostringstream file_name_oss;
        file_name_oss << directory_name << "/test" << setfill('0') << setw(3) << i << ".cpp";

		//open file
        std::ifstream file(file_name_oss.str().c_str());
        if(!file)
        {
            if(i == 0)
                throw runtime_error("There's no file to parse in " + directory_name + ".");
            else
                break; //exit if file doesn't exist
        }

		//read file
        ostringstream buffer;
        buffer << file.rdbuf();

		//close file
        file.close();

		//analyze file
		std::cout << "Analyzing " << file_name_oss.str() << "...\n";
        socoa::cpp::syntax_tree tree = m_syntax_analyzer(buffer.str()); //throws an exception if parsing fails

		//check syntax analysis results
		if(buffer.str() != tree.raw_code())
		{
			std::cout << "Analysis error!\n";
			std::cout << "Original content of " << file_name_oss.str() << ":\n";
			std::cout << "***\n";
			std::cout << buffer.str();
			std::cout << "\n***\n";
			std::cout << "Analysis results:\n";
			std::cout << "***\n";
			std::cout << tree.raw_code();
			std::cout << "\n***\n\n";

			throw "Analysis error!";
		}
    }
}

