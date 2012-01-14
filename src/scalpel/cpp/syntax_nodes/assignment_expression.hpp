/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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
#include "throw_expression.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"
#include "detail/macros/alternative_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/*
assignment_expression
	= assignment_assignment_expression
	| conditional_expression
	| throw_expression
;
assignment_assignment_expression
	= logical_or_expression >> assignment_operator >> assignment_expression
;
*/

class logical_or_expression;
class conditional_expression;
class assignment_expression;

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	assignment_assignment_expression,
	(logical_or_expression)
	(assignment_operator)
	(assignment_expression)
)

const logical_or_expression&
get_left_operand(const assignment_assignment_expression& o);

const assignment_operator&
get_operator(const assignment_assignment_expression& o);

const assignment_expression&
get_right_operand(const assignment_assignment_expression& o);

SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION
(
	assignment_expression,
	(assignment_assignment_expression)
	(conditional_expression)
	(throw_expression)
)



class template_argument_logical_or_expression;
class template_argument_conditional_expression;
class template_argument_assignment_expression;

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	template_argument_assignment_assignment_expression,
	(template_argument_logical_or_expression)
	(assignment_operator)
	(template_argument_assignment_expression)
)

SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION
(
	template_argument_assignment_expression,
	(template_argument_assignment_assignment_expression)
	(template_argument_conditional_expression)
	(throw_expression)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_declaration_undef.hpp"
#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

