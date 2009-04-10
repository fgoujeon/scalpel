/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

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

#include "member_declarator_bit_field_member.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

member_declarator_bit_field_member::member_declarator_bit_field_member
(
    boost::optional<identifier>&& an_identifier
):
    identifier_(an_identifier)
{
	update_node_list();
}

member_declarator_bit_field_member::member_declarator_bit_field_member(const member_declarator_bit_field_member& o):
	composite_node(),
    identifier_(o.identifier_)
{
	update_node_list();
}

member_declarator_bit_field_member::member_declarator_bit_field_member(member_declarator_bit_field_member&& o):
    identifier_(std::move(o.identifier_))
{
	update_node_list();
}

const member_declarator_bit_field_member&
member_declarator_bit_field_member::operator=(const member_declarator_bit_field_member& o)
{
    identifier_ = o.identifier_;
	update_node_list();

	return *this;
}

void
member_declarator_bit_field_member::update_node_list()
{
	clear();
	if(identifier_) add(*identifier_);
}

}}} //namespace socoa::cpp::syntax_tree
