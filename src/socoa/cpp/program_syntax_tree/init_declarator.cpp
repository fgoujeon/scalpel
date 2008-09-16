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

#include "init_declarator.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

init_declarator::init_declarator
(
    declarator&& a_declarator
):
    m_declarator(a_declarator)
{
}

const declarator&
init_declarator::get_declarator() const
{
    return m_declarator;
}

}}} //namespace socoa::cpp::program_syntax_tree
