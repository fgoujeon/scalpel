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

#include "simple_declaration.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

simple_declaration::simple_declaration
(
    boost::optional<decl_specifier_seq>&& a_decl_specifier_seq,
	boost::optional<space>&& post_decl_specifier_seq_space_node,
    boost::optional<init_declarator_list>&& an_init_declarator_list,
	boost::optional<space>&& post_init_declarator_list_space_node
):
    decl_specifier_seq_(a_decl_specifier_seq),
	post_decl_specifier_seq_space_(post_decl_specifier_seq_space_node),
    init_declarator_list_(an_init_declarator_list),
	post_init_declarator_list_space_(post_init_declarator_list_space_node)
{
	update_node_list();
}

simple_declaration::simple_declaration(const simple_declaration& o):
	composite_node(),
    decl_specifier_seq_(o.decl_specifier_seq_),
	post_decl_specifier_seq_space_(o.post_decl_specifier_seq_space_),
    init_declarator_list_(o.init_declarator_list_),
	post_init_declarator_list_space_(o.post_init_declarator_list_space_)
{
	update_node_list();
}

simple_declaration::simple_declaration(simple_declaration&& o):
    decl_specifier_seq_(std::move(o.decl_specifier_seq_)),
	post_decl_specifier_seq_space_(std::move(o.post_decl_specifier_seq_space_)),
    init_declarator_list_(std::move(o.init_declarator_list_)),
	post_init_declarator_list_space_(std::move(o.post_init_declarator_list_space_))
{
	update_node_list();
}

const simple_declaration&
simple_declaration::operator=(const simple_declaration& o)
{
    decl_specifier_seq_ = o.decl_specifier_seq_;
	post_decl_specifier_seq_space_ = o.post_decl_specifier_seq_space_;
    init_declarator_list_ = o.init_declarator_list_;
	post_init_declarator_list_space_ = o.post_init_declarator_list_space_;

	update_node_list();

	return *this;
}

void
simple_declaration::update_node_list()
{
	clear();
	if(decl_specifier_seq_) add(*decl_specifier_seq_);
	if(post_decl_specifier_seq_space_) add(*post_decl_specifier_seq_space_);
	if(init_declarator_list_) add(*init_declarator_list_);
	if(post_init_declarator_list_space_) add(*post_init_declarator_list_space_);
	add(semicolon);
}

}}} //namespace socoa::cpp::syntax_nodes
