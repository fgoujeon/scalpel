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

#include "parameter_declaration.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

parameter_declaration::parameter_declaration
(
    sequence<decl_specifier>&& a_decl_specifier_seq,
    std::shared_ptr<declarator> a_declarator,
    bool equal
):
    m_decl_specifier_seq(a_decl_specifier_seq),
    m_declarator(a_declarator),
    m_equal(equal)
{
}

const sequence<decl_specifier>&
parameter_declaration::get_decl_specifier_seq() const
{
    return m_decl_specifier_seq;
}

const std::shared_ptr<declarator>
parameter_declaration::get_declarator() const
{
    return m_declarator;
}

bool
parameter_declaration::has_equal() const
{
    return m_equal;
}

}}} //namespace socoa::cpp::program_syntax_tree
