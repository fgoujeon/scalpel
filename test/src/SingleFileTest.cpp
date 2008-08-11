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
		//generate filename
        std::ostringstream file_name_oss;
        file_name_oss << "resources/single_files/test" << setfill('0') << setw(3) << i << ".cpp";
        std::string file_name(file_name_oss.str());

		//open file
        std::ifstream file(file_name.c_str());
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

        ostringstream failure_message;
        failure_message << "Failed to parse " << file_name_oss.str() << "\n";
        failure_message << "Parsing stopped at:\n\t" << info.stop;

        CPPUNIT_ASSERT_MESSAGE
        (
            failure_message.str(),
            info.full
        );
    }
}

