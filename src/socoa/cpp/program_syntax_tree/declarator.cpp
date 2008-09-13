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

#include "declarator.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

declarator::declarator
(
    std::shared_ptr<direct_declarator> a_direct_declarator
):
    m_direct_declarator(a_direct_declarator)
{
}
/*
const std::vector<std::shared_ptr<ptr_operator>>&
declarator::get_ptr_operators() const
{
    return m_ptr_operators;
}

void
declarator::add(std::shared_ptr<ptr_operator> a_ptr_operator)
{
    m_ptr_operators.push_back(a_ptr_operator);
}
*/
const std::shared_ptr<direct_declarator>
declarator::get_direct_declarator() const
{
    return m_direct_declarator;
}

}}} //namespace socoa::cpp::program_syntax_tree
