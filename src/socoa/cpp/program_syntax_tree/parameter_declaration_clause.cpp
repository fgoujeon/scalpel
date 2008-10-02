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

#include "parameter_declaration_clause.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

parameter_declaration_clause::parameter_declaration_clause
(
    std::shared_ptr<sequence<parameter_declaration, ','>> a_parameter_declaration_list,
    bool trailing_comma,
    bool ellipsis
):
    m_parameter_declaration_list(a_parameter_declaration_list),
    m_trailing_comma(trailing_comma),
    m_ellipsis(ellipsis)
{
}

const std::shared_ptr<sequence<parameter_declaration, ','>>
parameter_declaration_clause::get_parameter_declaration_list() const
{
    return m_parameter_declaration_list;
}

bool
parameter_declaration_clause::has_trailing_comma() const
{
    return m_trailing_comma;
}

bool
parameter_declaration_clause::has_ellipsis() const
{
    return m_ellipsis;
}

}}} //namespace socoa::cpp::program_syntax_tree
