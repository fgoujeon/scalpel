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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION_HPP

#include "common.hpp"
#include "assignment_operator.hpp"
#include "template_argument_conditional_expression.hpp"
#include "expressions.hpp"
#include "throw_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
template_argument_assignment_expression
	= [template_argument_assignment_expression_first_part_seq], template_argument_assignment_expression_last_part
;
template_argument_assignment_expression::first_part_seq
	= {template_argument_assignment_expression::first_part}
;
template_argument_assignment_expression::first_part
	= template_argument_logical_or_expression, assignment_operator
;
template_argument_assignment_expression_last_part
	= conditional_expression
	| throw_expression
;
\endverbatim
*/
typedef
	sequence_node
	<
		template_argument_logical_or_expression,
		optional_node<space>,
		assignment_operator
	>
	template_argument_assignment_expression_first_part
;

typedef
	list_node
	<
		template_argument_assignment_expression_first_part
	>
	template_argument_assignment_expression_first_part_seq
;

typedef
	alternative_node
	<
		template_argument_conditional_expression,
		throw_expression
	>
	template_argument_assignment_expression_last_part
;

typedef
	sequence_node
	<
		optional_node<template_argument_assignment_expression_first_part_seq>,
		optional_node<space>,
		template_argument_assignment_expression_last_part
	>
	template_argument_assignment_expression_t
;

struct template_argument_assignment_expression: public template_argument_assignment_expression_t
{
	typedef template_argument_assignment_expression_t type;
	typedef type::head_node_t head_node_t;
	typedef type::tail_sequence_node_t tail_sequence_node_t;

	typedef template_argument_assignment_expression_first_part first_part;
	typedef template_argument_assignment_expression_first_part_seq first_part_seq;
	typedef template_argument_assignment_expression_last_part last_part;

	template_argument_assignment_expression
	(
		optional_node<template_argument_assignment_expression_first_part_seq>&& o1,
		optional_node<space>&& o2,
		template_argument_assignment_expression_last_part&& o3
	):
		type(o1, o2, o3)
	{
	}

	template_argument_assignment_expression
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		type(head, tail)
	{
	}

	template_argument_assignment_expression(const template_argument_assignment_expression& o):
		type(o)
	{
	}

	template_argument_assignment_expression(template_argument_assignment_expression&& o):
		type(o)
	{
	}

	using type::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
