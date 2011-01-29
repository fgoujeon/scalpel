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

#include "reference.hpp"
#include "type_variant.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

reference::reference(const type_variant& qualified_type):
	qualified_type_(std::unique_ptr<type_variant>(new type_variant(qualified_type)))
{
}

reference::reference(const reference& rhs):
	qualified_type_(std::unique_ptr<type_variant>(new type_variant(*rhs.qualified_type_)))
{
}

reference&
reference::operator=(const reference& rhs)
{
	qualified_type_ = std::unique_ptr<type_variant>(new type_variant(*rhs.qualified_type_));
	return *this;
}

const type_variant&
reference::qualified_type() const
{
	return *qualified_type_;
}

bool
operator==(const reference& lhs, const reference& rhs)
{
	return
		lhs.qualified_type() == rhs.qualified_type()
	;
}

bool
operator!=(const reference& lhs, const reference& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

