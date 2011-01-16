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

#include "function_type.hpp"
#include "type_variant.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

function_type::function_type
(
	const class_* parent_class,
	const type_variant& return_type,
	const std::vector<type_variant>& parameter_types,
	const bool variadic,
	const bool const_qualified,
	const bool volatile_qualified
):
	parent_class_(parent_class),
	return_type_(return_type),
	parameter_types_(parameter_types),
	variadic_(variadic),
	const_qualified_(const_qualified),
	volatile_qualified_(volatile_qualified)
{
}

function_type::function_type(const function_type& rhs):
	parent_class_(rhs.parent_class_),
	return_type_(rhs.return_type_),
	parameter_types_(rhs.parameter_types_),
	variadic_(rhs.variadic_),
	const_qualified_(rhs.const_qualified_),
	volatile_qualified_(rhs.volatile_qualified_)
{
}

bool
operator==(const function_type& lhs, const function_type& rhs)
{
	return
		lhs.parent_class() == rhs.parent_class() &&
		lhs.const_qualified() == rhs.const_qualified() &&
		lhs.volatile_qualified() == rhs.volatile_qualified() &&
		lhs.return_type() == rhs.return_type() &&
		lhs.variadic() == rhs.variadic() &&
		lhs.parameter_types() == rhs.parameter_types()
	;
}

}}} //namespace scalpel::cpp::semantic_entities

