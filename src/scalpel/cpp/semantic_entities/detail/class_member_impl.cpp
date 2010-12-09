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

#include "class_member_impl.hpp"
#include "../class_.hpp"
#include <scalpel/utility/ptr_variant_conversion_functions.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities { namespace detail
{

bool
class_member_impl::has_enclosing_declarative_region() const
{
	return !enclosing_declarative_region_.expired();
}

std::shared_ptr<class_>
class_member_impl::enclosing_class() const
{
	if(!enclosing_declarative_region_.expired())
		return enclosing_declarative_region_.lock();
	else
		throw std::runtime_error("The declarative region is not set.");
}

declarative_region_shared_ptr_variant
class_member_impl::enclosing_declarative_region() const
{
	return enclosing_class();
}

void
class_member_impl::enclosing_declarative_region(const std::shared_ptr<class_>& decl_region)
{
	if(enclosing_declarative_region_.expired())
		enclosing_declarative_region_ = decl_region;
	else
		throw std::runtime_error("The declarative region is already set.");
}

}}}} //namespace scalpel::cpp::semantic_entities::detail

