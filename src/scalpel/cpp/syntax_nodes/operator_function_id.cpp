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

#include "operator_function_id.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

operator_function_id::operator_function_id
(
	boost::optional<space>&& post_operator_keyword_space_node,
	operator_&& operator_node
):
	post_operator_keyword_space_(post_operator_keyword_space_node),
	operator__(operator_node)
{
	update_node_list();
}

operator_function_id::operator_function_id(const operator_function_id& o):
	composite_node(),
	post_operator_keyword_space_(o.post_operator_keyword_space_),
	operator__(o.operator__)
{
	update_node_list();
}

operator_function_id::operator_function_id(operator_function_id&& o):
	post_operator_keyword_space_(std::move(o.post_operator_keyword_space_)),
	operator__(std::move(o.operator__))
{
	update_node_list();
}

const operator_function_id&
operator_function_id::operator=(const operator_function_id& o)
{
	post_operator_keyword_space_ = o.post_operator_keyword_space_;
	operator__ = o.operator__;

	update_node_list();

	return *this;
}

void
operator_function_id::update_node_list()
{
	clear();
	add(common_nodes::operator_keyword);
	if(post_operator_keyword_space_) add(*post_operator_keyword_space_);
	add(operator__);
}

}}} //namespace scalpel::cpp::syntax_nodes

