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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_EVALUATION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_EXPRESSION_EVALUATION_HPP

#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

unsigned int
evaluate_expression_to_unsigned_int(const semantic_entities::expression_t& expr);



semantic_entities::expression_t
evaluate_addition_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_subtraction_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_multiplication_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_division_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_modulo_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_left_shift_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_right_shift_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_less_than_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_less_than_or_equal_to_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_greater_than_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_greater_than_or_equal_to_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_equal_to_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

semantic_entities::expression_t
evaluate_not_equal_to_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

