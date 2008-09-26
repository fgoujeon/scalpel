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

#include "member_declaration_member_declarator_list.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

member_declaration_member_declarator_list::member_declaration_member_declarator_list
(
    std::shared_ptr<sequence<decl_specifier>> a_decl_specifier_seq,
    std::shared_ptr<member_declarator_list> a_member_declarator_list
):
    decl_specifier_seq_(a_decl_specifier_seq),
    member_declarator_list_(a_member_declarator_list)
{
}

const std::shared_ptr<sequence<decl_specifier>>
member_declaration_member_declarator_list::get_decl_specifier_seq() const
{
    return decl_specifier_seq_;
}

const std::shared_ptr<member_declarator_list>
member_declaration_member_declarator_list::get_member_declarator_list() const
{
    return member_declarator_list_;
}

}}} //namespace socoa::cpp::program_syntax_tree
