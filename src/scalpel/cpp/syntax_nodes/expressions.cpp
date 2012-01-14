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

#include "expressions.hpp"
#include "detail/macros/sequence_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	pm_expression,
	(cast_expression)
	(optional_node<pm_operator>)
	(optional_node<pm_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	multiplicative_expression,
	(pm_expression)
	(optional_node<multiplicative_operator>)
	(optional_node<multiplicative_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	additive_expression,
	(multiplicative_expression)
	(optional_node<additive_operator>)
	(optional_node<additive_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	relational_expression,
	(shift_expression)
	(optional_node<relational_operator>)
	(optional_node<relational_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	equality_expression,
	(relational_expression)
	(optional_node<equality_operator>)
	(optional_node<equality_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	and_expression,
	(equality_expression)
	(optional_node<and_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	exclusive_or_expression,
	(and_expression)
	(optional_node<exclusive_or_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	inclusive_or_expression,
	(exclusive_or_expression)
	(optional_node<inclusive_or_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	logical_and_expression,
	(inclusive_or_expression)
	(optional_node<logical_and_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	logical_or_expression,
	(logical_and_expression)
	(optional_node<logical_or_expression>)
)




SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	shift_expression,
	(additive_expression)
	(optional_node<shift_operator>)
	(optional_node<shift_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_shift_expression,
	(additive_expression)
	(optional_node<template_argument_shift_operator>)
	(optional_node<template_argument_shift_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_relational_expression,
	(template_argument_shift_expression)
	(optional_node<template_argument_relational_operator>)
	(optional_node<template_argument_relational_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_equality_expression,
	(template_argument_relational_expression)
	(optional_node<equality_operator>)
	(optional_node<template_argument_equality_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_and_expression,
	(template_argument_equality_expression)
	(optional_node<template_argument_and_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_exclusive_or_expression,
	(template_argument_and_expression)
	(optional_node<template_argument_exclusive_or_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_inclusive_or_expression,
	(template_argument_exclusive_or_expression)
	(optional_node<template_argument_inclusive_or_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_logical_and_expression,
	(template_argument_inclusive_or_expression)
	(optional_node<template_argument_logical_and_expression>)
)

SCALPEL_SEQUENCE_NODE_PIMPL_DEFINITION
(
	template_argument_logical_or_expression,
	(template_argument_logical_and_expression)
	(optional_node<template_argument_logical_or_expression>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_definition_undef.hpp"

