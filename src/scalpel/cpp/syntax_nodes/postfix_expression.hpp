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

#ifndef SCALPEL_CPP_SYNTAX_NODES_POSTFIX_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_POSTFIX_EXPRESSION_HPP

#include "primary_expression.hpp"
#include "simple_type_specifier_postfix_expression.hpp"
#include "typename_expression.hpp"
#include "template_typename_expression.hpp"
#include "dynamic_cast_expression.hpp"
#include "static_cast_expression.hpp"
#include "reinterpret_cast_expression.hpp"
#include "const_cast_expression.hpp"
#include "typeid_expression.hpp"
#include "type_id_typeid_expression.hpp"
#include "dot_id_expression.hpp"
#include "arrow_id_expression.hpp"
#include "dot_pseudo_destructor_name.hpp"
#include "arrow_pseudo_destructor_name.hpp"
#include "predefined_text_node.hpp"
#include "expression.hpp"
#include "square_bracketed_expression.hpp"
#include "round_bracketed_optional_expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
postfix_expression
	= postfix_expression::first_part, [postfix_expression::last_part_seq]
;
\endverbatim
*/
typedef
	alternative_node
	<
		primary_expression,
		simple_type_specifier_postfix_expression,
		typename_expression,
		template_typename_expression,
		dynamic_cast_expression,
		static_cast_expression,
		reinterpret_cast_expression,
		const_cast_expression,
		typeid_expression,
		type_id_typeid_expression
	>
	postfix_expression_first_part
;

typedef
	alternative_node
	<
		square_bracketed_expression,
		round_bracketed_optional_expression,
		dot_id_expression,
		arrow_id_expression,
		dot_pseudo_destructor_name,
		arrow_pseudo_destructor_name,
		predefined_text_node<str::double_plus>,
		predefined_text_node<str::double_minus>
	>
	postfix_expression_last_part
;

typedef
	list_node<postfix_expression_last_part>
	postfix_expression_last_part_seq
;

typedef
	sequence_node
	<
		postfix_expression_first_part,
		optional_node<space>,
		optional_node<postfix_expression_last_part_seq>
	>
	postfix_expression_t
;

struct postfix_expression: public postfix_expression_t
{
	postfix_expression
	(
		postfix_expression_first_part&& o0,
		optional_node<space>&& o1,
		optional_node<postfix_expression_last_part_seq>&& o2
	):
		postfix_expression_t(o0, o1, o2)
	{
	}

	postfix_expression
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		postfix_expression_t(head, tail)
	{
	}

	postfix_expression(const postfix_expression& o):
		postfix_expression_t(o)
	{
	}

	postfix_expression(postfix_expression&& o):
		postfix_expression_t(o)
	{
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
