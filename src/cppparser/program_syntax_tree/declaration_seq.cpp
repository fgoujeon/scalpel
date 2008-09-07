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

#include "declaration_seq.h"

namespace cppparser { namespace program_syntax_tree
{

const std::vector<std::shared_ptr<declaration>>&
declaration_seq::declarations() const
{
    return m_declarations;
}

void
declaration_seq::add(std::shared_ptr<declaration> a_declaration)
{
    m_declarations.push_back(a_declaration);
}

void
declaration_seq::accept(visitor& a_visitor) const
{
    a_visitor.visit(*this);
}

}} //namespace cppparser::program_syntax_tree
