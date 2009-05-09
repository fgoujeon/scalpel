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

#include "unary_operator_unary_expression.hpp"

#include "cast_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

unary_operator_unary_expression::unary_operator_unary_expression
(
	unary_operator&& unary_operator_node,
	boost::optional<space>&& space_node,
	cast_expression&& cast_expression_node
):
	unary_operator_(unary_operator_node),
	space_(space_node),
	cast_expression_(new cast_expression(cast_expression_node))
{
	update_node_list();
}

unary_operator_unary_expression::unary_operator_unary_expression(const unary_operator_unary_expression& o):
	composite_node(),
	unary_operator_(o.unary_operator_),
	space_(o.space_),
	cast_expression_(new cast_expression(*o.cast_expression_))
{
	update_node_list();
}

unary_operator_unary_expression::unary_operator_unary_expression(unary_operator_unary_expression&& o):
	composite_node(),
	unary_operator_(std::move(o.unary_operator_)),
	space_(std::move(o.space_)),
	cast_expression_(std::move(o.cast_expression_))
{
	update_node_list();
}

const unary_operator_unary_expression&
unary_operator_unary_expression::operator=(const unary_operator_unary_expression& o)
{
	unary_operator_ = o.unary_operator_;
	space_ = o.space_;
	cast_expression_ = std::move(std::unique_ptr<cast_expression>(new cast_expression(*o.cast_expression_)));

	update_node_list();

	return *this;
}

void
unary_operator_unary_expression::update_node_list()
{
	clear();
	add(unary_operator_);
	if(space_) add(*space_);
	add(*cast_expression_);
}

}}} //namespace scalpel::cpp::syntax_nodes

