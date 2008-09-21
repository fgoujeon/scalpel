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

#include "nested_name_specifier_template_id.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

nested_name_specifier_template_id::nested_name_specifier_template_id
(
    bool template_keyword,
    template_id&& a_template_id
):
    m_template_keyword(template_keyword),
    m_template_id(a_template_id)
{
}

bool
nested_name_specifier_template_id::has_template_keyword() const
{
    return m_template_keyword;
}

const template_id&
nested_name_specifier_template_id::get_template_id() const
{
    return m_template_id;
}

}}} //namespace socoa::cpp::program_syntax_tree
