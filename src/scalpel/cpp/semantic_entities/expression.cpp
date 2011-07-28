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

#include "expression.hpp"
#include "variable.hpp"
#include "type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace
{

#define FUNDAMENTAL_TYPE(TYPE, RETURN_TYPE) \
type_t \
operator()(const TYPE&) \
{ \
	return RETURN_TYPE; \
}

#define ASSERTION_FAILURE(TYPE) \
type_t \
operator()(const TYPE&) \
{ \
	assert(false); \
}

	struct: utility::static_visitor<type_t>
	{
		//
		//unary expressions
		//

		ASSERTION_FAILURE(prefix_increment_expression)
		ASSERTION_FAILURE(prefix_decrement_expression)
		ASSERTION_FAILURE(indirection_expression)
		ASSERTION_FAILURE(pointer_expression)

		type_t
		operator()(const negation_expression& expr)
		{
			return apply_visitor(*this, expr.operand());
		}

		FUNDAMENTAL_TYPE(logical_negation_expression, fundamental_type::BOOL)
		ASSERTION_FAILURE(complement_expression)



		//
		//binary expressions
		//

		ASSERTION_FAILURE(multiplication_expression)
		ASSERTION_FAILURE(division_expression)
		ASSERTION_FAILURE(modulo_expression)
		ASSERTION_FAILURE(addition_expression)
		ASSERTION_FAILURE(subtraction_expression)
		ASSERTION_FAILURE(left_shift_expression)
		ASSERTION_FAILURE(right_shift_expression)

		FUNDAMENTAL_TYPE(less_than_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(less_than_or_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(greater_than_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(greater_than_or_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(not_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(logical_or_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(logical_and_expression, fundamental_type::BOOL)

		ASSERTION_FAILURE(bitwise_and_expression)
		ASSERTION_FAILURE(bitwise_exclusive_or_expression)
		ASSERTION_FAILURE(bitwise_inclusive_or_expression)



		//
		//assignment expressions
		//

		ASSERTION_FAILURE(assignment_expression)
		ASSERTION_FAILURE(multiplication_assignment_expression)
		ASSERTION_FAILURE(division_assignment_expression)
		ASSERTION_FAILURE(modulo_assignment_expression)
		ASSERTION_FAILURE(addition_assignment_expression)
		ASSERTION_FAILURE(subtraction_assignment_expression)
		ASSERTION_FAILURE(left_shift_assignment_expression)
		ASSERTION_FAILURE(right_shift_assignment_expression)
		ASSERTION_FAILURE(bitwise_and_assignment_expression)
		ASSERTION_FAILURE(bitwise_exclusive_or_assignment_expression)
		ASSERTION_FAILURE(bitwise_inclusive_or_assignment_expression)



		//
		//ternary expression
		//

		ASSERTION_FAILURE(conditional_expression)



		//
		//conversions
		//

		FUNDAMENTAL_TYPE(conversion_to_bool, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(conversion_to_int, fundamental_type::INT)
		FUNDAMENTAL_TYPE(conversion_to_long_int, fundamental_type::LONG_INT)
		FUNDAMENTAL_TYPE(conversion_to_unsigned_int, fundamental_type::UNSIGNED_INT)
		FUNDAMENTAL_TYPE(conversion_to_unsigned_long_int, fundamental_type::UNSIGNED_LONG_INT)
		FUNDAMENTAL_TYPE(conversion_to_float, fundamental_type::FLOAT)
		FUNDAMENTAL_TYPE(conversion_to_double, fundamental_type::DOUBLE)
		FUNDAMENTAL_TYPE(conversion_to_long_double, fundamental_type::LONG_DOUBLE)



		//
		//entities
		//

		type_t
		operator()(variable* const& var)
		{
			return var->type();
		}

		FUNDAMENTAL_TYPE(enum_constant<int>*, fundamental_type::INT)
		FUNDAMENTAL_TYPE(enum_constant<unsigned int>*, fundamental_type::UNSIGNED_INT)
		FUNDAMENTAL_TYPE(enum_constant<long int>*, fundamental_type::LONG_INT)
		FUNDAMENTAL_TYPE(enum_constant<unsigned long int>*, fundamental_type::UNSIGNED_LONG_INT)



		//
		//fundamental types
		//

		FUNDAMENTAL_TYPE(bool, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(char, fundamental_type::CHAR)
		FUNDAMENTAL_TYPE(wchar_t, fundamental_type::WCHAR_T)
		FUNDAMENTAL_TYPE(int, fundamental_type::INT)
		FUNDAMENTAL_TYPE(long int, fundamental_type::LONG_INT)
		FUNDAMENTAL_TYPE(long long int, fundamental_type::LONG_LONG_INT)
		FUNDAMENTAL_TYPE(unsigned int, fundamental_type::UNSIGNED_INT)
		FUNDAMENTAL_TYPE(unsigned long int, fundamental_type::UNSIGNED_LONG_INT)
		FUNDAMENTAL_TYPE(unsigned long long int, fundamental_type::UNSIGNED_LONG_LONG_INT)
		FUNDAMENTAL_TYPE(float, fundamental_type::FLOAT)
		FUNDAMENTAL_TYPE(double, fundamental_type::DOUBLE)
		FUNDAMENTAL_TYPE(long double, fundamental_type::LONG_DOUBLE)

		type_t
		operator()(const std::string& str)
		{
			return array(str.size() + 1, fundamental_type::CHAR);
		}

		type_t
		operator()(const std::wstring& str)
		{
			return array(str.size() + 1, fundamental_type::WCHAR_T);
		}
	} get_type_visitor;

#undef FUNDAMENTAL_TYPE
#undef ASSERTION_FAILURE

}

type_t
get_type(const expression_t& expr)
{
	return apply_visitor(get_type_visitor, expr);
}



namespace
{

#define RETURN_TRUE(TYPE) \
bool \
operator()(const TYPE&) \
{ \
	return true; \
}

	struct: utility::static_visitor<bool>
	{
		RETURN_TRUE(bool)
		RETURN_TRUE(char)
		RETURN_TRUE(wchar_t)
		RETURN_TRUE(int)
		RETURN_TRUE(long int)
		RETURN_TRUE(long long int)
		RETURN_TRUE(unsigned int)
		RETURN_TRUE(unsigned long int)
		RETURN_TRUE(unsigned long long int)
		RETURN_TRUE(float)
		RETURN_TRUE(double)
		RETURN_TRUE(long double)
		RETURN_TRUE(std::string)
		RETURN_TRUE(std::wstring)

		bool
		operator()(variable* const& var)
		{
			const type_t type = var->type();

			if(const cv_qualified_type* opt_cv_qualified_type = utility::get<cv_qualified_type>(&type))
				return opt_cv_qualified_type->const_qualified();

			return false;
		}

		//otherwise, return false
		template<typename T>
		bool
		operator()(const T&)
		{
			return false;
		}
	} is_constant_visitor;

#undef RETURN_TRUE

}

bool
is_constant(const expression_t& expr)
{
	return apply_visitor(is_constant_visitor, expr);
}

}}} //namespace scalpel::cpp::semantic_entities

