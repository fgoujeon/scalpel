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

#include "expression_statement.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

expression_statement::expression_statement
(
	boost::optional<expression>&& expression_node,
	boost::optional<space>&& post_expression_space_node
):
	expression_(expression_node),
	post_expression_space_(post_expression_space_node)
{
	update_node_list();
}

expression_statement::expression_statement(const expression_statement& o):
	composite_node(),
	expression_(o.expression_),
	post_expression_space_(o.post_expression_space_)
{
	update_node_list();
}

expression_statement::expression_statement(expression_statement&& o):
	composite_node(),
	expression_(std::move(o.expression_)),
	post_expression_space_(std::move(o.post_expression_space_))
{
	update_node_list();
}

const expression_statement&
expression_statement::operator=(const expression_statement& o)
{
	expression_ = o.expression_;
	post_expression_space_ = o.post_expression_space_;

	update_node_list();

	return *this;
}

void
expression_statement::update_node_list()
{
	clear();

	if(expression_) add(*expression_);
	if(post_expression_space_) add(*post_expression_space_);
	add(global_nodes::semicolon);
}

}}} //namespace scalpel::cpp::syntax_nodes

