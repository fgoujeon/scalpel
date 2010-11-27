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

#include "simple_function.hpp"
#include "declarative_region_member_impl.hpp"
#include "declarative_region_variants.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class constructor
{
	public:
		typedef simple_function::parameter parameter;
		typedef simple_function::parameters_t parameters_t;

		constructor
		(
			parameters_t&& parameters,
			const bool is_inline,
			const bool is_explicit
		);

		constructor(constructor&& o);

		bool
		operator==(const constructor& rhs) const;

		bool
		operator!=(const constructor& rhs) const;

		const parameters_t&
		parameters() const;

		bool
		is_inline() const;

		bool
		is_explicit() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

	private:
		std::shared_ptr<semantic_entities::simple_function> impl_;
		bool is_explicit_;
		declarative_region_member_impl declarative_region_member_impl_;
};

}}} //namespace scalpel::cpp::semantic_entities

#endif

