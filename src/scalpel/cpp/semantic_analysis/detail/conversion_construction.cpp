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

#include "conversion_construction.hpp"
#include <boost/type_traits/is_arithmetic.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace semantic_entities;
using namespace semantic_entity_analysis;

namespace
{
	class create_conversion_visitor: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			create_conversion_visitor(const semantic_entities::expression_t& expr):
				expr_(expr)
			{
			}

			semantic_entities::expression_t
			operator()(const array& /*type*/) const
			{
				return expr_; //TODO
			}

			semantic_entities::expression_t
			operator()(const fundamental_type& type) const
			{
				switch(type)
				{
					case fundamental_type::BOOL:
						return create_conversion_to_type<bool>(expr_, false);
					case fundamental_type::CHAR:
					case fundamental_type::DOUBLE:
					case fundamental_type::FLOAT:
					case fundamental_type::INT:
					case fundamental_type::LONG_DOUBLE:
					case fundamental_type::LONG_INT:
					case fundamental_type::LONG_LONG_INT:
					case fundamental_type::SHORT_INT:
					case fundamental_type::SIGNED_CHAR:
					case fundamental_type::UNSIGNED_CHAR:
					case fundamental_type::UNSIGNED_INT:
					case fundamental_type::UNSIGNED_LONG_INT:
					case fundamental_type::UNSIGNED_LONG_LONG_INT:
					case fundamental_type::UNSIGNED_SHORT_INT:
					case fundamental_type::VOID:
					case fundamental_type::WCHAR_T:
						return expr_; //TODO
				}

				assert(false);
			}

