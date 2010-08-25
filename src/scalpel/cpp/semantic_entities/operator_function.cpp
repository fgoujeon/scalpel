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

namespace scalpel { namespace cpp { namespace semantic_entities
{

operator_function::operator_function
(
	const operator_ op,
	std::shared_ptr<const type> return_type,
	parameters_t&& parameters,
	const bool is_inline_specified
):
	impl_("", return_type, std::move(parameters), is_inline_specified, false),
    op_(op)
{
}

operator_function::operator_function(operator_function&& rhs):
	impl_(std::move(rhs.impl_)),
    op_(rhs.op_)
{
}

const operator_function&
operator_function::operator=(operator_function&& rhs)
{
	impl_ = std::move(rhs.impl_);
    op_ = rhs.op_;

	return *this;
}

operator_
operator_function::get_operator() const
{
	return op_;
}

std::shared_ptr<const type>
operator_function::return_type() const
{
	return impl_.return_type();
}

const std::list<operator_function::parameter>&
operator_function::parameters() const
{
	return impl_.parameters();
}

bool
operator_function::inline_specified() const
{
	return impl_.inline_specified();
}

bool
operator_function::defined() const
{
	return impl_.defined();
}

void
operator_function::defined(const bool d)
{
	impl_.defined(d);
}

bool
operator_function::has_declarative_region() const
{
	return impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
operator_function::declarative_region() const
{
	return impl_.declarative_region();
}

void
operator_function::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	impl_.declarative_region(decl_region);
}

}}} //namespace scalpel::cpp::semantic_entities
