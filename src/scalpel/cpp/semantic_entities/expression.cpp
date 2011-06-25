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

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace
{

#define FUNDAMENTAL_TYPE(TYPE, RETURN_TYPE) \
type_variant \
operator()(const TYPE&) \
{ \
	return RETURN_TYPE; \
}

	struct: utility::static_visitor<type_variant>
	{
		template<typename T>
		type_variant
		operator()(const T&)
		{
			assert(false);
		}

		type_variant
		operator()(const negation_expression& expr)
		{
			return apply_visitor(*this, expr.operand());
		}



		//
		//unary expressions
		//

		FUNDAMENTAL_TYPE(logical_negation_expression, fundamental_type::BOOL)



		//
		//binary expressions
		//

		FUNDAMENTAL_TYPE(less_than_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(less_than_or_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(greater_than_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(greater_than_or_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(not_equal_to_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(logical_or_expression, fundamental_type::BOOL)
		FUNDAMENTAL_TYPE(logical_and_expression, fundamental_type::BOOL)



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

		type_variant
		operator()(const std::string& str)
		{
			return array(str.size() + 1, fundamental_type::CHAR);
		}

		type_variant
		operator()(const std::wstring& str)
		{
			return array(str.size() + 1, fundamental_type::WCHAR_T);
		}
	} get_type_visitor;

#undef EXPRESSION_TYPE

}

type_variant
get_type(const expression_t& expr)
{
	return apply_visitor(get_type_visitor, expr);
}

}}} //namespace scalpel::cpp::semantic_entities

