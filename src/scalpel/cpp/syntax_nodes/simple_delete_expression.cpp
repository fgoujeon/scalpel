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

#include "simple_delete_expression.hpp"

#include "common_nodes.hpp"
#include "cast_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

simple_delete_expression::simple_delete_expression
(
	bool leading_double_colon,
	boost::optional<space>&& post_double_colon_space_node,
	boost::optional<space>&& post_delete_keyword_space_node,
	cast_expression&& cast_expression_node
):
	leading_double_colon_(leading_double_colon),
	post_double_colon_space_(post_double_colon_space_node),
	post_delete_keyword_space_(post_delete_keyword_space_node),
	cast_expression_(new cast_expression(cast_expression_node))
{
	update_node_list();
}

simple_delete_expression::simple_delete_expression(const simple_delete_expression& o):
	composite_node(),
	leading_double_colon_(o.leading_double_colon_),
	post_double_colon_space_(o.post_double_colon_space_),
	post_delete_keyword_space_(o.post_delete_keyword_space_),
	cast_expression_(new cast_expression(*o.cast_expression_))
{
	update_node_list();
}

simple_delete_expression::simple_delete_expression(simple_delete_expression&& o):
	composite_node(),
	leading_double_colon_(std::move(o.leading_double_colon_)),
	post_double_colon_space_(std::move(o.post_double_colon_space_)),
	post_delete_keyword_space_(std::move(o.post_delete_keyword_space_)),
	cast_expression_(std::move(o.cast_expression_))
{
	update_node_list();
}

const simple_delete_expression&
simple_delete_expression::operator=(const simple_delete_expression& o)
{
	simple_delete_expression copy(o);
	std::swap(copy, *this);
	return *this;
}

void
simple_delete_expression::update_node_list()
{
	clear();
	if(leading_double_colon_) add(global_nodes::double_colon);
	if(post_double_colon_space_) add(*post_double_colon_space_);
	add(global_nodes::delete_keyword);
	if(post_delete_keyword_space_) add(*post_delete_keyword_space_);
	add(*cast_expression_);
}

}}} //namespace scalpel::cpp::syntax_nodes

