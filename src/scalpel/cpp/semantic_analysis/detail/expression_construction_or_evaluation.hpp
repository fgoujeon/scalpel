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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_CONSTRUCTION_OR_EVALUATION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_CONSTRUCTION_OR_EVALUATION_HPP

#include "unary_expression_evaluation.hpp"
#include "binary_expression_evaluation.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

namespace expression_creation_or_evaluation_policies
{

#define UNARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(NAME) \
struct NAME \
{ \
	static \
	semantic_entities::expression_t \
	evaluate \
	( \
		const semantic_entities::expression_t& operand \
	) \
	{ \
		return evaluate_##NAME##_expression(operand); \
	} \
 \
	static \
	semantic_entities::expression_t \
	create \
	( \
		semantic_entities::expression_t operand \
	); \
};

	UNARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(negation)
	UNARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(logical_negation)
	UNARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(complement)

#undef UNARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY

#define BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(NAME) \
struct NAME \
{ \
	static \
	semantic_entities::expression_t \
	evaluate \
	( \
		const semantic_entities::expression_t& left_operand, \
		const semantic_entities::expression_t& right_operand \
	) \
	{ \
		return evaluate_##NAME##_expression(left_operand, right_operand); \
	} \
 \
	static \
	semantic_entities::expression_t \
	create \
	( \
		semantic_entities::expression_t left_operand, \
		semantic_entities::expression_t right_operand \
	); \
};

	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(addition)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(subtraction)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(multiplication)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(division)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(modulo)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(left_shift)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(right_shift)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(less_than)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(less_than_or_equal_to)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(greater_than)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(greater_than_or_equal_to)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(equal_to)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(not_equal_to)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(bitwise_and)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(bitwise_exclusive_or)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(bitwise_inclusive_or)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(logical_and)
	BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY(logical_or)

#undef BINARY_EXPRESSION_CREATION_OR_EVALUATION_POLICY

}

template<class Policy>
semantic_entities::expression_t
create_or_evaluate_unary_expression
(
	const semantic_entities::expression_t& operand
)
{
	if(is_constant(operand))
		return Policy::evaluate(operand);
	else
		return Policy::create(operand);
}

template<class Policy>
semantic_entities::expression_t
create_or_evaluate_binary_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
)
{
	if(is_constant(left_operand) && is_constant(right_operand))
		return Policy::evaluate(left_operand, right_operand);
	else
		return Policy::create(left_operand, right_operand);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

