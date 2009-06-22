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

#include "template_argument_conditional_expression.hpp"

#include "template_argument_assignment_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template_argument_conditional_expression::template_argument_conditional_expression
(
	template_argument_logical_or_expression&& o1,
	optional_node<space>&& o2,
	optional_node<predefined_text_node<str::question_mark>> o3,
	optional_node<space>&& o4,
	optional_node<expression>&& o5,
	optional_node<space>&& o6,
	optional_node<predefined_text_node<str::colon>> o7,
	optional_node<space>&& o8,
	optional_node<template_argument_assignment_expression>&& o9
):
	impl_(new type(o1, o2, o3, o4, o5, o6, o7, o8, o9))
{
	add(*impl_);
}

template_argument_conditional_expression::template_argument_conditional_expression
(
	head_node_t&& head,
	tail_sequence_node_t&& tail
):
	impl_(new type(head, tail))
{
}

template_argument_conditional_expression::template_argument_conditional_expression(const template_argument_conditional_expression& o):
	composite_node(),
	impl_
	(
		new type(*o.impl_)
	)
{
	add(*impl_);
}

template_argument_conditional_expression::template_argument_conditional_expression(template_argument_conditional_expression&& o):
	composite_node(),
	impl_(o.impl_)
{
	o.impl_ = 0;
	add(*impl_);
}

template_argument_conditional_expression::template_argument_conditional_expression(const type& o):
	composite_node(),
	impl_
	(
		new type(o)
	)
{
	add(*impl_);
}

template_argument_conditional_expression::~template_argument_conditional_expression()
{
	delete impl_;
}

const template_argument_conditional_expression&
template_argument_conditional_expression::operator=(const template_argument_conditional_expression& o)
{
	*impl_ = *o.impl_;
	return *this;
}

}}} //namespace scalpel::cpp::syntax_nodes

