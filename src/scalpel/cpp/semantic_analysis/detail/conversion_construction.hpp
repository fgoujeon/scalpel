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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CONVERSION_CONSTRUCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CONVERSION_CONSTRUCTION_HPP

#include "semantic_entity_analysis/type_category.hpp"
#include <scalpel/cpp/semantic_graph.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

semantic_entities::expression_t
create_conversion
(
	const semantic_entities::expression_t& expr,
	const semantic_entities::type_t& destination_type
);



template<typename T>
struct conversion_to_type;

#define CONVERSION_TO_TYPE(TYPE, CONVERSION_CLASS) \
template<> \
struct conversion_to_type<TYPE> \
{ \
	typedef semantic_entities::conversion_to_##CONVERSION_CLASS type; \
};

CONVERSION_TO_TYPE(bool, bool)
CONVERSION_TO_TYPE(int, int)
CONVERSION_TO_TYPE(long int, long_int)
//CONVERSION_TO_TYPE(long long int, long_long_int)
CONVERSION_TO_TYPE(unsigned int, unsigned_int)
CONVERSION_TO_TYPE(unsigned long int, unsigned_long_int)
//CONVERSION_TO_TYPE(unsigned long long int, unsigned_long_long_int)
CONVERSION_TO_TYPE(float, float)
CONVERSION_TO_TYPE(double, double)
CONVERSION_TO_TYPE(long double, long_double)

#undef CONVERSION_TO_TYPE



//converts the given expression to T
template<typename T>
struct conversion_to_type_visitor: utility::static_visitor<T>
{
	conversion_to_type_visitor()
	{
	}

	template<typename U>
	T
	operator()
	(
		const U& expr,
		typename boost::enable_if<boost::is_arithmetic<U>>::type* = 0
	) const
	{
		return expr;
	}

	T
	operator()(semantic_entities::variable* const var) const
	{
		assert(var->default_value());
		return apply_visitor(*this, *(var->default_value()));
	}

	template<class U>
	T
	operator()
	(
		const U&,
		typename boost::disable_if<boost::is_arithmetic<U>>::type* = 0
	) const
	{
		assert(false);
	}
};

template<typename T>
semantic_entities::expression_t
create_conversion_to_type
(
	const semantic_entities::expression_t& expr,
	const bool evaluate
)
{
	static const conversion_to_type_visitor<T> visitor;

	if(evaluate)
		return apply_visitor(visitor, expr);
	else
		return typename conversion_to_type<T>::type(expr);
}



semantic_entities::expression_t
create_integral_promotions
(
	const semantic_entities::expression_t& source,
	const semantic_entity_analysis::type_category source_type_category
);

void
create_usual_arithmetic_conversions
(
	semantic_entities::expression_t& left_operand,
	semantic_entities::expression_t& right_operand,
	const bool evaluate,
	const semantic_entity_analysis::type_category left_operand_type_category,
	const semantic_entity_analysis::type_category right_operand_type_category
);

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

