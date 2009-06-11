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

#include "assignment_expression.hpp"

#include "expressions.hpp"
#include "conditional_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

assignment_expression::assignment_expression
(
	optional_node<first_part_seq>&& o1,
	optional_node<space>&& o2,
	last_part&& o3
):
	impl_(new type(o1, o2, o3))
{
	add(*impl_);
}

assignment_expression::assignment_expression
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new type(head, tail))
{
	add(*impl_);
}

assignment_expression::assignment_expression(const assignment_expression& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

assignment_expression::assignment_expression(assignment_expression&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

assignment_expression::~assignment_expression()
{
}

const assignment_expression&
assignment_expression::operator=(const assignment_expression& o)
{
	*impl_ = *o.impl_;
	return *this;
}



assignment_expression::first_part::first_part
(
	logical_or_expression&& o0,
	optional_node<space>&& o1,
	assignment_operator&& o2
):
	impl_
	(
		new type
		(
			o0,
			o1,
			o2
		)
	)
{
	add(*impl_);
}

assignment_expression::first_part::first_part
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_
	(
		new type
		(
			head,
			tail
		)
	)
{
	add(*impl_);
}

assignment_expression::first_part::first_part(const first_part& o):
	composite_node(),
	impl_(new type(*o.impl_))
{
	add(*impl_);
}

assignment_expression::first_part::first_part(first_part&& o):
	composite_node(),
	impl_(std::move(o.impl_))
{
	add(*impl_);
}

assignment_expression::first_part::~first_part()
{
}

const assignment_expression::first_part&
assignment_expression::first_part::operator=(const first_part& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

