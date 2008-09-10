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

#include <iostream>
#include "class_specifier.h"

namespace cppparser { namespace program_syntax_tree
{

class_specifier::class_specifier(const std::string& name):
    m_name(name)
{
}

const std::string&
class_specifier::name() const
{
    return m_name;
}

void
class_specifier::accept(visitor& a_visitor) const
{
    a_visitor.visit(*this);
}

}} //namespace cppparser::program_syntax_tree
