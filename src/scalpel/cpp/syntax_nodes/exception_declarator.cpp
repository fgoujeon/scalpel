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

#include "exception_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

exception_declarator::exception_declarator
(
	type_specifier_seq&& type_specifier_seq_node,
	boost::optional<space>&& post_type_specifier_seq_space_node,
	declarator&& declarator_node
):
	type_specifier_seq_(type_specifier_seq_node),
	post_type_specifier_seq_space_(post_type_specifier_seq_space_node),
	declarator_(declarator_node)
{
	update_node_list();
}

exception_declarator::exception_declarator(const exception_declarator& o):
	composite_node(),
	type_specifier_seq_(o.type_specifier_seq_),
	post_type_specifier_seq_space_(o.post_type_specifier_seq_space_),
	declarator_(o.declarator_)
{
	update_node_list();
}

exception_declarator::exception_declarator(exception_declarator&& o):
	composite_node(),
	type_specifier_seq_(std::move(o.type_specifier_seq_)),
	post_type_specifier_seq_space_(std::move(o.post_type_specifier_seq_space_)),
	declarator_(std::move(o.declarator_))
{
	update_node_list();
}

const exception_declarator&
exception_declarator::operator=(const exception_declarator& o)
{
	type_specifier_seq_ = o.type_specifier_seq_;
	post_type_specifier_seq_space_ = o.post_type_specifier_seq_space_;
	declarator_ = o.declarator_;

	update_node_list();

	return *this;
}

void
exception_declarator::update_node_list()
{
	clear();
	add(type_specifier_seq_);
	if(post_type_specifier_seq_space_) add(*post_type_specifier_seq_space_);
	add(declarator_);
}

}}} //namespace scalpel::cpp::syntax_nodes

