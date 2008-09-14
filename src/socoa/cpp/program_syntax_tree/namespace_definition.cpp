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

#include "namespace_definition.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

namespace_definition::namespace_definition()
{
}

namespace_definition::namespace_definition(const std::string& name):
    m_name(name)
{
}

const std::string&
namespace_definition::get_name() const
{
    return m_name;
}

declaration_seq&
namespace_definition::get_body()
{
    return m_body;
}

const declaration_seq&
namespace_definition::get_body() const
{
    return m_body;
}

void
namespace_definition::accept(visitor& a_visitor) const
{
    a_visitor.visit(*this);
}

}}} //namespace socoa::cpp::program_syntax_tree
