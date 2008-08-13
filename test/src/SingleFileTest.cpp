/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <boost/spirit.hpp>
#include <CppParser/Grammar.h>
#include <cppunit/TestSuite.h>

#include "SingleFileTest.h"

using namespace boost::spirit;
using namespace std;

void SingleFileTest::parse_files()
{
    CppParser::Grammar grammar;

    for(unsigned int i = 0; ; ++i)
    {
		//generate file's name
        std::ostringstream file_name_oss;
        file_name_oss << "testfiles/single_files/test" << setfill('0') << setw(3) << i << ".cpp";

		//open file
        std::ifstream file(file_name_oss.str().c_str());
        if(!file)
        {
            if(i == 0)
                throw runtime_error("There's no file to parse.");
            else
                break; //exit if file doesn't exist
        }

		//read file
        ostringstream buffer;
        buffer << file.rdbuf();

		//close file
        file.close();

		//parse file
        parse_info<> info = parse(buffer.str().c_str(), grammar, space_p);
        std::string stopped_at = info.stop;

        ostringstream failure_message;
        failure_message << "Failed to parse " << file_name_oss.str() << "\n";
        failure_message << "Parsing stopped at:\n***\n" << stopped_at << "\n***";

        CPPUNIT_ASSERT_MESSAGE
        (
            failure_message.str(),
            info.full
        );
    }
}

