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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_EXPRESSION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_EXPRESSION_HPP

#include "type.hpp"
#include "expressions.hpp"
#include "conversions.hpp"
#include "conditional_expression.hpp"
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class variable;

typedef
	utility::variant
	<
		//unary expressions
		prefix_increment_expression,
		prefix_decrement_expression,
		indirection_expression,
		pointer_expression,
		negation_expression,
		logical_negation_expression,
		complement_expression,

		//binary expressions
		multiplication_expression,
		division_expression,
		modulo_expression,
		addition_expression,
		subtraction_expression,
		left_shift_expression,
		right_shift_expression,
		less_than_expression,
		less_than_or_equal_to_expression,
		greater_than_expression,
		greater_than_or_equal_to_expression,
		equal_to_expression,
		not_equal_to_expression,
		bitwise_and_expression,
		bitwise_exclusive_or_expression,
		bitwise_inclusive_or_expression,
		logical_and_expression,
		logical_or_expression,

		//assignment expressions
		assignment_expression,
		multiplication_assignment_expression,
		division_assignment_expression,
		modulo_assignment_expression,
		addition_assignment_expression,
		subtraction_assignment_expression,
		left_shift_assignment_expression,
		right_shift_assignment_expression,
		bitwise_and_assignment_expression,
		bitwise_exclusive_or_assignment_expression,
		bitwise_inclusive_or_assignment_expression,

		//ternary expression
		conditional_expression,

		//conversions
		conversion_to_bool,
		conversion_to_int,
		conversion_to_long_int,
		conversion_to_unsigned_int,
		conversion_to_unsigned_long_int,
		conversion_to_float,
		conversion_to_double,
		conversion_to_long_double,

		//entities
		variable*,
		enum_constant<int>*,
		enum_constant<unsigned int>*,
		enum_constant<long int>*,
		enum_constant<unsigned long int>*,

		//boolean type
		bool,

		//character types
		char,
		wchar_t,

		//integer types
		int,
		long int,
		long long int,
		unsigned int,
		unsigned long int,
		unsigned long long int,

		//floating types
		float,
		double,
		long double,

		//string types
		std::string,
		std::wstring
	>
	expression_t_t
;

//make forward declarations of expression_t possible
struct expression_t: public expression_t_t
{
	//general case
	template<typename U>
	expression_t
	(
		const U& value,
		typename boost::disable_if<boost::is_same<U, variant>>::type* = 0
	):
		expression_t_t(value)
	{
	}

	//if U is a reference of non-const
	template<typename U>
	expression_t
	(
		U& value,
		typename boost::disable_if<boost::is_same<U, variant>>::type* = 0
	):
		expression_t_t(value)
	{
	}

	expression_t(const expression_t_t& rhs):
		expression_t_t(rhs)
	{
	}
};

type_t
get_type(const expression_t& expr);

bool
is_constant(const expression_t& expr);

}}} //namespace scalpel::cpp::semantic_entities

#endif

