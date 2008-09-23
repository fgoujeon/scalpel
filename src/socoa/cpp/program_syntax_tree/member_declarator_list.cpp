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

#include "member_declarator_list.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

member_declarator_list::member_declarator_list
(
    std::vector<std::shared_ptr<member_declarator>>&& member_declarators
):
    member_declarators_(member_declarators)
{
}

const std::vector<std::shared_ptr<member_declarator>>&
member_declarator_list::get_member_declarators() const
{
    return member_declarators_;
}

}}} //namespace socoa::cpp::program_syntax_tree
