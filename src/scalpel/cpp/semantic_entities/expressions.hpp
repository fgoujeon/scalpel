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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATIONS_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATIONS_HPP

#include "unary_expression.hpp"
#include "binary_expression.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

enum class expression_tag
{
	PREFIX_INCREMENT_EXPRESSION,
	PREFIX_DECREMENT_EXPRESSION,
	POSTFIX_INCREMENT_EXPRESSION,
	POSTFIX_DECREMENT_EXPRESSION,
	INDIRECTION_EXPRESSION,
	POINTER_EXPRESSION,
	NEGATION_EXPRESSION,
	LOGICAL_NEGATION_EXPRESSION,
	COMPLEMENT_EXPRESSION,

	MULTIPLICATION,
	DIVISION,
	MODULO,
	ADDITION,
	SUBTRACTION,
	LEFT_SHIFT,
	RIGHT_SHIFT,
	LESS_THAN,
	LESS_THAN_OR_EQUAL_TO,
	GREATER_THAN,
	GREATER_THAN_OR_EQUAL_TO,
	EQUAL_TO,
	NOT_EQUAL_TO,
	BITWISE_AND,
	BITWISE_EXCLUSIVE_OR,
	BITWISE_INCLUSIVE_OR,
	LOGICAL_AND,
	LOGICAL_OR,

	ASSIGNMENT,
	MULTIPLICATION_ASSIGNMENT,
	DIVISION_ASSIGNMENT,
	MODULO_ASSIGNMENT,
	ADDITION_ASSIGNMENT,
	SUBTRACTION_ASSIGNMENT,
	LEFT_SHIFT_ASSIGNMENT,
	RIGHT_SHIFT_ASSIGNMENT,
	BITWISE_AND_ASSIGNMENT,
	BITWISE_EXCLUSIVE_OR_ASSIGNMENT,
	BITWISE_INCLUSIVE_OR_ASSIGNMENT
};

typedef
	unary_expression<static_cast<int>(expression_tag::PREFIX_INCREMENT_EXPRESSION)>
	prefix_increment_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::PREFIX_DECREMENT_EXPRESSION)>
	prefix_decrement_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::POSTFIX_INCREMENT_EXPRESSION)>
	postfix_increment_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::POSTFIX_DECREMENT_EXPRESSION)>
	postfix_decrement_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::INDIRECTION_EXPRESSION)>
	indirection_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::POINTER_EXPRESSION)>
	pointer_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::NEGATION_EXPRESSION)>
	negation_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::LOGICAL_NEGATION_EXPRESSION)>
	logical_negation_expression
;

typedef
	unary_expression<static_cast<int>(expression_tag::COMPLEMENT_EXPRESSION)>
	complement_expression
;



typedef
	binary_expression<static_cast<int>(expression_tag::MULTIPLICATION)>
	multiplication_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::DIVISION)>
	division_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::MODULO)>
	modulo_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::ADDITION)>
	addition_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::SUBTRACTION)>
	subtraction_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::LEFT_SHIFT)>
	left_shift_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::RIGHT_SHIFT)>
	right_shift_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::LESS_THAN)>
	less_than_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::LESS_THAN_OR_EQUAL_TO)>
	less_than_or_equal_to_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::GREATER_THAN)>
	greater_than_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::GREATER_THAN_OR_EQUAL_TO)>
	greater_than_or_equal_to_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::EQUAL_TO)>
	equal_to_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::NOT_EQUAL_TO)>
	not_equal_to_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::BITWISE_AND)>
	bitwise_and_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::BITWISE_EXCLUSIVE_OR)>
	bitwise_exclusive_or_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::BITWISE_INCLUSIVE_OR)>
	bitwise_inclusive_or_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::LOGICAL_AND)>
	logical_and_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::LOGICAL_OR)>
	logical_or_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::ASSIGNMENT)>
	assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::MULTIPLICATION_ASSIGNMENT)>
	multiplication_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::DIVISION_ASSIGNMENT)>
	division_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::MODULO_ASSIGNMENT)>
	modulo_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::ADDITION_ASSIGNMENT)>
	addition_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::SUBTRACTION_ASSIGNMENT)>
	subtraction_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::LEFT_SHIFT_ASSIGNMENT)>
	left_shift_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::RIGHT_SHIFT_ASSIGNMENT)>
	right_shift_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::BITWISE_AND_ASSIGNMENT)>
	bitwise_and_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::BITWISE_EXCLUSIVE_OR_ASSIGNMENT)>
	bitwise_exclusive_or_assignment_expression
;

typedef
	binary_expression<static_cast<int>(expression_tag::BITWISE_INCLUSIVE_OR_ASSIGNMENT)>
	bitwise_inclusive_or_assignment_expression
;

}}} //namespace scalpel::cpp::semantic_entities

#endif

