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

#include "member_declaration_member_declarator_list.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

member_declaration_member_declarator_list::member_declaration_member_declarator_list
(
    boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
    boost::optional<member_declarator_list>&& a_member_declarator_list
):
    decl_specifier_seq_(a_decl_specifier_seq),
    member_declarator_list_(a_member_declarator_list)
{
	update_node_list();
}

member_declaration_member_declarator_list::member_declaration_member_declarator_list(const member_declaration_member_declarator_list& o):
	composite_node(),
    decl_specifier_seq_(o.decl_specifier_seq_),
    member_declarator_list_(o.member_declarator_list_)
{
	update_node_list();
}

member_declaration_member_declarator_list::member_declaration_member_declarator_list(member_declaration_member_declarator_list&& o):
    decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
    member_declarator_list_(std::move(o.member_declarator_list_))
{
	update_node_list();
}

const member_declaration_member_declarator_list&
member_declaration_member_declarator_list::operator=(const member_declaration_member_declarator_list& o)
{
    decl_specifier_seq_ = o.decl_specifier_seq_;
    member_declarator_list_ = o.member_declarator_list_;
	update_node_list();

	return *this;
}

void
member_declaration_member_declarator_list::update_node_list()
{
	clear();
	if(decl_specifier_seq_) add(*decl_specifier_seq_);
	if(member_declarator_list_) add(*member_declarator_list_);
}

}}} //namespace socoa::cpp::syntax_nodes
