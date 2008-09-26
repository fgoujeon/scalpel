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

#include "namespace_definition.h"

namespace socoa { namespace cpp { namespace program_syntax_tree
{

namespace_definition::namespace_definition
(
    std::shared_ptr<identifier> an_identifier,
    std::shared_ptr<sequence<declaration>> a_declaration_seq
):
    identifier_(an_identifier),
    m_declaration_seq(a_declaration_seq)
{
}

const std::shared_ptr<identifier>
namespace_definition::get_identifier() const
{
    return identifier_;
}

const std::shared_ptr<sequence<declaration>>
namespace_definition::get_declaration_seq() const
{
    return m_declaration_seq;
}

}}} //namespace socoa::cpp::program_syntax_tree
