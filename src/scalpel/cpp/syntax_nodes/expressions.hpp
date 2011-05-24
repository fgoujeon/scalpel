/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXPRESSIONS_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXPRESSIONS_HPP

#include "cast_expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

//primary expressions
typedef
	list_node<cast_expression>
	pm_ptr_expression
;

typedef
	list_node<pm_ptr_expression>
	pm_ref_expression
;

typedef
	list_node<pm_ref_expression>
	modulo_expression
;

typedef
	list_node<modulo_expression>
	divisive_expression
;

typedef
	list_node<divisive_expression>
	multiplicative_expression
;

typedef
	list_node<multiplicative_expression>
	subtractive_expression
;

typedef
	list_node<subtractive_expression>
	additive_expression
;

typedef
	list_node<additive_expression>
	left_shift_expression
;

typedef
	list_node<left_shift_expression>
	right_shift_expression
;

typedef
	list_node<right_shift_expression>
	less_than_or_equal_to_expression
;

typedef
	list_node<less_than_or_equal_to_expression>
	less_than_expression
;

typedef
	list_node<less_than_expression>
	greater_than_or_equal_to_expression
;

typedef
	list_node<greater_than_or_equal_to_expression>
	greater_than_expression
;

typedef
	list_node<greater_than_expression>
	inequality_expression
;

typedef
	list_node<inequality_expression>
	equality_expression
;

typedef
	list_node<equality_expression>
	and_expression
;

typedef
	list_node<and_expression>
	exclusive_or_expression
;

typedef
	list_node<exclusive_or_expression>
	inclusive_or_expression
;

typedef
	list_node<inclusive_or_expression>
	logical_and_expression
;

typedef
	list_node<logical_and_expression>
	logical_or_expression_t
;
struct logical_or_expression: public logical_or_expression_t
{
	logical_or_expression()
	{
	}

	logical_or_expression(const logical_or_expression& o):
		logical_or_expression_t(o)
	{
	}

	logical_or_expression(logical_or_expression&& o):
		logical_or_expression_t(o)
	{
	}
};



//round bracketed expressions
typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		right_shift_expression,
		predefined_text_node<str::closing_round_bracket>
	>
	round_bracketed_right_shift_expression
;

typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		greater_than_expression,
		predefined_text_node<str::closing_round_bracket>
	>
	round_bracketed_greater_than_expression
;



//same expressions used as template arguments
typedef
	alternative_node
	<
		round_bracketed_right_shift_expression,
		left_shift_expression
	>
	template_argument_right_shift_expression
;

typedef
	list_node<template_argument_right_shift_expression>
	template_argument_less_than_or_equal_to_expression
;

typedef
	list_node<template_argument_less_than_or_equal_to_expression>
	template_argument_less_than_expression
;

typedef
	list_node<template_argument_less_than_expression>
	template_argument_greater_than_or_equal_to_expression
;

typedef
	alternative_node
	<
		round_bracketed_greater_than_expression,
		template_argument_greater_than_or_equal_to_expression
	>
	template_argument_greater_than_expression
;

typedef
	list_node<template_argument_greater_than_expression>
	template_argument_inequality_expression
;

typedef
	list_node<template_argument_inequality_expression>
	template_argument_equality_expression
;

typedef
	list_node<template_argument_equality_expression>
	template_argument_and_expression
;

typedef
	list_node<template_argument_and_expression>
	template_argument_exclusive_or_expression
;

typedef
	list_node<template_argument_exclusive_or_expression>
	template_argument_inclusive_or_expression
;

typedef
	list_node<template_argument_inclusive_or_expression>
	template_argument_logical_and_expression
;

typedef
	list_node<template_argument_logical_and_expression>
	template_argument_logical_or_expression
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif

