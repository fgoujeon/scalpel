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
#include "detail/empty_class_shared_ptr_vector.hpp"
#include <iostream>
#include <cassert>

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
	defined_(false)
{
	std::cout << "New simple function " << name << "\n";
}

simple_function::simple_function(const simple_function& f):
	name_(f.name_),
	return_type_(f.return_type_),
	parameters_(f.parameters_),
	inline_specified_(f.inline_specified_),
	static_specified_(f.static_specified_),
	defined_(f.defined_),
	statement_block_(f.statement_block_)
{
}

simple_function::simple_function(simple_function&& f):
	name_(std::move(f.name_)),
	return_type_(std::move(f.return_type_)),
	parameters_(std::move(f.parameters_)),
	inline_specified_(f.inline_specified_),
	static_specified_(f.static_specified_),
	defined_(f.defined_),
	statement_block_(std::move(f.statement_block_))
{
}

const simple_function&
simple_function::operator=(const simple_function& f)
{
	name_ = f.name_;
	return_type_ = f.return_type_;
	parameters_ = f.parameters_;
	inline_specified_ = f.inline_specified_;
	static_specified_ = f.static_specified_;
	defined_ = f.defined_;
	statement_block_ = f.statement_block_;

	return *this;
}

const simple_function&
simple_function::operator=(simple_function&& f)
{
	name_ = std::move(f.name_);
	return_type_ = std::move(f.return_type_);
	parameters_ = std::move(f.parameters_);
	inline_specified_ = f.inline_specified_;
	static_specified_ = f.static_specified_;
	defined_ = f.defined_;
	statement_block_ = std::move(f.statement_block_);

	return *this;
}

bool
simple_function::operator==(const simple_function& f) const
{
	return
		name_ == f.name_ &&
		return_type_ == f.return_type_ &&
		parameters_ == f.parameters_ &&
		inline_specified_ == f.inline_specified_ &&
		static_specified_ == f.static_specified_ &&
		defined_ == f.defined_ &&
		statement_block_ == f.statement_block_
	;
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

simple_function::named_entities_t::range
simple_function::named_entities()
{
	return named_entities_;
}

const simple_function::named_entities_t&
simple_function::named_entities() const
{
	return named_entities_;
}

simple_function::named_declarative_regions_t::range
simple_function::named_declarative_regions()
{
	return named_declarative_regions_;
}

const simple_function::named_declarative_regions_t&
simple_function::named_declarative_regions() const
{
	return named_declarative_regions_;
}

simple_function::classes_t::range
simple_function::base_classes()
{
	return detail::empty_class_shared_ptr_vector_range;
}


simple_function::parameter::parameter(std::shared_ptr<const type> t, const std::string& name):
	type_(t),
	name_(name)
{
	std::cout << "New parameter " << name << "\n";
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

