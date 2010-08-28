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

namespace scalpel { namespace cpp { namespace semantic_entities
{

simple_function::simple_function
(
	const std::string& name,
	const type_shared_ptr_variant& return_type,
	std::list<parameter>&& parameters,
	bool is_is_inline,
	bool is_is_static
):
    name_(name),
	return_type_(return_type),
	parameters_(std::move(parameters)),
	is_inline_(is_is_inline),
	is_static_(is_is_static),
	defined_(false),
	body_(std::make_shared<statement_block>())
{
}

simple_function::simple_function(simple_function&& rhs):
	name_(std::move(rhs.name_)),
	return_type_(std::move(rhs.return_type_)),
	parameters_(std::move(rhs.parameters_)),
	is_inline_(rhs.is_inline_),
	is_static_(rhs.is_static_),
	defined_(rhs.defined_),
	body_(rhs.body_)
{
}

const simple_function&
simple_function::operator=(simple_function&& rhs)
{
	name_ = std::move(rhs.name_);
	return_type_ = std::move(rhs.return_type_);
	parameters_ = std::move(rhs.parameters_);
	is_inline_ = rhs.is_inline_;
	is_static_ = rhs.is_static_;
	defined_ = rhs.defined_;
	body_ = rhs.body_;

	return *this;
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
		if(!equals(param.type(), param2.type()))
			return false;
	}

	return true;
}

const std::string&
simple_function::name() const
{
    return name_;
}

bool
simple_function::is_open_to_outside() const
{
	return false;
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
	return defined_;
}

void
simple_function::defined(bool d)
{
	defined_ = d;
}

bool
simple_function::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
simple_function::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
simple_function::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}

const simple_function::declarative_region_shared_ptr_variants_t&
simple_function::declarative_regions()
{
	return declarative_regions_;
}

std::shared_ptr<statement_block>
simple_function::body()
{
	return body_;
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

bool
simple_function::parameter::operator==(const parameter& o) const
{
	return
		type_ == o.type_ &&
		name_ == o.name_
	;
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

}}} //namespace scalpel::cpp::semantic_entities

