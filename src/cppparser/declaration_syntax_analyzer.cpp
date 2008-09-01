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
#include <stdexcept>

#include "declaration_syntax_analyzer.h"

using namespace boost::spirit;

namespace cppparser
{

declaration_syntax_analyzer::declaration_syntax_analyzer():
    m_grammar(m_grammar_configuration)
{
    m_grammar_configuration.skip_function_bodies = true;
}

boost::spirit::tree_match<const char*>::container_t
declaration_syntax_analyzer::analyze(const std::string& input)
{
    tree_parse_info<> info = ast_parse(input.c_str(), m_grammar, space_p);

    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    return info.trees;
}

}
