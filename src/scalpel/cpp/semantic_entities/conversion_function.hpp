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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSION_FUNCTION_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_CONVERSION_FUNCTION_HPP

#include "type_variants_fwd.hpp"
#include "declarative_region_variants.hpp"
#include "declarative_region_member_impl.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class conversion_function
{
	public:
		conversion_function
		(
			const type_shared_ptr_variant& return_type,
			const bool is_inline
		);

		conversion_function(conversion_function&& o);

		const type_shared_ptr_variant&
		return_type() const;

		bool
		is_inline() const;

		bool
		has_enclosing_declarative_region() const;

		declarative_region_shared_ptr_variant
		enclosing_declarative_region() const;

		void
		enclosing_declarative_region(const declarative_region_shared_ptr_variant& enclosing_declarative_region);

	private:
		type_shared_ptr_variant return_type_;
		bool is_inline_;
		declarative_region_member_impl declarative_region_member_impl_;
};

bool
operator==(const conversion_function& lhs, const conversion_function& rhs);

bool
operator!=(const conversion_function& lhs, const conversion_function& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

