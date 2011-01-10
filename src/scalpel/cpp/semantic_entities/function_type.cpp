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

#include "function_type.hpp"
#include "type_variant.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

function_type::function_type
(
	const class_* parent_class_p,
	const bool const_qualified_p,
	const bool volatile_qualified_p,
	const type_variant& return_type_p,
	const std::vector<type_variant>& parameter_types_p,
	const bool variadic_p
):
	parent_class(parent_class_p),
	const_qualified(const_qualified_p),
	volatile_qualified(volatile_qualified_p),
	return_type(return_type_p),
	parameter_types(parameter_types_p),
	variadic(variadic_p)
{
}

bool
operator==(const function_type& lhs, const function_type& rhs)
{
	return
		lhs.parent_class == rhs.parent_class &&
		lhs.const_qualified == rhs.const_qualified &&
		lhs.volatile_qualified == rhs.volatile_qualified &&
		lhs.return_type == rhs.return_type &&
		lhs.parameter_types == rhs.parameter_types &&
		lhs.variadic == rhs.variadic
	;
}

}}} //namespace scalpel::cpp::semantic_entities