			semantic_entities::expression_t
			operator()(const function_type& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(class_* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(member_class* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(union_* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(member_union* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(anonymous_union* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(anonymous_member_union* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(const cv_qualified_type& type) const
			{
				return apply_visitor(*this, type.qualified_type());
			}

			semantic_entities::expression_t
			operator()(enum_* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(member_enum* const& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(const pointer& /*type*/) const
			{
				return expr_; //TODO
			}

			semantic_entities::expression_t
			operator()(const pointer_to_member& /*type*/) const
			{
				assert(false);
			}

			semantic_entities::expression_t
			operator()(const reference& type) const
			{
				return apply_visitor(*this, type.qualified_type());
			}

		private:
			const semantic_entities::expression_t& expr_;
	};
}

semantic_entities::expression_t
create_conversion
(
	const semantic_entities::expression_t& expr,
	const semantic_entities::type_t& destination_type
)
{
	if(get_type(expr) == destination_type)
	{
		return expr;
	}
	else
	{
		create_conversion_visitor visitor(expr);
		return apply_visitor(visitor, destination_type);
	}
}



namespace
{
	template<typename T, typename U, bool TSigned, bool USigned>
	struct can_represent_all_the_values_of_base;

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, false, false>
	{
		static const bool value =
			std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
		;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, false, true>
	{
		static const bool value = false;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, true, false>
	{
		static const bool value =
			std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
		;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of_base<T, U, true, true>
	{
		static const bool value =
			std::numeric_limits<T>::min() <= std::numeric_limits<U>::min() &&
			std::numeric_limits<T>::max() >= std::numeric_limits<U>::max()
		;
	};

	template<typename T, typename U>
	struct can_represent_all_the_values_of
	{
		static const bool value =
			can_represent_all_the_values_of_base
			<
				T,
				U,
				std::numeric_limits<T>::is_signed,
				std::numeric_limits<U>::is_signed
			>::value
		;
	};
}

semantic_entities::expression_t
create_integral_promotions
(
	const semantic_entities::expression_t& source,
	const expression_information& expr_info
)
{
	//An rvalue of type char, signed char, unsigned char, short int, or
	//unsigned short int can be converted to an rvalue of type int if int can
	//represent all the values of the source type.
	//Otherwise, the source rvalue can be converted to an rvalue of type
	//unsigned int.
	if(expr_info.has_char_type())
	{
		if(can_represent_all_the_values_of<int, char>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(expr_info.has_signed_char_type())
	{
		if(can_represent_all_the_values_of<int, signed char>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(expr_info.has_unsigned_char_type())
	{
		if(can_represent_all_the_values_of<int, unsigned char>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(expr_info.has_short_int_type())
	{
		if(can_represent_all_the_values_of<int, short int>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	else if(expr_info.has_unsigned_short_int_type())
	{
		if(can_represent_all_the_values_of<int, unsigned short int>::value)
			return conversion_to_int(source);
		else
			return conversion_to_unsigned_int(source);
	}
	//An rvalue of type wchar_t or an enumeration type can be converted to an
	//rvalue of the first of the following types that can represent all the
	//values of its underlying type: int, unsigned int, long, or unsigned long.
	else if(expr_info.has_wchar_t_type())
	{
		if(can_represent_all_the_values_of<int, wchar_t>::value)
			return conversion_to_int(source);
		else if(can_represent_all_the_values_of<unsigned int, wchar_t>::value)
			return conversion_to_unsigned_int(source);
		else if(can_represent_all_the_values_of<long int, wchar_t>::value)
			return conversion_to_long_int(source);
		else if(can_represent_all_the_values_of<unsigned long int, wchar_t>::value)
			return conversion_to_unsigned_long_int(source);
		else
			assert(false);
	}
	else if(expr_info.has_enumeration_type())
	{
		assert(false); //TODO
	}
	//An rvalue for an integral bit-field...
	else if(expr_info.is_bit_field())
	{
		//... can be converted to an rvalue of type int if int can represent all
		//the values of the bit-field

		//otherwise, it can be converted to unsigned int if unsigned int can
		//represent all the values of the bit-field.

		//If the bit-field is larger yet, no integral promotion applies to it.

		//If the bit-field has an enumerated type, it is treated as any other
		//value of that type for promotion purposes.

		assert(false); //TODO
	}
	//An rvalue of type bool can be converted to an rvalue of type int, with
	//false becoming zero and true becoming one.
	else if(expr_info.has_bool_type())
	{
		return conversion_to_int(source);
	}
	else
	{
		return source;
	}
}

void
create_usual_arithmetic_conversions
(
	semantic_entities::expression_t& left_operand,
	semantic_entities::expression_t& right_operand,
	const bool evaluate,
	const expression_information& left_operand_info,
	const expression_information& right_operand_info
)
{
	assert(left_operand_info.has_arithmetic_or_enumeration_type() && right_operand_info.has_arithmetic_or_enumeration_type());

	//if either operand is of type long double, the other shall be converted to long double
	if(left_operand_info.has_long_double_type())
		right_operand = create_conversion_to_type<long double>(right_operand, evaluate);
	else if(right_operand_info.has_long_double_type())
		left_operand = create_conversion_to_type<long double>(left_operand, evaluate);
	//otherwise, if either operand is double, the other shall be converted to double
	else if(left_operand_info.has_double_type())
		right_operand = create_conversion_to_type<double>(right_operand, evaluate);
	else if(right_operand_info.has_double_type())
		left_operand = create_conversion_to_type<double>(left_operand, evaluate);
	//otherwise, if either operand is float, the other shall be converted to float
	else if(left_operand_info.has_float_type())
		right_operand = create_conversion_to_type<float>(right_operand, evaluate);
	else if(right_operand_info.has_float_type())
		left_operand = create_conversion_to_type<float>(left_operand, evaluate);
	//otherwise...
	else
	{
		//the integral promotions shall be performed on both operands
		left_operand = create_integral_promotions(left_operand, left_operand_info);
		right_operand = create_integral_promotions(right_operand, right_operand_info);

		const expression_information& left_operand_info(left_operand);
		const expression_information& right_operand_info(right_operand);

		//if either operand is unsigned long the other shall be converted to unsigned long
		if(left_operand_info.has_unsigned_long_int_type())
			right_operand = create_conversion_to_type<unsigned long int>(right_operand, evaluate);
		else if(right_operand_info.has_unsigned_long_int_type())
			left_operand = create_conversion_to_type<unsigned long int>(left_operand, evaluate);
		//otherwise, if one operand is a long int and the other unsigned int...
		else if
		(
			left_operand_info.has_long_int_type() &&
			right_operand_info.has_unsigned_int_type()
		)
		{
			//if a long int can represent all the values of an unsigned int, the unsigned int shall be converted to a long int
			if(can_represent_all_the_values_of<long int, unsigned int>::value)
				right_operand = create_conversion_to_type<long int>(right_operand, evaluate);
			//otherwise both operands shall be converted to unsigned long int
			else
			{
				left_operand = create_conversion_to_type<unsigned long int>(left_operand, evaluate);
				right_operand = create_conversion_to_type<unsigned long int>(right_operand, evaluate);
			}
		}
		else if
		(
			right_operand_info.has_long_int_type() &&
			left_operand_info.has_unsigned_int_type()
		)
		{
			if(can_represent_all_the_values_of<long int, unsigned int>::value)
				left_operand = create_conversion_to_type<long int>(left_operand, evaluate);
			else
			{
				left_operand = create_conversion_to_type<unsigned long int>(left_operand, evaluate);
				right_operand = create_conversion_to_type<unsigned long int>(right_operand, evaluate);
			}
		}
		//otherwise, if either operand is long, the other shall be converted to long
		else if(left_operand_info.has_long_int_type())
			right_operand = create_conversion_to_type<long int>(right_operand, evaluate);
		else if(right_operand_info.has_long_int_type())
			left_operand = create_conversion_to_type<long int>(left_operand, evaluate);
		//otherwise, if either operand is unsigned, the other shall be converted to unsigned.
		else if(left_operand_info.has_unsigned_int_type())
			right_operand = create_conversion_to_type<unsigned int>(right_operand, evaluate);
		else if(right_operand_info.has_unsigned_int_type())
			left_operand = create_conversion_to_type<unsigned int>(left_operand, evaluate);

		//otherwise, the only remaining case is that both operands are int
	}
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

