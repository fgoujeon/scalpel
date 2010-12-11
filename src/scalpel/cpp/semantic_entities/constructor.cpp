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

#include "constructor.hpp"
#include "class_.hpp"
#include "fundamental_type_shared_ptrs.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

constructor::constructor
(
	function_parameter_list&& parameters,
	const bool is_inline,
	const bool is_explicit
):
	parameters_(std::move(parameters)),
	is_inline_(is_inline),
	is_explicit_(is_explicit)
{
}

constructor::constructor(constructor&& rhs):
	parameters_(std::move(rhs.parameters_)),
	is_inline_(rhs.is_inline_),
	is_explicit_(rhs.is_explicit_)
{
}

const std::string&
constructor::name() const
{
	return class_member_impl_.enclosing_class()->name();
}



bool
operator==(const constructor& lhs, const constructor& rhs)
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
operator!=(const constructor& lhs, const constructor& rhs)
{
	return !operator==(lhs, rhs);
}

bool
have_same_signature(const constructor& lhs, const constructor& rhs)
{
	return
		lhs.is_inline() == rhs.is_inline() &&
		lhs.is_explicit() == rhs.is_explicit() &&
		lhs.parameters() == rhs.parameters()
	;
}

}}} //namespace scalpel::cpp::semantic_entities

