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

#ifndef SCALPEL_CPP_SEMANTIC_ENTITIES_TYPEDEF_HPP
#define SCALPEL_CPP_SEMANTIC_ENTITIES_TYPEDEF_HPP

#include "type_variants_fwd.hpp"
#include "detail/declarative_region_member_impl.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

/**
Represents the const qualifier.
*/
class typedef_
{
	public:
		typedef_(const std::string& name, const type_shared_ptr_variant& type);

		const std::string&
		name() const
		{
			return name_;
		}

		const type_shared_ptr_variant&
		type() const
		{
			return type_;
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

	private:
		std::string name_;
		type_shared_ptr_variant type_;

		detail::declarative_region_member_impl declarative_region_member_impl_;
};

bool
operator==(const typedef_& lhs, const typedef_& rhs);

bool
operator!=(const typedef_& lhs, const typedef_& rhs);

}}} //namespace scalpel::cpp::semantic_entities

#endif

