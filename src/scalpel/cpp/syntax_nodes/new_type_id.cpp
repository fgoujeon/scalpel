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

#include "new_type_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

new_type_id::new_type_id
(
	type_specifier_seq&& type_specifier_seq_node,
	boost::optional<space>&& pre_new_declarator_space_node,
	boost::optional<new_declarator>&& new_declarator_node
):
	type_specifier_seq_(type_specifier_seq_node),
	pre_new_declarator_space_(pre_new_declarator_space_node),
	new_declarator_(new_declarator_node)
{
	update_node_list();
}

new_type_id::new_type_id(const new_type_id& o):
	composite_node(),
	type_specifier_seq_(o.type_specifier_seq_),
	pre_new_declarator_space_(o.pre_new_declarator_space_),
	new_declarator_(o.new_declarator_)
{
	update_node_list();
}

new_type_id::new_type_id(new_type_id&& o):
	composite_node(),
	type_specifier_seq_(std::move(o.type_specifier_seq_)),
	pre_new_declarator_space_(std::move(o.pre_new_declarator_space_)),
	new_declarator_(std::move(o.new_declarator_))
{
	update_node_list();
}

const new_type_id&
new_type_id::operator=(const new_type_id& o)
{
	type_specifier_seq_ = o.type_specifier_seq_;
	pre_new_declarator_space_ = o.pre_new_declarator_space_;
	new_declarator_ = o.new_declarator_;

	update_node_list();

	return *this;
}

void
new_type_id::update_node_list()
{
	clear();
	add(type_specifier_seq_);
	if(pre_new_declarator_space_) add(*pre_new_declarator_space_);
	if(new_declarator_) add(*new_declarator_);
}

}}} //namespace scalpel::cpp::syntax_nodes

