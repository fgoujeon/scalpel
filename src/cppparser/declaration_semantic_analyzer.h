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

#ifndef CPPPARSER_DECLARATION_SEMANTIC_ANALYZER_H
#define CPPPARSER_DECLARATION_SEMANTIC_ANALYZER_H

#include <string>
#include <boost/spirit.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#include "program_tree/program.h"

namespace cppparser
{

class declaration_semantic_analyzer
{
    public:
        std::shared_ptr<program_tree::program>
        analyze();
};

}

#endif
