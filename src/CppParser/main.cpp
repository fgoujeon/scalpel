#include <boost/spirit.hpp>
#include "Grammar.h"
#include "Preprocessor.h"

using namespace boost::spirit;

int main(int argc, char** argv)
{
    std::string test_file_name;
    if(argc > 1)
        test_file_name = argv[1];
    else
        test_file_name = "test/testfiles/single_files_with_pp_tokens/000.cpp";

    Preprocessor preprocessor;
    std::string preprocessed_code = preprocessor(test_file_name);


    CppParser::Grammar grammar;
    parse_info<> info = parse(preprocessed_code.c_str(), grammar, space_p);
    if(info.full)
        std::cout << "Success!";
    else
        std::cout << "Failed at :\n\n" << info.stop;


    return 0;
}
