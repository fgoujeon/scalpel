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

#ifndef CPPPARSER_PROGRAM_SYNTAX_TREE_DECLARATION_SEQ_H
#define CPPPARSER_PROGRAM_SYNTAX_TREE_DECLARATION_SEQ_H

#include <vector>
#include <memory>
#include "item.h"
#include "declaration.h"

namespace cppparser { namespace program_syntax_tree
{

class declaration_seq: public item, public std::enable_shared_from_this<declaration_seq>
{
    public:
        const std::vector<std::shared_ptr<declaration>>&
        declarations() const;

        void
        add(std::shared_ptr<declaration> a_declaration);

        void
        accept(visitor& a_visitor) const;

    private:
        std::vector<std::shared_ptr<declaration>> m_declarations;
};

}} //namespace cppparser::program_syntax_tree

#endif
