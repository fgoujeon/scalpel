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

#ifndef CPPPARSER_PROGRAM_SYNTAX_TREE_MEMBER_SPECIFICATION_H
#define CPPPARSER_PROGRAM_SYNTAX_TREE_MEMBER_SPECIFICATION_H

#include <vector>
#include <memory>
#include "item.h"
#include "member_specification_item.h"

namespace cppparser { namespace program_syntax_tree
{

class member_specification: public item
{
    public:
        const std::vector<std::shared_ptr<member_specification_item>>&
        items() const;

        void
        add(std::shared_ptr<member_specification_item> item);

        void
        accept(visitor& a_visitor) const;

    private:
        std::vector<std::shared_ptr<member_specification_item>> m_items;
};

}} //namespace cppparser::program_syntax_tree

#endif
