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

#include "declaration_seq.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

const std::vector<std::shared_ptr<declaration>>&
declaration_seq::get_declarations() const
{
    return m_declarations;
}

void
declaration_seq::add(std::shared_ptr<declaration> a_declaration)
{
    m_declarations.push_back(a_declaration);
}

}}} //namespace socoa::cpp::program_syntax_tree
