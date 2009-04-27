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

#include "exception_abstract_declarator.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

exception_abstract_declarator::exception_abstract_declarator
(
	type_specifier_seq&& type_specifier_seq_node,
	boost::optional<space>&& post_type_specifier_seq_space_node,
	abstract_declarator&& abstract_declarator_node
):
	type_specifier_seq_(type_specifier_seq_node),
	post_type_specifier_seq_space_(post_type_specifier_seq_space_node),
	abstract_declarator_(abstract_declarator_node)
{
	update_node_list();
}

exception_abstract_declarator::exception_abstract_declarator(const exception_abstract_declarator& o):
	composite_node(),
	type_specifier_seq_(o.type_specifier_seq_),
	post_type_specifier_seq_space_(o.post_type_specifier_seq_space_),
	abstract_declarator_(o.abstract_declarator_)
{
	update_node_list();
}

exception_abstract_declarator::exception_abstract_declarator(exception_abstract_declarator&& o):
	composite_node(),
	type_specifier_seq_(std::move(o.type_specifier_seq_)),
	post_type_specifier_seq_space_(std::move(o.post_type_specifier_seq_space_)),
	abstract_declarator_(std::move(o.abstract_declarator_))
{
	update_node_list();
}

const exception_abstract_declarator&
exception_abstract_declarator::operator=(const exception_abstract_declarator& o)
{
	type_specifier_seq_ = o.type_specifier_seq_;
	post_type_specifier_seq_space_ = o.post_type_specifier_seq_space_;
	abstract_declarator_ = o.abstract_declarator_;

	update_node_list();

	return *this;
}

void
exception_abstract_declarator::update_node_list()
{
	clear();
	add(type_specifier_seq_);
	if(post_type_specifier_seq_space_) add(*post_type_specifier_seq_space_);
	add(abstract_declarator_);
}

}}} //namespace socoa::cpp::syntax_nodes

