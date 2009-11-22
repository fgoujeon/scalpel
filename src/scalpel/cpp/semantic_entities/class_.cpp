/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "class_.hpp"

#include <iostream>
#include <cassert>
#include "namespace_.hpp"
#include "built_in_type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name)
{
	std::cout << "New class " << name << '\n';
}

class_::class_(class_&& c):
	scope_impl_(std::move(c.scope_impl_)),
	name_(std::move(c.name_)),
	classes_(std::move(c.classes_)),
	constructors_(std::move(c.constructors_)),
	functions_(std::move(c.functions_)),
	variables_(std::move(c.variables_))
{
}

const class_&
class_::operator=(class_&& c)
{
	scope_impl_ = std::move(c.scope_impl_);
	name_ = std::move(c.name_);
	classes_ = std::move(c.classes_);
	constructors_ = std::move(c.constructors_);
	functions_ = std::move(c.functions_);
	variables_ = std::move(c.variables_);

	return *this;
}

void
class_::accept(scope_visitor& v)
{
	v.visit(*this);
}

const std::string&
class_::name() const
{
    return name_;
}

bool
class_::is_a_type() const
{
    return true;
}

bool
class_::is_global() const
{
    return false;
}

scope::scope_iterator_range
class_::scopes()
{
	return scope_impl_.scopes();
}

scope::scope_const_iterator_range
class_::scopes() const
{
	return scope_impl_.scopes();
}

scope::named_entity_iterator_range
class_::named_entities()
{
	return scope_impl_.named_entities();
}

scope::named_entity_const_iterator_range
class_::named_entities() const
{
	return scope_impl_.named_entities();
}

class_::class_const_iterator_range
class_::classes() const
{
	return classes_;
}

class_::constructor_const_iterator_range
class_::constructors() const
{
	return constructors_;
}

class_::function_const_iterator_range
class_::functions() const
{
	return functions_;
}

class_::variable_const_iterator_range
class_::variables() const
{
	return variables_;
}

void
class_::add(member<class_>&& nested_class)
{
	classes_.push_back(std::move(nested_class));

	class_& member_ref = classes_.back().entity();

	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
class_::add(constructor&& member)
{
    constructors_.push_back(std::move(member));
}

void
class_::add(member<function>&& member)
{
    functions_.push_back(std::move(member));

	function& member_ref = functions_.back().entity();

	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
class_::add(member<variable>&& member)
{
    variables_.push_back(std::move(member));

	variable& member_ref = variables_.back().entity();

	scope_impl_.add_to_named_entities(member_ref);
}



class_::constructor::constructor(parameters_t&& parameters, class_::access access):
	impl_("_", built_in_type::void_, std::move(parameters)),
	access_(access)
{
}

class_::constructor::constructor(constructor&& o):
	impl_(std::move(o.impl_)),
	access_(o.access_)
{
}

const class_::constructor::parameters_t&
class_::constructor::parameters() const
{
	return impl_.parameters();
}

class_::access
class_::constructor::access() const
{
	return access_;
}



class_::member<function>::member
(
	function&& entity,
	class_::access a,
	bool is_const_qualified,
	bool is_volatile_qualified,
	bool is_inline_specified,
	bool is_virtual_specified
):
	entity_(std::move(entity)),
	access_(a),
	const_qualified_(is_const_qualified),
	volatile_qualified_(is_volatile_qualified),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified)
{
}

class_::member<function>::member(member<function>&& o):
	entity_(std::move(o.entity_)),
	access_(o.access_),
	const_qualified_(o.const_qualified_),
	volatile_qualified_(o.volatile_qualified_),
	inline_specified_(o.inline_specified_),
	virtual_specified_(o.virtual_specified_)
{
}

const function&
class_::member<function>::entity() const
{
	return entity_;
}

function&
class_::member<function>::entity()
{
	return entity_;
}

class_::access
class_::member<function>::access() const
{
	return access_;
}

bool
class_::member<function>::const_qualified() const
{
	return const_qualified_;
}

bool
class_::member<function>::volatile_qualified() const
{
	return volatile_qualified_;
}

bool
class_::member<function>::inline_specified() const
{
	return inline_specified_;
}

bool
class_::member<function>::virtual_specified() const
{
	return virtual_specified_;
}

}}} //namespace scalpel::cpp::semantic_entities

