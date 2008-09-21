/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <boost/spirit.hpp>
#include <cppunit/TestSuite.h>

#include "standard_library_test.h"

using namespace boost::spirit;
using namespace std;

void
standard_library_test::parse_files()
{
    for(unsigned int i = 0; ; ++i)
    {
		//generate file's name
        std::ostringstream file_name_oss;
        file_name_oss << "testfiles/standard_library/test" << setfill('0') << setw(3) << i << ".cpp";

		//check whether file exists
        std::ifstream file(file_name_oss.str().c_str());
        if(!file)
        {
            if(i == 0)
                throw runtime_error("There's no file to parse.");
            else
                break; //exit if file doesn't exist
        }

		//preprocess file
		std::string preprocessed_code = m_preprocessor(file_name_oss.str());

		//parse preprocessed code
        m_declaration_syntax_analyzer(preprocessed_code); //throws an exception if parsing fails
    }
}

