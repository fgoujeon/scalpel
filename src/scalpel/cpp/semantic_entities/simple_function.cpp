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
	std::shared_ptr<const type> return_type,
	std::list<parameter>&& parameters,
	bool is_inline_specified,
	bool is_static_specified
):
    name_(name),
	return_type_(return_type),
	parameters_(std::move(parameters)),
	inline_specified_(is_inline_specified),
	static_specified_(is_static_specified),
	defined_(false),
	body_(std::make_shared<statement_block>())
{
}

simple_function::simple_function(simple_function&& rhs):
	name_(std::move(rhs.name_)),
	return_type_(std::move(rhs.return_type_)),
	parameters_(std::move(rhs.parameters_)),
	inline_specified_(rhs.inline_specified_),
	static_specified_(rhs.static_specified_),
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
	inline_specified_ = rhs.inline_specified_;
	static_specified_ = rhs.static_specified_;
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
		inline_specified_ == f.inline_specified_ &&
		static_specified_ == f.static_specified_
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
		if(param.get_type() != param2.get_type())
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

std::shared_ptr<const type>
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
simple_function::inline_specified() const
{
	return inline_specified_;
}

bool
simple_function::static_specified() const
{
	return static_specified_;
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
simple_function::declarative_region_variants()
{
	return declarative_region_variants_;
}

std::shared_ptr<statement_block>
simple_function::body()
{
	return body_;
}


simple_function::parameter::parameter(std::shared_ptr<const type> t, const std::string& name):
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

std::shared_ptr<const type>
simple_function::parameter::get_type() const
{
	return type_;
}

const std::string&
simple_function::parameter::name() const
{
	return name_;
}

}}} //namespace scalpel::cpp::semantic_entities

