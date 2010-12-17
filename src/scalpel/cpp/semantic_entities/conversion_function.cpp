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

#include "conversion_function.hpp"
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

conversion_function::conversion_function
(
	const type_shared_ptr_variant& return_type,
	const bool is_inline
):
	return_type_(return_type),
	is_inline_(is_inline)
{
}

conversion_function::conversion_function(const conversion_function& rhs):
	std::enable_shared_from_this<conversion_function>(),
	return_type_(rhs.return_type_),
	is_inline_(rhs.is_inline_)
{
}

const type_shared_ptr_variant&
conversion_function::return_type() const
{
	return return_type_;
}

bool
conversion_function::is_inline() const
{
	return is_inline_;
}

bool
conversion_function::has_enclosing_declarative_region() const
{
	return declarative_region_member_impl_.has_enclosing_declarative_region();
}

declarative_region_shared_ptr_variant
conversion_function::enclosing_declarative_region() const
{
	return declarative_region_member_impl_.enclosing_declarative_region();
}

void
conversion_function::enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.enclosing_declarative_region(decl_region);
}

bool
operator==(const conversion_function& lhs, const conversion_function& rhs)
{
	return
		lhs.is_inline() == rhs.is_inline() &&
		utility::are_pointed_objects_equal(lhs.return_type(), rhs.return_type()) &&
		*lhs.body() == *rhs.body()
	;
}

bool
operator!=(const conversion_function& lhs, const conversion_function& rhs)
{
	return !operator==(lhs, rhs);
}

bool
have_same_signature(const conversion_function& lhs, const conversion_function& rhs)
{
	return
		utility::are_pointed_objects_equal(lhs.return_type(), rhs.return_type())
	;
}

}}} //namespace scalpel::cpp::semantic_entities

