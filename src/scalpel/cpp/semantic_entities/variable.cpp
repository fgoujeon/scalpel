/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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
	const type_variant& type,
	const bool is_static
):
	type_(type),
	name_(name),
	is_static_(is_static)
{
}

member_variable::member_variable
(
	const std::string& name,
	const type_variant& type,
	const bool is_static,
	const bool is_mutable,
	const member_access access
):
	type_(type),
	name_(name),
	is_static_(is_static),
	is_mutable_(is_mutable),
	access_(access)
{
}

bit_field::bit_field
(
	const std::string& name,
	const type_variant& type,
	const unsigned int size,
	const bool is_mutable,
	const member_access access
):
	type_(type),
	name_(name),
	size_(size),
	is_mutable_(is_mutable),
	access_(access)
{
}

}}} //namespace scalpel::cpp::semantic_entities

