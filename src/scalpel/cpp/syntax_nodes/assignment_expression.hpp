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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ASSIGNMENT_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ASSIGNMENT_EXPRESSION_HPP

#include "assignment_operator.hpp"
#include "conditional_expression_fwd.hpp"
#include "throw_expression.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
assignment_expression
	= [assignment_expression_first_part_seq], assignment_expression_last_part
;
assignment_expression::first_part_seq
	= {assignment_expression::first_part}
;
assignment_expression::first_part
	= logical_or_expression, assignment_operator
;
assignment_expression_last_part
	= conditional_expression
	| throw_expression
;
\endverbatim
*/

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	assignment_expression_first_part,
	(logical_or_expression)
	(optional_node<space>)
	(assignment_operator)
)

typedef
	list_node<assignment_expression_first_part>
	assignment_expression_first_part_seq
;

typedef
	alternative_node
	<
		conditional_expression,
		throw_expression
	>
	assignment_expression_last_part
;

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	assignment_expression,
	(optional_node<assignment_expression_first_part_seq>)
	(optional_node<space>)
	(assignment_expression_last_part)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
