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

#include "operator_.hpp"
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
		typedef simple_function::parameter parameter;
		typedef simple_function::parameters_t parameters_t;

        operator_function
		(
			const operator_ op,
			const type_shared_ptr_variant& return_type,
			parameters_t&& parameters,
			const bool is_inline,
			const bool is_static
		);

		bool
		operator==(const operator_function& rhs) const;

		bool
		operator!=(const operator_function& rhs) const;

		operator_
		get_operator() const;

		const type_shared_ptr_variant&
		return_type() const;

		const parameters_t&
		parameters() const;

		bool
		is_inline() const;

		bool
		is_static() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

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
		std::shared_ptr<simple_function> impl_;
        operator_ op_;

		std::shared_ptr<statement_block> body_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

