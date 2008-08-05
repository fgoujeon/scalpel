#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <stdexcept>
#include <boost/spirit.hpp>
#include <CppParser/Grammar.h>

using namespace boost::spirit;
using namespace std;

int
main()
{
    CppParser::Grammar grammar;

    std::string file_name("files/test.cpp");
    std::ifstream file(file_name.c_str());
    if(!file)
    {
        std::runtime_error e(("Unable to open " + file_name).c_str());
        throw e;
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();


    parse_info<> info = parse(buffer.str().c_str(), grammar, space_p);
    cout << "=============================\n";
    cout << buffer.str() << endl;
    cout << "=============================\n";
    if(info.full) //success
    {
        cout << "Parsing succeeded!\n";
    }
    else
    {
        cout << "Parsing failed\n";
        cout << "stopped at: \": " << info.stop << "\"\n";
    }

    return 0;
}
