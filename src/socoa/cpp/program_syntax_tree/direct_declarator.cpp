/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

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

direct_declarator::direct_declarator
(
    std::shared_ptr<declarator_id> a_declarator_id,
    std::vector<std::shared_ptr<direct_declarator_part>>&& other_parts
):
    m_declarator_id(a_declarator_id),
    m_other_parts(other_parts)
{
}

direct_declarator::direct_declarator
(
    std::shared_ptr<declarator> a_declarator,
    std::vector<std::shared_ptr<direct_declarator_part>>&& other_parts
):
    m_declarator(a_declarator),
    m_other_parts(other_parts)
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

const std::vector<std::shared_ptr<direct_declarator_part>>&
direct_declarator::get_other_parts() const
{
    return m_other_parts;
}

}}} //namespace socoa::cpp::program_syntax_tree
