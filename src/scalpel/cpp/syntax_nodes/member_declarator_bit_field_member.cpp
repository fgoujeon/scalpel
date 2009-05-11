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

#include "member_declarator_bit_field_member.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

member_declarator_bit_field_member::member_declarator_bit_field_member
(
    boost::optional<identifier>&& identifier_node,
	boost::optional<space>&& post_identifier_space_node,
	boost::optional<space>&& post_colon_space_node,
	conditional_expression&& conditional_expression_node
):
    identifier_(identifier_node),
	post_identifier_space_(post_identifier_space_node),
	post_colon_space_(post_colon_space_node),
	conditional_expression_(conditional_expression_node)
{
	update_node_list();
}

member_declarator_bit_field_member::member_declarator_bit_field_member(const member_declarator_bit_field_member& o):
	composite_node(),
    identifier_(o.identifier_),
	post_identifier_space_(o.post_identifier_space_),
	post_colon_space_(o.post_colon_space_),
	conditional_expression_(o.conditional_expression_)
{
	update_node_list();
}

member_declarator_bit_field_member::member_declarator_bit_field_member(member_declarator_bit_field_member&& o):
    identifier_(std::move(o.identifier_)),
	post_identifier_space_(std::move(o.post_identifier_space_)),
	post_colon_space_(std::move(o.post_colon_space_)),
	conditional_expression_(std::move(o.conditional_expression_))
{
	update_node_list();
}

const member_declarator_bit_field_member&
member_declarator_bit_field_member::operator=(const member_declarator_bit_field_member& o)
{
    identifier_ = o.identifier_;
	post_identifier_space_ = o.post_identifier_space_;
	post_colon_space_ = o.post_colon_space_;
	conditional_expression_ = o.conditional_expression_;

	update_node_list();

	return *this;
}

void
member_declarator_bit_field_member::update_node_list()
{
	clear();
	if(identifier_) add(*identifier_);
	if(post_identifier_space_) add(*post_identifier_space_);
	add(global_nodes::colon);
	if(post_colon_space_) add(*post_colon_space_);
	add(conditional_expression_);
}

}}} //namespace scalpel::cpp::syntax_nodes
