/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "member_declarator_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

member_declarator_declarator::member_declarator_declarator
(
    declarator&& a_declarator,
    bool pure_specifier
):
    declarator_(std::move(a_declarator)),
    pure_specifier_(pure_specifier)
{
	update_node_list();
}

member_declarator_declarator::member_declarator_declarator(const member_declarator_declarator& o):
	composite_node(),
    declarator_(o.declarator_),
    pure_specifier_(o.pure_specifier_)
{
	update_node_list();
}

member_declarator_declarator::member_declarator_declarator(member_declarator_declarator&& o):
    declarator_(std::move(o.declarator_)),
    pure_specifier_(std::move(o.pure_specifier_))
{
	update_node_list();
}

const member_declarator_declarator&
member_declarator_declarator::operator=(const member_declarator_declarator& o)
{
    declarator_ = o.declarator_;
    pure_specifier_ = o.pure_specifier_;
	update_node_list();

	return *this;
}

void
member_declarator_declarator::update_node_list()
{
	clear();
	add(declarator_);
}

}}} //namespace scalpel::cpp::syntax_nodes
