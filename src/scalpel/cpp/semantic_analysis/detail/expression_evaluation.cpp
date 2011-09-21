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



namespace
{
	template<class OperationPolicy, class T>
	class evaluate_binary_expression_visitor_2: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			evaluate_binary_expression_visitor_2(const T& right_operand):
				right_operand_(right_operand)
			{
			}

			//C++ fundamental types (NOT scalpel::semantic_entities::fundamental_type object)
			template<class U>
			semantic_entities::expression_t
			operator()
			(
				const U& left_operand,
				typename boost::enable_if<boost::is_fundamental<U>>::type* = 0
			) const
			{
				return OperationPolicy::apply(left_operand, right_operand_);
			}

			//variable
			semantic_entities::expression_t
			operator()(variable* const var) const
			{
				assert(var->default_value());
				return utility::apply_visitor(*this, *(var->default_value()));
			}

			//other types
			template<class U>
			semantic_entities::expression_t
			operator()
			(
				const U&,
				typename boost::disable_if<boost::is_fundamental<U>>::type* = 0
			) const
			{
				assert(false);
			}

		private:
			const T& right_operand_;
	};

	template<class OperationPolicy>
	class evaluate_binary_expression_visitor: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			evaluate_binary_expression_visitor(const semantic_entities::expression_t& left_operand):
				left_operand_(left_operand)
			{
			}

			//C++ fundamental types (NOT scalpel::semantic_entities::fundamental_type object)
			template<class T>
			semantic_entities::expression_t
			operator()
			(
				const T& right_operand,
				typename boost::enable_if<boost::is_fundamental<T>>::type* = 0
			) const
			{
				evaluate_binary_expression_visitor_2<OperationPolicy, T> visitor(right_operand);
				return utility::apply_visitor(visitor, left_operand_);
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

		private:
			const semantic_entities::expression_t& left_operand_;
	};

	namespace comparison_operation_policies
	{
		//all the comparison operation policies are based on this higher order policy
		template<class OperationPolicy>
		struct comparison
		{
			template<typename T1, typename T2>
			static
			bool
			apply
			(
				T1 a,
				T2 b,
				typename boost::disable_if_c
				<
					(boost::is_signed<T1>::value && boost::is_unsigned<T2>::value) ||
					(boost::is_unsigned<T1>::value && boost::is_signed<T2>::value)
				>::type* = 0,
				typename boost::disable_if_c<boost::is_same<T1, bool>::value || boost::is_same<T2, bool>::value>::type* = 0
			)
			{
				return OperationPolicy::apply(a, b);
			}

			//avoid "comparison between signed and unsigned integer" warning
			template<typename T1, typename T2>
			static
			bool
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c
				<
					(boost::is_signed<T1>::value && boost::is_unsigned<T2>::value) ||
					(boost::is_unsigned<T1>::value && boost::is_signed<T2>::value)
				>::type* = 0,
				typename boost::disable_if_c<boost::is_same<T1, bool>::value || boost::is_same<T2, bool>::value>::type* = 0
			)
			{
				assert(false);
			}

			//the comparison operators can't be applied to bool
			template<typename T1, typename T2>
			static
			bool
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_same<T1, bool>::value || boost::is_same<T2, bool>::value>::type* = 0
			)
			{
				assert(false);
			}
		};

		struct less_than
		{
			template<typename T1, typename T2>
			static
			bool
			apply(T1 a, T2 b)
			{
				return a < b;
			}
		};

		struct less_than_or_equal_to
		{
			template<typename T1, typename T2>
			static
			bool
			apply(T1 a, T2 b)
			{
				return a <= b;
			}
		};

		struct greater_than
		{
			template<typename T1, typename T2>
			static
			bool
			apply(T1 a, T2 b)
			{
				return a > b;
			}
		};

		struct greater_than_or_equal_to
		{
			template<typename T1, typename T2>
			static
			bool
			apply(T1 a, T2 b)
			{
				return a >= b;
			}
		};

		struct equal_to
		{
			template<typename T1, typename T2>
			static
			bool
			apply(T1 a, T2 b)
			{
				return a == b;
			}
		};

		struct not_equal_to
		{
			template<typename T1, typename T2>
			static
			bool
			apply(T1 a, T2 b)
			{
				return a != b;
			}
		};
	}

	namespace operation_policies
	{
		struct addition
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a + b)
			{
				return a + b;
			}
		};

		struct subtraction
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a - b)
			{
				return a - b;
			}
		};

		struct multiplication
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a * b)
			{
				return a * b;
			}
		};

		struct division
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a / b)
			{
				return a / b;
			}
		};

		struct modulo
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a % b)
			{
				return a % b;
			}

			//the modulo operator can't be applied to floating types
			template<typename T1, typename T2>
			static
			int
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_floating_point<T1>::value || boost::is_floating_point<T2>::value>::type* = 0
			)
			{
				assert(false);
			}
		};

		struct left_shift
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a << b)
			{
				return a << b;
			}

			//the left shift operator can't be applied to floating types
			template<typename T1, typename T2>
			static
			int
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_floating_point<T1>::value || boost::is_floating_point<T2>::value>::type* = 0
			)
			{
				assert(false);
			}
		};

		struct right_shift
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a >> b)
			{
				return a >> b;
			}

			//the left shift operator can't be applied to floating types
			template<typename T1, typename T2>
			static
			int
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_floating_point<T1>::value || boost::is_floating_point<T2>::value>::type* = 0
			)
			{
				assert(false);
			}
		};

		typedef
			comparison_operation_policies::comparison<comparison_operation_policies::less_than>
			less_than
		;

		typedef
			comparison_operation_policies::comparison<comparison_operation_policies::less_than_or_equal_to>
			less_than_or_equal_to
		;

		typedef
			comparison_operation_policies::comparison<comparison_operation_policies::greater_than>
			greater_than
		;

		typedef
			comparison_operation_policies::comparison<comparison_operation_policies::greater_than_or_equal_to>
			greater_than_or_equal_to
		;

		typedef
			comparison_operation_policies::comparison<comparison_operation_policies::equal_to>
			equal_to
		;

		typedef
			comparison_operation_policies::comparison<comparison_operation_policies::not_equal_to>
			not_equal_to
		;

		struct bitwise_and
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a & b)
			{
				return a & b;
			}

			//the & operator can't be applied to floating types
			template<typename T1, typename T2>
			static
			int
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_floating_point<T1>::value || boost::is_floating_point<T2>::value>::type* = 0
			)
			{
				assert(false);
			}
		};

		struct bitwise_exclusive_or
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a ^ b)
			{
				return a ^ b;
			}

			//the ^ operator can't be applied to floating types
			template<typename T1, typename T2>
			static
			int
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_floating_point<T1>::value || boost::is_floating_point<T2>::value>::type* = 0
			)
			{
				assert(false);
			}
		};

		struct bitwise_inclusive_or
		{
			template<typename T1, typename T2>
			static
			auto apply(T1 a, T2 b) -> decltype(a | b)
			{
				return a | b;
			}

			//the | operator can't be applied to floating types
			template<typename T1, typename T2>
			static
			int
			apply
			(
				T1,
				T2,
				typename boost::enable_if_c<boost::is_floating_point<T1>::value || boost::is_floating_point<T2>::value>::type* = 0
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
	const semantic_entities::expression_t& left_operand, \
	const semantic_entities::expression_t& right_operand \
) \
{ \
	evaluate_binary_expression_visitor<operation_policies::NAME> visitor(left_operand); \
	return utility::apply_visitor(visitor, right_operand); \
}

EVALUATE_EXPRESSION(addition)
EVALUATE_EXPRESSION(subtraction)
EVALUATE_EXPRESSION(multiplication)
EVALUATE_EXPRESSION(division)
EVALUATE_EXPRESSION(modulo)
EVALUATE_EXPRESSION(left_shift)
EVALUATE_EXPRESSION(right_shift)
EVALUATE_EXPRESSION(less_than)
EVALUATE_EXPRESSION(less_than_or_equal_to)
EVALUATE_EXPRESSION(greater_than)
EVALUATE_EXPRESSION(greater_than_or_equal_to)
EVALUATE_EXPRESSION(equal_to)
EVALUATE_EXPRESSION(not_equal_to)
EVALUATE_EXPRESSION(bitwise_and)
EVALUATE_EXPRESSION(bitwise_exclusive_or)
EVALUATE_EXPRESSION(bitwise_inclusive_or)

#undef EVALUATE_EXPRESSION

}}}} //namespace scalpel::cpp::semantic_analysis::detail

