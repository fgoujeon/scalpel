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

#include "variable.hpp"
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

variable::variable
(
	const std::string& name,
	const type_shared_ptr_variant& type,
	bool is_is_static
):
	type_(type),
	name_(name),
	is_static_(is_is_static)
{
}

variable::variable(const variable& rhs):
	type_(rhs.type_),
	name_(rhs.name_),
	is_static_(rhs.is_static_)
{
}

variable::variable(variable&& rhs):
	type_(rhs.type_),
	name_(std::move(rhs.name_)),
	is_static_(rhs.is_static_)
{
}

const variable&
variable::operator=(variable&& rhs)
{
	type_ = rhs.type_;
	name_ = std::move(rhs.name_);
	is_static_ = rhs.is_static_;

	return *this;
}

const type_shared_ptr_variant&
variable::type() const
{
	return type_;
}

const std::string&
variable::name() const
{
	return name_;
}

bool
variable::is_static() const
{
	return is_static_;
}

bool
variable::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
variable::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
variable::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}

bool
operator==(const variable& lhs, const variable& rhs)
{
	return
		lhs.name() == rhs.name() &&
		lhs.is_static() == rhs.is_static() &&
		are_pointed_objects_equal(lhs.type(), rhs.type())
	;
}

bool
operator!=(const variable& lhs, const variable& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

