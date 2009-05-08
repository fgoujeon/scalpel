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

#include "conversion_function_id.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

conversion_function_id::conversion_function_id
(
	boost::optional<space>&& post_operator_keyword_space_node,
	type_specifier_seq&& type_specifier_seq_node,
	boost::optional<space>&& pre_ptr_operator_seq_space_node,
	boost::optional<ptr_operator_seq>&& ptr_operator_seq_node
):
	post_operator_keyword_space_(post_operator_keyword_space_node),
	type_specifier_seq_(type_specifier_seq_node),
	pre_ptr_operator_seq_space_(pre_ptr_operator_seq_space_node),
	ptr_operator_seq_(ptr_operator_seq_node)
{
	update_node_list();
}

conversion_function_id::conversion_function_id(const conversion_function_id& o):
	composite_node(),
	post_operator_keyword_space_(o.post_operator_keyword_space_),
	type_specifier_seq_(o.type_specifier_seq_),
	pre_ptr_operator_seq_space_(o.pre_ptr_operator_seq_space_),
	ptr_operator_seq_(o.ptr_operator_seq_)
{
	update_node_list();
}

conversion_function_id::conversion_function_id(conversion_function_id&& o):
	post_operator_keyword_space_(std::move(o.post_operator_keyword_space_)),
	type_specifier_seq_(std::move(o.type_specifier_seq_)),
	pre_ptr_operator_seq_space_(std::move(o.pre_ptr_operator_seq_space_)),
	ptr_operator_seq_(std::move(o.ptr_operator_seq_))
{
	update_node_list();
}

const conversion_function_id&
conversion_function_id::operator=(const conversion_function_id& o)
{
	post_operator_keyword_space_ = o.post_operator_keyword_space_;
	type_specifier_seq_ = o.type_specifier_seq_;
	pre_ptr_operator_seq_space_ = o.pre_ptr_operator_seq_space_;
	ptr_operator_seq_ = o.ptr_operator_seq_;

	update_node_list();

	return *this;
}

void
conversion_function_id::update_node_list()
{
	clear();
	add(global_nodes::operator_keyword);
	if(post_operator_keyword_space_) add(*post_operator_keyword_space_);
	add(type_specifier_seq_);
	if(pre_ptr_operator_seq_space_) add(*pre_ptr_operator_seq_space_);
	if(ptr_operator_seq_) add(*ptr_operator_seq_);
}

}}} //namespace socoa::cpp::syntax_nodes

