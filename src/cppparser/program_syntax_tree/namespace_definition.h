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

#ifndef CPPPARSER_PROGRAM_SYNTAX_TREE_NAMESPACE_DEFINITION_H
#define CPPPARSER_PROGRAM_SYNTAX_TREE_NAMESPACE_DEFINITION_H

#include <string>
#include "declaration_seq.h"
#include "declaration.h"

namespace cppparser { namespace program_syntax_tree
{

class namespace_definition: public declaration, public std::enable_shared_from_this<namespace_definition>
{
    public:
        explicit namespace_definition(const std::string& name);

        const std::string&
        name() const;

        declaration_seq&
        body();

        const declaration_seq&
        body() const;

        void
        accept(visitor& a_visitor) const;

    private:
        std::string m_name;
        declaration_seq m_body;
};

}} //namespace cppparser::program_syntax_tree

#endif
