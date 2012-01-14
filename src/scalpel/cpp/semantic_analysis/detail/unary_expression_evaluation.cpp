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

#include "unary_expression_evaluation.hpp"
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
	template<class OperationPolicy>
	class evaluate_unary_expression_visitor: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			//C++ fundamental types (NOT scalpel::semantic_entities::fundamental_type object)
			template<class T>
			semantic_entities::expression_t
			operator()
			(
				const T& operand,
				typename boost::enable_if<boost::is_fundamental<T>>::type* = 0
			) const
			{
				return OperationPolicy::apply(operand);
			}

			//variable
			semantic_entities::expression_t
			operator()(variable* const var) const
			{
				assert(var->default_value());
				return utility::apply_visitor(*this, *(var->default_value()));
			}

			//other types
			template<class T>
			semantic_entities::expression_t
			operator()
			(
				const T&,
				typename boost::disable_if<boost::is_fundamental<T>>::type* = 0
			) const
			{
				assert(false);
			}
	};

	namespace operation_policies
	{
		struct negation
		{
			template<typename T>
			static
			auto apply(T v) -> decltype(-v)
			{
				return -v;
			}
		};

		struct logical_negation
		{
			template<typename T>
			static
			bool
			apply(T v)
			{
				return !v;
			}
		};

		struct complement
		{
			template<typename T>
			static
			T
			apply
			(
				T v,
				typename boost::disable_if_c<
					boost::is_floating_point<T>::value ||
					boost::is_same<T, bool>::value
				>::type* = 0
			)
			{
				return ~v;
			}

			//the ~ operator can't be applied to bool and floating types
			template<typename T>
			static
			int
			apply
			(
				T,
				typename boost::enable_if_c<
					boost::is_floating_point<T>::value ||
					boost::is_same<T, bool>::value
				>::type* = 0
			)
			{
				assert(false);
			}
		};
	}
}

#define EVALUATE_EXPRESSION(NAME) \
semantic_entities::expression_t \
evaluate_##NAME##_expression \
( \
	const semantic_entities::expression_t& operand \
) \
{ \
	evaluate_unary_expression_visitor<operation_policies::NAME> visitor; \
	return utility::apply_visitor(visitor, operand); \
}

EVALUATE_EXPRESSION(negation)
EVALUATE_EXPRESSION(logical_negation)
EVALUATE_EXPRESSION(complement)

#undef EVALUATE_EXPRESSION

}}}} //namespace scalpel::cpp::semantic_analysis::detail

