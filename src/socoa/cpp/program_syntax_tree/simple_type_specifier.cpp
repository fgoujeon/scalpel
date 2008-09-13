/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <cassert>
#include "simple_type_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

simple_type_specifier::simple_type_specifier(const std::string& type):
    m_type(type)
{
    assert
    (
        type == "char" ||
        type == "wchar_t" ||
        type == "bool" ||
        type == "short" ||
        type == "int" ||
        type == "long" ||
        type == "signed" ||
        type == "unsigned" ||
        type == "float" ||
        type == "double" ||
        type == "void"
    );
}

const std::string&
simple_type_specifier::get_type() const
{
    return m_type;
}

void
simple_type_specifier::accept(visitor& a_visitor) const
{
    a_visitor.visit(*this);
}

}}} //namespace socoa::cpp::program_syntax_tree
