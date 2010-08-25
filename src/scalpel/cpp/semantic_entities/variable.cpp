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

namespace scalpel { namespace cpp { namespace semantic_entities
{

variable::variable
(
	const std::string& name,
	std::shared_ptr<const type> t,
	bool is_is_static
):
	type_(t),
	name_(name),
	is_static_(is_is_static)
{
}

variable::variable(const variable& v):
	type_(v.type_),
	name_(v.name_),
	is_static_(v.is_static_)
{
}

variable::variable(variable&& v):
	type_(v.type_),
	name_(std::move(v.name_)),
	is_static_(v.is_static_)
{
}

const variable&
variable::operator=(variable&& v)
{
	type_ = v.type_;
	name_ = std::move(v.name_);
	is_static_ = v.is_static_;

	return *this;
}

std::shared_ptr<const type>
variable::get_type() const
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

}}} //namespace scalpel::cpp::semantic_entities

