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

#include "square_bracketed_expression.hpp"

#include "expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

square_bracketed_expression::square_bracketed_expression
(
	boost::optional<space>&& pre_expression_space_node,
	expression&& expression_node,
	boost::optional<space>&& post_expression_space_node
):
	pre_expression_space_(pre_expression_space_node),
	expression_(new expression(expression_node)),
	post_expression_space_(post_expression_space_node)
{
	update_node_list();
}

square_bracketed_expression::square_bracketed_expression(const square_bracketed_expression& o):
	composite_node(),
	pre_expression_space_(o.pre_expression_space_),
	expression_(new expression(*o.expression_)),
	post_expression_space_(o.post_expression_space_)
{
	update_node_list();
}

square_bracketed_expression::square_bracketed_expression(square_bracketed_expression&& o):
	composite_node(),
	pre_expression_space_(std::move(o.pre_expression_space_)),
	expression_(o.expression_),
	post_expression_space_(std::move(o.post_expression_space_))
{
	o.expression_ = 0;
	update_node_list();
}

square_bracketed_expression::~square_bracketed_expression()
{
	delete expression_;
}

const square_bracketed_expression&
square_bracketed_expression::operator=(const square_bracketed_expression& o)
{
	pre_expression_space_ = o.pre_expression_space_;
	delete expression_;
	expression_ = new expression(*o.expression_);
	post_expression_space_ = o.post_expression_space_;

	update_node_list();

	return *this;
}

void
square_bracketed_expression::update_node_list()
{
	clear();
	add(global_nodes::opening_square_bracket);
	if(pre_expression_space_) add(*pre_expression_space_);
	add(*expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(global_nodes::closing_square_bracket);
}

}}} //namespace scalpel::cpp::syntax_nodes

