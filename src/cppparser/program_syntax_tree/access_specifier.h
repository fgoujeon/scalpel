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

#ifndef CPPPARSER_PROGRAM_SYNTAX_TREE_ACCESS_SPECIFIER_H
#define CPPPARSER_PROGRAM_SYNTAX_TREE_ACCESS_SPECIFIER_H

#include "member_specification_item.h"
#include "item.h"

namespace cppparser { namespace program_syntax_tree
{

class access_specifier: public member_specification_item, public item
{
    public:
        enum possible_value
        {
            PUBLIC,
            PROTECTED,
            PRIVATE
        };

        access_specifier(possible_value value);

        possible_value
        value() const;

        void
        accept(visitor& a_visitor) const;

    private:
        possible_value m_value;
};

}} //namespace cppparser::program_syntax_tree

#endif
