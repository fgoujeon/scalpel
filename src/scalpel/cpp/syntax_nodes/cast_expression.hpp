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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP

#include "type_id.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class unary_expression;

/**
cast_expression
	= !(cast_expression_first_part_seq >> !s) >> unary_expression
;
cast_expression_first_part_seq
	= cast_expression_first_part % !s
;
cast_expression_first_part
	= '(' >> !s >> type_id >> !s >> ')'
;
*/

typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		type_id,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>
	>
	cast_expression_first_part
;

typedef
	list_node
	<
		cast_expression_first_part
	>
	cast_expression_first_part_seq
;

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	cast_expression,
	(optional_node<cast_expression_first_part_seq>)
	(optional_node<space>)
	(unary_expression)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
