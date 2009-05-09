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

#include "member_declaration_member_declarator_list.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

member_declaration_member_declarator_list::member_declaration_member_declarator_list
(
	boost::optional<decl_specifier_seq>&& decl_specifier_seq_node,
	boost::optional<space>&& post_decl_specifier_seq_space_node,
	boost::optional<member_declarator_list>&& member_declarator_list_node,
	boost::optional<space>&& post_member_declarator_list_space_node
):
	decl_specifier_seq_(decl_specifier_seq_node),
	post_decl_specifier_seq_space_(post_decl_specifier_seq_space_node),
	member_declarator_list_(member_declarator_list_node),
	post_member_declarator_list_space_(post_member_declarator_list_space_node)
{
	update_node_list();
}

member_declaration_member_declarator_list::member_declaration_member_declarator_list(const member_declaration_member_declarator_list& o):
	composite_node(),
	decl_specifier_seq_(o.decl_specifier_seq_),
	post_decl_specifier_seq_space_(o.post_decl_specifier_seq_space_),
	member_declarator_list_(o.member_declarator_list_),
	post_member_declarator_list_space_(o.post_member_declarator_list_space_)
{
	update_node_list();
}

member_declaration_member_declarator_list::member_declaration_member_declarator_list(member_declaration_member_declarator_list&& o):
	decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
	post_decl_specifier_seq_space_(std::move(o.post_decl_specifier_seq_space_)),
	member_declarator_list_(std::move(o.member_declarator_list_)),
	post_member_declarator_list_space_(std::move(o.post_member_declarator_list_space_))
{
	update_node_list();
}

const member_declaration_member_declarator_list&
member_declaration_member_declarator_list::operator=(const member_declaration_member_declarator_list& o)
{
	decl_specifier_seq_ = o.decl_specifier_seq_;
	post_decl_specifier_seq_space_ = o.post_decl_specifier_seq_space_;
	member_declarator_list_ = o.member_declarator_list_;
	post_member_declarator_list_space_ = o.post_member_declarator_list_space_;
	update_node_list();

	return *this;
}

void
member_declaration_member_declarator_list::update_node_list()
{
	clear();
	if(decl_specifier_seq_) add(*decl_specifier_seq_);
	if(post_decl_specifier_seq_space_) add(*post_decl_specifier_seq_space_);
	if(member_declarator_list_) add(*member_declarator_list_);
	if(post_member_declarator_list_space_) add(*post_member_declarator_list_space_);
	add(global_nodes::semicolon);
}

}}} //namespace scalpel::cpp::syntax_nodes
