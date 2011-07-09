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

#include "expression_construction.hpp"
#include "expression_evaluation.hpp"
#include "conversion_construction.hpp"
#include "value_construction.hpp"
#include "semantic_entity_analysis/expression_information.hpp"
#include <limits>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;
using namespace semantic_entity_analysis;

semantic_entities::expression_t
create_expression(const syntax_nodes::literal& literal_node)
{
	if(const boost::optional<const integer_literal&>& opt_integer_literal_node = get<integer_literal>(&literal_node))
		return create_integer_value(*opt_integer_literal_node);
	if(const boost::optional<const boolean_literal&>& opt_boolean_literal_node = get<boolean_literal>(&literal_node))
		return create_boolean_value(*opt_boolean_literal_node);
	if(const boost::optional<const floating_literal&>& opt_floating_literal_node = get<floating_literal>(&literal_node))
		return create_floating_value(*opt_floating_literal_node);
	if(const boost::optional<const character_literal&>& opt_character_literal_node = get<character_literal>(&literal_node))
		return create_character_value(*opt_character_literal_node);
	if(const boost::optional<const string_literal&>& opt_string_literal_node = get<string_literal>(&literal_node))
		return create_string_value(*opt_string_literal_node);

	assert(false);
}



semantic_entities::expression_t
create_addition_expression
(
	const semantic_entities::expression_t& const_left_operand,
	const semantic_entities::expression_t& const_right_operand
)
{
	semantic_entities::expression_t left_operand = const_left_operand;
	semantic_entities::expression_t right_operand = const_right_operand;

	const expression_information left_operand_info(left_operand);
	const expression_information right_operand_info(right_operand);

	const bool evaluate = is_constant(const_left_operand) && is_constant(const_right_operand);

	if(left_operand_info.has_arithmetic_or_enumeration_type() && right_operand_info.has_arithmetic_or_enumeration_type())
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			evaluate,
			left_operand_info,
			right_operand_info
		);
	}
	else if(left_operand_info.has_pointer_to_defined_type_type() && right_operand_info.has_integral_or_enumeration_type())
	{
	}
	else if(left_operand_info.has_integral_or_enumeration_type() && right_operand_info.has_pointer_to_defined_type_type())
	{
	}
	else
	{
		throw std::runtime_error("create_addition_expression error");
	}

	if(evaluate)
		return evaluate_addition_expression(left_operand, right_operand);
	else
		return semantic_entities::addition_expression
		(
			left_operand,
			right_operand
		);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

