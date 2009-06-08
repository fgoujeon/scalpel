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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ARGUMENT_CONDITIONAL_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ARGUMENT_CONDITIONAL_EXPRESSION_HPP

#include "common.hpp"
#include "expressions.hpp"
#include "expression_fwd.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class template_argument_assignment_expression;

/**
\verbatim
template_argument_conditional_expression
	= template_argument_logical_or_expression, ["?", expression, ":", template_argument_assignment_expression]
;
\endverbatim
*/
typedef
	sequence_node
	<
		template_argument_logical_or_expression,
		optional_node<space>,
		optional_node<simple_text_node<str::question_mark>>,
		optional_node<space>,
		optional_node<expression>,
		optional_node<space>,
		optional_node<simple_text_node<str::colon>>,
		optional_node<space>,
		optional_node<template_argument_assignment_expression>
	>
	template_argument_conditional_expression_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		optional_node<simple_text_node<str::question_mark>>,
		optional_node<space>,
		optional_node<expression>,
		optional_node<space>,
		optional_node<simple_text_node<str::colon>>,
		optional_node<space>,
		optional_node<template_argument_assignment_expression>
	>
	template_argument_conditional_expression_tail_t
;

/**
\verbatim
template_argument_conditional_expression
	= template_argument_logical_or_expression, ["?", expression, ":", template_argument_assignment_expression]
;
\endverbatim
*/
class template_argument_conditional_expression: public composite_node
{
	public:
		typedef template_argument_conditional_expression_t type;
		typedef template_argument_logical_or_expression head_node_t;
		typedef template_argument_conditional_expression_tail_t tail_sequence_node_t;

		template_argument_conditional_expression
		(
			template_argument_logical_or_expression&& o1,
			optional_node<space>&& o2,
			optional_node<simple_text_node<str::question_mark>> o3,
			optional_node<space>&& o4,
			optional_node<expression>&& o5,
			optional_node<space>&& o6,
			optional_node<simple_text_node<str::colon>> o7,
			optional_node<space>&& o8,
			optional_node<template_argument_assignment_expression>&& o9
		);

		template_argument_conditional_expression
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		template_argument_conditional_expression(const template_argument_conditional_expression& o);

		template_argument_conditional_expression(template_argument_conditional_expression&& o);

		template_argument_conditional_expression(const type& o);

		~template_argument_conditional_expression();

		const template_argument_conditional_expression&
		operator=(const template_argument_conditional_expression& o);

	private:
		type* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
