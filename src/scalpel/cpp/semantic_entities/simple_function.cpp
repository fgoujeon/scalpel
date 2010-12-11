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

#include "simple_function.hpp"
#include "type_variants.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

simple_function::simple_function
(
	const std::string& name,
	const type_shared_ptr_variant& return_type,
	function_parameter_list&& parameters,
	bool is_inline,
	bool is_static
):
    name_(name),
	return_type_(return_type),
	parameters_(std::move(parameters)),
	is_inline_(is_inline),
	is_static_(is_static)
{
}

std::shared_ptr<simple_function>
simple_function::make_shared
(
	const std::string& name,
	const type_shared_ptr_variant& return_type,
	function_parameter_list&& parameters,
	bool is_inline,
	bool is_static
)
{
	std::shared_ptr<simple_function> new_simple_function =
		std::shared_ptr<simple_function>
		(
			new simple_function
			(
				name,
				return_type,
				std::move(parameters),
				is_inline,
				is_static
			)
		)
	;

	return new_simple_function;
}

const std::string&
simple_function::name() const
{
    return name_;
}

const type_shared_ptr_variant&
simple_function::return_type() const
{
	return return_type_;
}

const function_parameter_list&
simple_function::parameters() const
{
	return parameters_;
}

bool
simple_function::is_inline() const
{
	return is_inline_;
}

bool
simple_function::is_static() const
{
	return is_static_;
}

bool
simple_function::defined() const
{
	return body_.get();
}

bool
simple_function::has_enclosing_declarative_region() const
{
	return declarative_region_member_impl_.has_enclosing_declarative_region();
}

declarative_region_shared_ptr_variant
simple_function::enclosing_declarative_region() const
{
	return declarative_region_member_impl_.enclosing_declarative_region();
}

void
simple_function::enclosing_declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.enclosing_declarative_region(decl_region);
}

std::shared_ptr<statement_block>
simple_function::body()
{
	return body_;
}

std::shared_ptr<const statement_block>
simple_function::body() const
{
	return body_;
}

void
simple_function::body(std::shared_ptr<statement_block> b)
{
	body_ = b;
	body_->enclosing_declarative_region(shared_from_this());
}



bool
operator==(const simple_function& lhs, const simple_function& rhs)
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
operator!=(const simple_function& lhs, const simple_function& rhs)
{
	return !operator==(lhs, rhs);
}

bool
have_same_signature(const simple_function& lhs, const simple_function& rhs)
{
	return
		lhs.name() == rhs.name() &&
		lhs.is_inline() == rhs.is_inline() &&
		lhs.is_static() == rhs.is_static() &&
		utility::are_pointed_objects_equal(lhs.return_type(), rhs.return_type()) &&
		lhs.parameters() == rhs.parameters()
	;
}

}}} //namespace scalpel::cpp::semantic_entities

