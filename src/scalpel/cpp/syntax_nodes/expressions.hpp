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
#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

//primary expressions

typedef
	alternative_node
	<
		predefined_text_node<str::arrow_asterisk>,
		predefined_text_node<str::dot_asterisk>
	>
	pm_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	pm_expression,
	(cast_expression)
	(optional_node<pm_operator>)
	(optional_node<pm_expression>)
)

typedef
	alternative_node
	<
		predefined_text_node<str::asterisk>,
		predefined_text_node<str::slash>,
		predefined_text_node<str::percent>
	>
	multiplicative_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	multiplicative_expression,
	(pm_expression)
	(optional_node<multiplicative_operator>)
	(optional_node<multiplicative_expression>)
)

typedef
	alternative_node
	<
		predefined_text_node<str::plus>,
		predefined_text_node<str::minus>
	>
	additive_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	additive_expression,
	(multiplicative_expression)
	(optional_node<additive_operator>)
	(optional_node<additive_expression>)
)

typedef
	alternative_node
	<
		predefined_text_node<str::double_left_angle_bracket>,
		predefined_text_node<str::double_right_angle_bracket>
	>
	shift_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	shift_expression,
	(additive_expression)
	(optional_node<shift_operator>)
	(optional_node<shift_expression>)
)

typedef
	alternative_node
	<
		predefined_text_node<str::left_angle_bracket>,
		predefined_text_node<str::right_angle_bracket>,
		predefined_text_node<str::left_angle_bracket_equal>,
		predefined_text_node<str::right_angle_bracket_equal>
	>
	relational_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	relational_expression,
	(shift_expression)
	(optional_node<relational_operator>)
	(optional_node<relational_expression>)
)

typedef
	list_node<relational_expression>
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



//same expressions used as template arguments
typedef
	alternative_node
	<
		predefined_text_node<str::double_left_angle_bracket>
	>
	template_argument_shift_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	template_argument_shift_expression,
	(additive_expression)
	(optional_node<template_argument_shift_operator>)
	(optional_node<template_argument_shift_expression>)
)

typedef
	alternative_node
	<
		predefined_text_node<str::left_angle_bracket>,
		predefined_text_node<str::left_angle_bracket_equal>,
		predefined_text_node<str::right_angle_bracket_equal>
	>
	template_argument_relational_operator
;
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	template_argument_relational_expression,
	(template_argument_shift_expression)
	(optional_node<template_argument_relational_operator>)
	(optional_node<template_argument_relational_expression>)
)

typedef
	list_node<template_argument_relational_expression>
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

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

