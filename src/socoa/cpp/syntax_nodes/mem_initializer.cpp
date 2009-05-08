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

#include "mem_initializer.hpp"

#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

mem_initializer::mem_initializer
(
	mem_initializer_id&& mem_initializer_id_node,
	boost::optional<space>&& post_mem_initializer_id_space_node,
	boost::optional<space>&& post_opening_bracket_space_node,
	boost::optional<expression_list>&& expression_list_node,
	boost::optional<space>&& post_expression_list_space_node
):
	mem_initializer_id_(mem_initializer_id_node),
	post_mem_initializer_id_space_(post_mem_initializer_id_space_node),
	post_opening_bracket_space_(post_opening_bracket_space_node),
	expression_list_(expression_list_node),
	post_expression_list_space_(post_expression_list_space_node)
{
	update_node_list();
}

mem_initializer::mem_initializer(const mem_initializer& o):
	composite_node(),
	mem_initializer_id_(o.mem_initializer_id_),
	post_mem_initializer_id_space_(o.post_mem_initializer_id_space_),
	post_opening_bracket_space_(o.post_opening_bracket_space_),
	expression_list_(o.expression_list_),
	post_expression_list_space_(o.post_expression_list_space_)
{
	update_node_list();
}

mem_initializer::mem_initializer(mem_initializer&& o):
	mem_initializer_id_(std::move(o.mem_initializer_id_)),
	post_mem_initializer_id_space_(std::move(o.post_mem_initializer_id_space_)),
	post_opening_bracket_space_(std::move(o.post_opening_bracket_space_)),
	expression_list_(std::move(o.expression_list_)),
	post_expression_list_space_(std::move(o.post_expression_list_space_))
{
	update_node_list();
}

const mem_initializer&
mem_initializer::operator=(const mem_initializer& o)
{
	mem_initializer_id_ = o.mem_initializer_id_;
	post_mem_initializer_id_space_ = o.post_mem_initializer_id_space_;
	post_opening_bracket_space_ = o.post_opening_bracket_space_;
	expression_list_ = o.expression_list_;
	post_expression_list_space_ = o.post_expression_list_space_;

	update_node_list();

	return *this;
}

void
mem_initializer::update_node_list()
{
	clear();
	add(mem_initializer_id_);
	if(post_mem_initializer_id_space_) add(*post_mem_initializer_id_space_);
	add(global_nodes::opening_bracket);
	if(post_opening_bracket_space_) add(*post_opening_bracket_space_);
	if(expression_list_) add(*expression_list_);
	if(post_expression_list_space_) add(*post_expression_list_space_);
	add(global_nodes::closing_bracket);
}

}}} //namespace socoa::cpp::syntax_nodes
