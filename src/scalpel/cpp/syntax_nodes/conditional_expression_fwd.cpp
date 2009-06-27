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

#include "conditional_expression_fwd.hpp"

#include "expressions.hpp"
#include "expression.hpp"
#include "assignment_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

conditional_expression::conditional_expression
(
	logical_or_expression&& o1,
	optional_node<space>&& o2,
	optional_node<predefined_text_node<str::question_mark>> o3,
	optional_node<space>&& o4,
	optional_node<expression>&& o5,
	optional_node<space>&& o6,
	optional_node<predefined_text_node<str::colon>> o7,
	optional_node<space>&& o8,
	optional_node<assignment_expression>&& o9
):
	impl_(new type(o1, o2, o3, o4, o5, o6, o7, o8, o9))
{
}

conditional_expression::conditional_expression
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new type(head, tail))
{
}

conditional_expression::conditional_expression(const conditional_expression& o):
	impl_(new type(*o.impl_))
{
}

conditional_expression::conditional_expression(conditional_expression&& o):
	impl_(std::move(o.impl_))
{
}

conditional_expression::~conditional_expression()
{
}

const conditional_expression&
conditional_expression::operator=(const conditional_expression& o)
{
	*impl_ = *o.impl_;
	return *this;
}

node::child_const_iterator_range
conditional_expression::children() const
{
	return impl_->children();
}

const std::string
conditional_expression::value() const
{
	return impl_->value();
}

}}} //namespace scalpel::cpp::syntax_nodes

