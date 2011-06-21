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

#include "operations.hpp"
#include "conditional_expression.hpp"
#include <scalpel/utility/variant.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

typedef
	utility::variant
	<
		//binary operations
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

		//ternary operation
		conditional_expression,

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

}}} //namespace scalpel::cpp::semantic_entities

#endif

