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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONSTRUCTOR_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONSTRUCTOR_HPP

#include "function_parameter_list.hpp"
#include "simple_function.hpp"
#include "declarative_region_variants.hpp"
#include "detail/class_member_impl.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class constructor:
	public std::enable_shared_from_this<constructor>
{
	public:
		constructor
		(
			function_parameter_list&& parameters,
			const bool is_inline,
			const bool is_explicit
		);

		constructor(constructor&& o);

		bool
		operator==(const constructor& rhs) const;

		bool
		operator!=(const constructor& rhs) const;

		const std::string&
		name() const;

		bool
		has_same_signature(const constructor& f) const;

		const function_parameter_list&
		parameters() const;

		bool
		is_inline() const;

		bool
		is_explicit() const;

		bool
		has_enclosing_declarative_region() const
		{
			return class_member_impl_.has_enclosing_declarative_region();
		}

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const
		{
			return class_member_impl_.enclosing_declarative_region();
		}

		void
		enclosing_declarative_region(const std::shared_ptr<class_>& enclosing_declarative_region)
		{
			class_member_impl_.enclosing_declarative_region(enclosing_declarative_region);
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
		std::shared_ptr<semantic_entities::simple_function> impl_;
		bool is_explicit_;
		detail::class_member_impl class_member_impl_;

		std::shared_ptr<statement_block> body_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

