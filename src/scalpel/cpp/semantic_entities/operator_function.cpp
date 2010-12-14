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

#include "operator_function.hpp"
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

operator_function::operator_function
(
	const overloadable_operator op,
	const type_shared_ptr_variant& return_type,
	function_parameter_list&& parameters,
	const bool is_inline,
	const bool is_static
):
    op_(op),
	return_type_(return_type),
	parameters_(std::move(parameters)),
	is_inline_(is_inline),
	is_static_(is_static)
{
}

bool
operator==(const operator_function& lhs, const operator_function& rhs)
{
	return
		have_same_signature(lhs, rhs) &&
		(
			lhs.body().get() == rhs.body().get() ||
			(
				lhs.body().get() != 0 &&
				rhs.body().get() != 0 &&
				*lhs.body() == *rhs.body()
			)
		)
	;
}

bool
operator!=(const operator_function& lhs, const operator_function& rhs)
{
	return !operator==(lhs, rhs);
}

bool
have_same_signature(const operator_function& lhs, const operator_function& rhs)
{
	return
		lhs.get_operator() == rhs.get_operator() &&
		lhs.is_inline() == rhs.is_inline() &&
		lhs.is_static() == rhs.is_static() &&
		utility::are_pointed_objects_equal(lhs.return_type(), rhs.return_type()) &&
		lhs.parameters() == rhs.parameters()
	;
}

}}} //namespace scalpel::cpp::semantic_entities

