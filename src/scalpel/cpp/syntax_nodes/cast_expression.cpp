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

#include "cast_expression.hpp"

#include "unary_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

cast_expression::cast_expression
(
	optional_node<cast_expression_first_part_seq>&& o0,
	optional_node<space>&& o1,
	unary_expression&& o2
):
	impl_
	(
		new type
		(
			std::move(o0),
			std::move(o1),
			std::move(o2)
		)
	)
{
	add(*impl_);
}

cast_expression::cast_expression
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_
	(
		new type
		(
			std::move(head),
			std::move(tail)
		)
	)
{
	add(*impl_);
}

cast_expression::cast_expression(const cast_expression& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

cast_expression::cast_expression(cast_expression&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

cast_expression::~cast_expression()
{
}

const cast_expression&
cast_expression::operator=(const cast_expression& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

