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
#include <boost/type_traits/is_fundamental.hpp>
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
	template<class T>
	class evaluate_addition_expression_visitor_2: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			evaluate_addition_expression_visitor_2(const T& right_operand):
				right_operand_(right_operand)
			{
			}

			//fundamental types
			template<class U>
			semantic_entities::expression_t
			operator()
			(
				const U& left_operand,
				typename boost::enable_if<boost::is_fundamental<U>>::type* = 0
			) const
			{
				return left_operand + right_operand_;
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

	class evaluate_addition_expression_visitor: public utility::static_visitor<semantic_entities::expression_t>
	{
		public:
			evaluate_addition_expression_visitor(const semantic_entities::expression_t& left_operand):
				left_operand_(left_operand)
			{
			}

			//fundamental types
			template<class T>
			semantic_entities::expression_t
			operator()
			(
				const T& right_operand,
				typename boost::enable_if<boost::is_fundamental<T>>::type* = 0
			) const
			{
				evaluate_addition_expression_visitor_2<T> visitor(right_operand);
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
}

semantic_entities::expression_t
evaluate_addition_expression
(
	const semantic_entities::expression_t& left_operand,
	const semantic_entities::expression_t& right_operand
)
{
	evaluate_addition_expression_visitor visitor(left_operand);
	return utility::apply_visitor(visitor, right_operand);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

