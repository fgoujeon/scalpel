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
	parameters_t&& parameters,
	const bool is_inline,
	const bool is_explicit
):
	impl_
	(
		simple_function::make_shared
		(
			"_",
			fundamental_type_shared_ptrs::void_,
			std::move(parameters),
			is_inline,
			false
		)
	),
	is_explicit_(is_explicit)
{
}

constructor::constructor(constructor&& o):
	impl_(std::move(o.impl_)),
	is_explicit_(o.is_explicit_)
{
}

bool
constructor::operator==(const constructor& rhs) const
{
	return
		is_explicit_ == rhs.is_explicit_ &&
		*impl_ == *rhs.impl_
	;
}

bool
constructor::operator!=(const constructor& rhs) const
{
	return !operator==(rhs);
}

const std::string&
constructor::name() const
{
	return class_member_impl_.enclosing_class()->name();
}

const constructor::parameters_t&
constructor::parameters() const
{
	return impl_->parameters();
}

bool
constructor::is_inline() const
{
	return impl_->is_inline();
}

bool
constructor::is_explicit() const
{
	return is_explicit_;
}

}}} //namespace scalpel::cpp::semantic_entities

