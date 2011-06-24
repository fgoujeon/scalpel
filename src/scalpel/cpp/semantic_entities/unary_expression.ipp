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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_UNARY_EXPRESSION_IPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_UNARY_EXPRESSION_IPP

#include "utility_functions/detail/make_expression.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

template<int Tag>
unary_expression<Tag>::unary_expression
(
	const expression_t& operand
):
	operand_(utility_functions::detail::make_expression(operand))
{
}

template<int Tag>
unary_expression<Tag>::unary_expression(const unary_expression& rhs):
	operand_(utility_functions::detail::make_expression(rhs.operand()))
{
}

}}} //namespace scalpel::cpp::semantic_entities

#endif

