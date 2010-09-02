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
	std::list<parameter>&& parameters,
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
	parameters_t&& parameters,
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

bool
simple_function::has_same_signature(const simple_function& f) const
{
	return
		name_ == f.name_ &&
		return_type_ == f.return_type_ &&
		has_same_parameters(f) &&
		is_inline_ == f.is_inline_ &&
		is_static_ == f.is_static_
	;
}

bool
simple_function::has_same_parameters(const simple_function& f) const
{
	if(parameters_.size() != f.parameters_.size())
		return false;

	for
	(
		parameters_t::const_iterator i = parameters_.begin(), j = f.parameters_.begin();
		i != parameters_.end();
		++i, ++j
	)
	{
		auto param = *i;
		auto param2 = *j;
		if(!are_pointed_objects_equal(param.type(), param2.type()))
			return false;
	}

	return true;
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

const std::list<simple_function::parameter>&
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
        lhs.name() == rhs.name() &&
		lhs.is_inline() == rhs.is_inline() &&
		lhs.is_static() == rhs.is_static() &&
		lhs.defined() == rhs.defined() &&
		*lhs.body() == *rhs.body() &&
		utility::are_pointed_objects_equal(lhs.return_type(), rhs.return_type()) &&
		lhs.parameters() == rhs.parameters()
	;
}

bool
operator!=(const simple_function& lhs, const simple_function& rhs)
{
	return !operator==(lhs, rhs);
}



simple_function::parameter::parameter(const type_shared_ptr_variant& t, const std::string& name):
	type_(t),
	name_(name)
{
}

simple_function::parameter::parameter(const parameter& o):
	type_(o.type_),
	name_(o.name_)
{
}

simple_function::parameter::parameter(parameter&& o):
	type_(std::move(o.type_)),
	name_(std::move(o.name_))
{
}

const simple_function::parameter&
simple_function::parameter::operator=(const parameter& o)
{
	type_ = o.type_;
	name_ = o.name_;

	return *this;
}

const simple_function::parameter&
simple_function::parameter::operator=(parameter&& o)
{
	type_ = o.type_;
	name_ = std::move(o.name_);

	return *this;
}

const type_shared_ptr_variant&
simple_function::parameter::type() const
{
	return type_;
}

const std::string&
simple_function::parameter::name() const
{
	return name_;
}

bool
operator==(const simple_function::parameter& lhs, const simple_function::parameter& rhs)
{
	return
		lhs.type() == rhs.type() &&
		lhs.name() == rhs.name()
	;
}

bool
operator!=(const simple_function::parameter& lhs, const simple_function::parameter& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

