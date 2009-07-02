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

#include "expressions.hpp"
#include "expression.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

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
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	template_argument_conditional_expression,
	(template_argument_logical_or_expression)
	(optional_node<space>)
	(optional_node<predefined_text_node<str::question_mark>>)
	(optional_node<space>)
	(optional_node<expression>)
	(optional_node<space>)
	(optional_node<predefined_text_node<str::colon>>)
	(optional_node<space>)
	(optional_node<template_argument_assignment_expression>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
