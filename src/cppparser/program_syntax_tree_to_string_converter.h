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

#ifndef CPPPARSER_PROGRAM_SYNTAX_TREE_TO_STRING_CONVERTER_H
#define CPPPARSER_PROGRAM_SYNTAX_TREE_TO_STRING_CONVERTER_H

#include <string>
#include <sstream>
#include <memory>
#include "program_syntax_tree/visitor.h"

namespace cppparser
{

namespace program_syntax_tree
{
class declaration_seq;
class namespace_definition;
class class_specifier;
}

class program_syntax_tree_to_string_converter: public program_syntax_tree::visitor
{
    public:
        program_syntax_tree_to_string_converter();

        std::string
        operator()(const std::shared_ptr<program_syntax_tree::declaration_seq> translation_unit);

    private:
        void
        visit(const program_syntax_tree::declaration_seq& item);

        void
        visit(const program_syntax_tree::namespace_definition& item);

        void
        visit(const program_syntax_tree::class_specifier& item);

        void
        indent();

        std::ostringstream m_result_oss;
        unsigned int m_indentation_level;
};

}

#endif
