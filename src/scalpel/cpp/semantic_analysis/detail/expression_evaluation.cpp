/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#include "expression_evaluation.hpp"
#include <scalpel/utility/variant.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_fundamental.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/utility/enable_if.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace semantic_entities;

namespace
{
	struct: utility::static_visitor<unsigned int>
	{
		template<typename T>
		unsigned int
		operator()(const T&)
		{
			assert(false);
		}

		unsigned int
		operator()(const int i)
		{
			return i;
		}
	} evaluate_expression_visitor;
}

unsigned int
evaluate_expression_to_unsigned_int(const semantic_entities::expression_t& expr)
{
	return apply_visitor(evaluate_expression_visitor, expr);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

