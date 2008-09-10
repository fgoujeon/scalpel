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

#include "access_specifier.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

access_specifier::access_specifier(possible_value value):
    m_value(value)
{
}

access_specifier::possible_value
access_specifier::value() const
{
    return m_value;
}

void
access_specifier::accept(visitor& a_visitor) const
{
    a_visitor.visit(*this);
}

}}} //namespace socoa::cpp::program_syntax_tree
