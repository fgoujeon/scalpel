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

#include "type_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

type_id::type_id
(
	type_specifier_seq&& type_specifier_seq_node,
	optional_node<space>&& pre_abstract_declarator_space_node,
	optional_node<abstract_declarator>&& abstract_declarator_node
):
	type_specifier_seq_(type_specifier_seq_node),
	pre_abstract_declarator_space_(pre_abstract_declarator_space_node),
	abstract_declarator_(abstract_declarator_node)
{
	update_node_list();
}

type_id::type_id(const type_id& o):
	composite_node(),
	type_specifier_seq_(o.type_specifier_seq_),
	pre_abstract_declarator_space_(o.pre_abstract_declarator_space_),
	abstract_declarator_(o.abstract_declarator_)
{
	update_node_list();
}

type_id::type_id(type_id&& o):
	composite_node(),
	type_specifier_seq_(std::move(o.type_specifier_seq_)),
	pre_abstract_declarator_space_(std::move(o.pre_abstract_declarator_space_)),
	abstract_declarator_(std::move(o.abstract_declarator_))
{
	update_node_list();
}

const type_id&
type_id::operator=(const type_id& o)
{
	type_specifier_seq_ = o.type_specifier_seq_;
	pre_abstract_declarator_space_ = o.pre_abstract_declarator_space_;
	abstract_declarator_ = o.abstract_declarator_;

	update_node_list();

	return *this;
}

void
type_id::update_node_list()
{
	clear();
	add(type_specifier_seq_);
	if(pre_abstract_declarator_space_) add(*pre_abstract_declarator_space_);
	if(abstract_declarator_) add(*abstract_declarator_);
}

}}} //namespace scalpel::cpp::syntax_nodes

