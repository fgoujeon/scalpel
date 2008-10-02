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

#include "simple_declaration.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

simple_declaration::simple_declaration
(
    std::shared_ptr<sequence<decl_specifier>> a_decl_specifier_seq,
    std::shared_ptr<sequence<init_declarator, ','>> an_init_declarator_list
):
    m_decl_specifier_seq(a_decl_specifier_seq),
    m_init_declarator_list(an_init_declarator_list)
{
}

const std::shared_ptr<sequence<decl_specifier>>
simple_declaration::get_decl_specifier_seq() const
{
    return m_decl_specifier_seq;
}

const std::shared_ptr<sequence<init_declarator, ','>>
simple_declaration::get_init_declarator_list() const
{
    return m_init_declarator_list;
}

}}} //namespace socoa::cpp::program_syntax_tree
