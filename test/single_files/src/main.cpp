#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <boost/spirit.hpp>
#include <CppParser/Grammar.h>

using namespace boost::spirit;
using namespace std;

int
main()
{
    CppParser::Grammar grammar;

    for(unsigned int i = 0; ; ++i)
    {
        std::ostringstream file_name_oss;
        file_name_oss << "files/test" << setfill('0') << setw(3) << i << ".cpp";
        std::string file_name(file_name_oss.str());

        std::ifstream file(file_name.c_str());
        if(!file)
        {
            break;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();
        file.close();

        cout << "Parsing " << file_name << "... ";
        parse_info<> info = parse(buffer.str().c_str(), grammar, space_p);
        if(info.full) //success
        {
            cout << "Success!";
        }
        else
        {
            cout << "\n=============================\n";
            cout << buffer.str() << endl;
            cout << "=============================\n";
            cout << "/////////////////////////////\n";
            cout << "Parsing failed\n";
            cout << "stopped at: \": " << info.stop << "\"\n";
            cout << "/////////////////////////////\n";
        }

        cout << '\n';
    }

    return 0;
}
