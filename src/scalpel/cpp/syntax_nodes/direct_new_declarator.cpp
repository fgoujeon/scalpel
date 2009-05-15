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

#include "direct_new_declarator.hpp"

#include "conditional_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

direct_new_declarator::direct_new_declarator
(
	boost::optional<space>&& post_first_opening_bracket_space_node,
	expression&& expression_node,
	boost::optional<space>&& post_expression_space_node,
	boost::optional<space>&& post_first_closing_bracket_space_node,
	boost::optional<space>&& post_second_opening_bracket_space_node,
	boost::optional<conditional_expression>&& conditional_expression_node,
	boost::optional<space>&& post_conditional_expression_space_node
):
	post_first_opening_bracket_space_(post_first_opening_bracket_space_node),
	expression_(expression_node),
	post_expression_space_(post_expression_space_node),
	post_first_closing_bracket_space_(post_first_closing_bracket_space_node),
	post_second_opening_bracket_space_(post_second_opening_bracket_space_node),
	conditional_expression_(conditional_expression_node),
	post_conditional_expression_space_(post_conditional_expression_space_node)
{
	update_node_list();
}

direct_new_declarator::direct_new_declarator(const direct_new_declarator& o):
	composite_node(),
	post_first_opening_bracket_space_(o.post_first_opening_bracket_space_),
	expression_(o.expression_),
	post_expression_space_(o.post_expression_space_),
	post_first_closing_bracket_space_(o.post_first_closing_bracket_space_),
	post_second_opening_bracket_space_(o.post_second_opening_bracket_space_),
	conditional_expression_(o.conditional_expression_),
	post_conditional_expression_space_(o.post_conditional_expression_space_)
{
	update_node_list();
}

direct_new_declarator::direct_new_declarator(direct_new_declarator&& o):
	composite_node(),
	post_first_opening_bracket_space_(std::move(o.post_first_opening_bracket_space_)),
	expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_)),
	post_first_closing_bracket_space_(std::move(o.post_first_closing_bracket_space_)),
	post_second_opening_bracket_space_(std::move(o.post_second_opening_bracket_space_)),
	conditional_expression_(std::move(o.conditional_expression_)),
	post_conditional_expression_space_(std::move(o.post_conditional_expression_space_))
{
	update_node_list();
}

const direct_new_declarator&
direct_new_declarator::operator=(const direct_new_declarator& o)
{
	direct_new_declarator copy(o);
	std::swap(copy, *this);
	return *this;
}

void
direct_new_declarator::update_node_list()
{
	clear();
	add(common_nodes::opening_square_bracket);
	if(post_first_opening_bracket_space_) add(*post_first_opening_bracket_space_);
	add(expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(common_nodes::closing_square_bracket);
	if(conditional_expression_)
	{
		if(post_first_closing_bracket_space_) add(*post_first_closing_bracket_space_);
		add(common_nodes::opening_square_bracket);
		if(post_second_opening_bracket_space_) add(*post_second_opening_bracket_space_);
		add(*conditional_expression_);
		if(post_conditional_expression_space_) add(*post_conditional_expression_space_);
		add(common_nodes::closing_square_bracket);
	}
}

}}} //namespace scalpel::cpp::syntax_nodes

