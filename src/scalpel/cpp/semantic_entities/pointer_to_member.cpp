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

#include "pointer_to_member.hpp"
#include "type_variant.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

pointer_to_member::pointer_to_member
(
	const type_variant& qualified_type,
	const class_& member_class
):
	qualified_type_(std::unique_ptr<type_variant>(new type_variant(qualified_type))),
	member_class_(&member_class)
{
}

pointer_to_member::pointer_to_member(const pointer_to_member& rhs):
	qualified_type_(std::unique_ptr<type_variant>(new type_variant(*rhs.qualified_type_))),
	member_class_(rhs.member_class_)
{
}

pointer_to_member&
pointer_to_member::operator=(const pointer_to_member& rhs)
{
	qualified_type_ = std::unique_ptr<type_variant>(new type_variant(*rhs.qualified_type_));
	member_class_ = rhs.member_class_;
	return *this;
}

const type_variant&
pointer_to_member::qualified_type() const
{
	return *qualified_type_;
}

bool
operator==(const pointer_to_member& lhs, const pointer_to_member& rhs)
{
	return
		&lhs.member_class() == &rhs.member_class() &&
		lhs.qualified_type() == rhs.qualified_type()
	;
}

bool
operator!=(const pointer_to_member& lhs, const pointer_to_member& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

