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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_BINARY_EXPRESSION_EVALUATION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_BINARY_EXPRESSION_EVALUATION_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

#define EVALUATE_EXPRESSION(NAME) \
semantic_entities::expression_t \
evaluate_##NAME##_expression \
( \
	const semantic_entities::expression_t& left_operand, \
	const semantic_entities::expression_t& right_operand \
);

EVALUATE_EXPRESSION(addition)
EVALUATE_EXPRESSION(subtraction)
EVALUATE_EXPRESSION(multiplication)
EVALUATE_EXPRESSION(division)
EVALUATE_EXPRESSION(modulo)
EVALUATE_EXPRESSION(left_shift)
EVALUATE_EXPRESSION(right_shift)
EVALUATE_EXPRESSION(less_than)
EVALUATE_EXPRESSION(less_than_or_equal_to)
EVALUATE_EXPRESSION(greater_than)
EVALUATE_EXPRESSION(greater_than_or_equal_to)
EVALUATE_EXPRESSION(equal_to)
EVALUATE_EXPRESSION(not_equal_to)
EVALUATE_EXPRESSION(bitwise_and)
EVALUATE_EXPRESSION(bitwise_exclusive_or)
EVALUATE_EXPRESSION(bitwise_inclusive_or)
EVALUATE_EXPRESSION(logical_and)
EVALUATE_EXPRESSION(logical_or)

#undef EVALUATE_EXPRESSION

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

