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

#include "template_declaration.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

template_declaration::template_declaration(bool exported, std::shared_ptr<declaration> declaration_part):
    m_exported(exported),
    m_declaration_part(declaration_part)
{
}

bool
template_declaration::exported() const
{
    return m_exported;
}

const std::shared_ptr<declaration>
template_declaration::declaration_part() const
{
    return m_declaration_part;
}

}}} //namespace socoa::cpp::program_syntax_tree
