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

#include "conditional_expression.hpp"

#include "expressions.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

conditional_expression::conditional_expression
(
	logical_or_expression&& logical_or_expression_node
):
	logical_or_expression_(new logical_or_expression(logical_or_expression_node))
{
	update_node_list();
}

conditional_expression::conditional_expression(const conditional_expression& o):
	composite_node(),
	logical_or_expression_(new logical_or_expression(*o.logical_or_expression_))
{
	update_node_list();
}

conditional_expression::conditional_expression(conditional_expression&& o):
	composite_node(),
	logical_or_expression_(o.logical_or_expression_)
{
	o.logical_or_expression_ = 0;
	update_node_list();
}

conditional_expression::~conditional_expression()
{
	delete logical_or_expression_;
}

const conditional_expression&
conditional_expression::operator=(const conditional_expression& o)
{
	conditional_expression copy(o);
	std::swap(copy, *this);
	return *this;
}

void
conditional_expression::update_node_list()
{
	clear();
	add(*logical_or_expression_);
}

}}} //namespace scalpel::cpp::syntax_nodes

