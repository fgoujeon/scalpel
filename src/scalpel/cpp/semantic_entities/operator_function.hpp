/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_OPERATOR_FUNCTION_HPP

#include "overloadable_operator.hpp"
#include "function_parameter_list.hpp"
#include "simple_function.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents a C++ operator function.
*/
class operator_function:
	public std::enable_shared_from_this<operator_function>
{
    public:
        operator_function
		(
			const overloadable_operator op,
			const type_shared_ptr_variant& return_type,
			function_parameter_list&& parameters = function_parameter_list(),
			const bool is_inline = false,
			const bool is_static = false
		);

		overloadable_operator
		get_operator() const
		{
			return op_;
		}

		const type_shared_ptr_variant&
		return_type() const
		{
			return return_type_;
		}

		const function_parameter_list&
		parameters() const
		{
			return parameters_;
		}

		bool
		is_inline() const
		{
			return is_inline_;
		}

		bool
		is_static() const
		{
			return is_static_;
		}

		bool
		has_enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.has_enclosing_declarative_region();
		}

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const
		{
			return declarative_region_member_impl_.enclosing_declarative_region();
		}

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region)
		{
			declarative_region_member_impl_.enclosing_declarative_region(enclosing_declarative_region);
		}

		bool
		defined() const
		{
			return body_.get();
		}

		std::shared_ptr<statement_block>
		body()
		{
			return body_;
		}

		std::shared_ptr<const statement_block>
		body() const
		{
			return body_;
		}

		void
		body(std::shared_ptr<statement_block> b)
		{
			body_ = b;
			body_->enclosing_declarative_region(shared_from_this());
		}

    private:
        overloadable_operator op_;
		type_shared_ptr_variant return_type_;
		function_parameter_list parameters_;
		bool is_inline_;
		bool is_static_;
		detail::declarative_region_member_impl declarative_region_member_impl_;

		std::shared_ptr<statement_block> body_;
};

bool
operator==(const operator_function& lhs, const operator_function& rhs);

bool
operator!=(const operator_function& lhs, const operator_function& rhs);

bool
have_same_signature(const operator_function& lhs, const operator_function& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

