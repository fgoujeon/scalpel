#include <boost/spirit.hpp>
#include "Grammar.h"
#include "Preprocessor.h"

using namespace boost::spirit;

int main(int argc, char** argv)
{
    CppParser::Preprocessor preprocessor;
    std::string preprocessed_code = preprocessor.process("test/testfiles/single_preprocessing_files/test000.cpp");


    CppParser::Grammar grammar;
    parse_info<> info = parse(preprocessed_code.c_str(), grammar, space_p);
    if(info.full)
        std::cout << "Success!";
    else
        std::cout << "Failed at :\n\n" << info.stop;


    return 0;
}
