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
#include "conversion_construction.hpp"
#include "value_construction.hpp"
#include "semantic_entity_analysis/type_category.hpp"
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



namespace
{
	const bool long_int_contains_unsigned_int =
		std::numeric_limits<long int>::min() <= std::numeric_limits<unsigned int>::min() &&
		std::numeric_limits<long int>::max() >= std::numeric_limits<unsigned int>::max()
	;

	void
	create_usual_arithmetic_conversions
	(
		semantic_entities::expression_t& left_operand,
		semantic_entities::expression_t& right_operand,
		const type_category left_operand_type_category,
		const type_category right_operand_type_category
	)
	{
		if(is_arithmetic_or_enumeration(left_operand_type_category) && is_arithmetic_or_enumeration(right_operand_type_category))
		{
			//if either operand is of type long double, the other shall be converted to long double
			if(is_long_double(left_operand_type_category))
				right_operand = create_conversion_to_long_double(right_operand);
			else if(is_long_double(right_operand_type_category))
				left_operand = create_conversion_to_long_double(left_operand);
			//otherwise, if either operand is double, the other shall be converted to double
			else if(is_double(left_operand_type_category))
				right_operand = create_conversion_to_double(right_operand);
			else if(is_double(right_operand_type_category))
				left_operand = create_conversion_to_double(left_operand);
			//otherwise, if either operand is float, the other shall be converted to float
			else if(is_float(left_operand_type_category))
				right_operand = create_conversion_to_float(right_operand);
			else if(is_float(right_operand_type_category))
				left_operand = create_conversion_to_float(left_operand);
			//otherwise...
			else
			{
				//the integral promotions shall be performed on both operands
				left_operand = create_integral_promotions(left_operand, left_operand_type_category);
				right_operand = create_integral_promotions(right_operand, right_operand_type_category);

				const type_category left_operand_type_category = get_category(get_type(left_operand));
				const type_category right_operand_type_category = get_category(get_type(right_operand));

				//if either operand is unsigned long the other shall be converted to unsigned long
				if(is_unsigned_long_int(left_operand_type_category))
					right_operand = create_conversion_to_unsigned_long_int(right_operand);
				else if(is_unsigned_long_int(right_operand_type_category))
					left_operand = create_conversion_to_unsigned_long_int(left_operand);
				//otherwise, if one operand is a long int and the other unsigned int...
				else if
				(
					is_long_int(left_operand_type_category) &&
					is_unsigned_int(right_operand_type_category)
				)
				{
					//if a long int can represent all the values of an unsigned int, the unsigned int shall be converted to a long int
					if(long_int_contains_unsigned_int)
						right_operand = create_conversion_to_long_int(right_operand);
					//otherwise both operands shall be converted to unsigned long int
					else
					{
						left_operand = create_conversion_to_unsigned_long_int(left_operand);
						right_operand = create_conversion_to_unsigned_long_int(right_operand);
					}
				}
				else if
				(
					is_long_int(right_operand_type_category) &&
					is_unsigned_int(left_operand_type_category)
				)
				{
					if(long_int_contains_unsigned_int)
						left_operand = create_conversion_to_long_int(left_operand);
					else
					{
						left_operand = create_conversion_to_unsigned_long_int(left_operand);
						right_operand = create_conversion_to_unsigned_long_int(right_operand);
					}
				}
				//otherwise, if either operand is long, the other shall be converted to long
				else if(is_long_int(left_operand_type_category))
					right_operand = create_conversion_to_long_int(right_operand);
				else if(is_long_int(right_operand_type_category))
					left_operand = create_conversion_to_long_int(left_operand);
				//otherwise, if either operand is unsigned, the other shall be converted to unsigned.
				else if(is_unsigned_int(left_operand_type_category))
					right_operand = create_conversion_to_unsigned_int(right_operand);
				else if(is_unsigned_int(right_operand_type_category))
					left_operand = create_conversion_to_unsigned_int(left_operand);

				//otherwise, the only remaining case is that both operands are int
			}
		}
	}
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

	const type_category left_operand_type_category = get_category(get_type(left_operand));
	const type_category right_operand_type_category = get_category(get_type(right_operand));

	if(is_arithmetic_or_enumeration(left_operand_type_category) && is_arithmetic_or_enumeration(right_operand_type_category))
	{
		create_usual_arithmetic_conversions
		(
			left_operand,
			right_operand,
			left_operand_type_category,
			right_operand_type_category
		);
	}
	else if(is_pointer_to_defined_type(left_operand_type_category) && is_integral_or_enumeration(right_operand_type_category))
	{
	}
	else if(is_integral_or_enumeration(left_operand_type_category) && is_pointer_to_defined_type(right_operand_type_category))
	{
	}
	else
	{
		throw std::runtime_error("create_addition_expression error");
	}

	return semantic_entities::addition_expression
	(
		left_operand,
		right_operand
	);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

