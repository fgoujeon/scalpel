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

#include "direct_declarator.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

direct_declarator::direct_declarator(std::shared_ptr<declarator_id> a_declarator_id):
    m_declarator_id(a_declarator_id)
{
}

const std::shared_ptr<declarator_id>
direct_declarator::get_declarator_id() const
{
    return m_declarator_id;
}

const std::shared_ptr<declarator>
direct_declarator::get_declarator() const
{
    return m_declarator;
}

}}} //namespace socoa::cpp::program_syntax_tree
