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

#include "init_declarator_list.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

const std::vector<std::shared_ptr<init_declarator>>
init_declarator_list::get_init_declarators() const
{
    return m_init_declarators;
}

void
init_declarator_list::set_init_declarators(std::vector<std::shared_ptr<init_declarator>> init_declarators)
{
    m_init_declarators = init_declarators;
}

void
init_declarator_list::add(std::shared_ptr<init_declarator> an_init_declarator)
{
    m_init_declarators.push_back(an_init_declarator);
}

}}} //namespace socoa::cpp::program_syntax_tree
