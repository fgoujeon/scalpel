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
	struct: utility::static_visitor<type_t>
	{
		template<class T>
		type_t
		operator()(T* type)
		{
			return type;
		}
	} to_type_visitor;

#define FUNDAMENTAL_TYPE(TYPE, RETURN_TYPE) \
type_t \
operator()(const TYPE&) \
{ \
	return RETURN_TYPE; \
}

#define RETURN_SINGLE_OPERAND_TYPE(TYPE) \
type_t \
operator()(const TYPE& expr) \
{ \
	return apply_visitor(*this, expr.operand()); \
}

#define RETURN_LEFT_OPERAND_TYPE(TYPE) \
type_t \
operator()(const TYPE& expr) \
{ \
	return apply_visitor(*this, expr.left_operand()); \
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

		RETURN_SINGLE_OPERAND_TYPE(prefix_increment_expression)
		RETURN_SINGLE_OPERAND_TYPE(prefix_decrement_expression)
		RETURN_SINGLE_OPERAND_TYPE(postfix_increment_expression)
		RETURN_SINGLE_OPERAND_TYPE(postfix_decrement_expression)

		type_t
		operator()(const indirection_expression& expr)
		{
			type_t expr_type = apply_visitor(*this, expr.operand());
			if(pointer* opt_type = utility::get<pointer>(&expr_type))
			{
				return opt_type->qualified_type();
			}
			else
			{
				assert(false);
			}
		}

		type_t
		operator()(const pointer_expression& expr)
		{
			return pointer(apply_visitor(*this, expr.operand()));
		}

		RETURN_SINGLE_OPERAND_TYPE(negation_expression)
		FUNDAMENTAL_TYPE(logical_negation_expression, fundamental_type::BOOL)
		RETURN_SINGLE_OPERAND_TYPE(complement_expression)



		//
		//binary expressions
		//

		RETURN_LEFT_OPERAND_TYPE(multiplication_expression)
		RETURN_LEFT_OPERAND_TYPE(division_expression)
		RETURN_LEFT_OPERAND_TYPE(modulo_expression)
		RETURN_LEFT_OPERAND_TYPE(addition_expression) //TODO
		RETURN_LEFT_OPERAND_TYPE(subtraction_expression) //TODO
		RETURN_LEFT_OPERAND_TYPE(left_shift_expression) //TODO
		RETURN_LEFT_OPERAND_TYPE(right_shift_expression) //TODO

		FUNDAMENTAL_TYPE(less_than_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(less_than_or_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(greater_than_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(greater_than_or_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(not_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(logical_or_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(logical_and_expression, fundamental_type::BOOL)

		RETURN_LEFT_OPERAND_TYPE(bitwise_and_expression) //TODO
		RETURN_LEFT_OPERAND_TYPE(bitwise_exclusive_or_expression) //TODO
		RETURN_LEFT_OPERAND_TYPE(bitwise_inclusive_or_expression) //TODO



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

		type_t
		operator()(const conditional_expression& expr)
		{
			return apply_visitor(*this, expr.true_operand());
		}



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

		template<typename UnderlyingType>
		type_t
		operator()(enum_constant<UnderlyingType>* const& c)
		{
			return apply_visitor(to_type_visitor, c->enclosing_declarative_region());
		}



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
#undef RETURN_SINGLE_OPERAND_TYPE
#undef RETURN_LEFT_OPERAND_TYPE
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

