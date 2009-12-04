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
#include <memory>
#include <cassert>
#include <scalpel/utility/null_deleter.hpp>
#include "namespace_.hpp"
#include "built_in_type.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name),
	destructor_(new destructor(access::PUBLIC, true, false, false, true)) //implicitly declared destructor
{
	std::cout << "New class " << name << '\n';
}

class_::class_(class_&& c):
	scope_impl_(std::move(c.scope_impl_)),
	name_(std::move(c.name_)),
	nested_classes_(std::move(c.nested_classes_)),
	constructors_(std::move(c.constructors_)),
	destructor_(std::move(c.destructor_)),
	functions_(std::move(c.functions_)),
	variables_(std::move(c.variables_))
{
}

const class_&
class_::operator=(class_&& c)
{
	scope_impl_ = std::move(c.scope_impl_);
	name_ = std::move(c.name_);
	nested_classes_ = std::move(c.nested_classes_);
	constructors_ = std::move(c.constructors_);
	destructor_ = std::move(c.destructor_);
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

class_::base_class_const_iterator_range
class_::base_classes() const
{
	return base_classes_;
}

class_::nested_class_const_iterator_range
class_::nested_classes() const
{
	return nested_classes_;
}

class_::constructor_const_iterator_range
class_::constructors() const
{
	return constructors_;
}

std::shared_ptr<const class_::destructor>
class_::get_destructor() const
{
	return destructor_;
}

void
class_::set_destructor(std::shared_ptr<destructor> d)
{
	destructor_ = d;
}

class_::function_const_iterator_range
class_::functions() const
{
	return functions_;
}

class_::operator_function_const_iterator_range
class_::operator_functions() const
{
	return operator_functions_;
}

class_::variable_const_iterator_range
class_::variables() const
{
	return variables_;
}

void
class_::add(std::shared_ptr<base_class> c)
{
	base_classes_.push_back(c);
}

void
class_::add(std::shared_ptr<member<class_>> nested_class)
{
	nested_classes_.push_back(nested_class);

	/*
	member<class_>& member_ref = *nested_class.get();

	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
	*/
}

void
class_::add(std::shared_ptr<constructor> member)
{
    constructors_.push_back(member);
}

void
class_::add(std::shared_ptr<member_function> member)
{
    functions_.push_back(member);

	/*
	function& member_ref = *member.get();

	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
	*/
}

void
class_::add(std::shared_ptr<member_operator_function> member)
{
    operator_functions_.push_back(member);

	/*
	operator_function& member_ref = *member.get();

	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
	*/
}

void
class_::add(std::shared_ptr<member_variable> member)
{
    variables_.push_back(member);
	//scope_impl_.add_to_named_entities(member);
}



class_::base_class::base_class
(
	std::shared_ptr<class_> base,
	class_::access access,
	const bool is_virtual_specified
):
	base_(base),
	access_(access),
	virtual_specified_(is_virtual_specified)
{
}

class_::base_class::base_class(base_class&& o):
	base_(o.base_),
	access_(o.access_),
	virtual_specified_(o.virtual_specified_)
{
}

std::shared_ptr<const class_>
class_::base_class::base() const
{
	return base_;
}

class_::access
class_::base_class::access() const
{
	return access_;
}

bool
class_::base_class::virtual_specified() const
{
	return virtual_specified_;
}



class_::constructor::constructor
(
	parameters_t&& parameters,
	class_::access access,
	const bool is_inline_specified,
	const bool is_explicit_specified
):
	impl_
	(
		"_",
		std::shared_ptr<const built_in_type>(&built_in_type::void_, scalpel::utility::null_deleter()),
		std::move(parameters),
		false
	),
	access_(access),
	inline_specified_(is_inline_specified),
	explicit_specified_(is_explicit_specified)
{
}

class_::constructor::constructor(constructor&& o):
	impl_(std::move(o.impl_)),
	access_(o.access_),
	inline_specified_(o.inline_specified_),
	explicit_specified_(o.explicit_specified_)
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

bool
class_::constructor::inline_specified() const
{
	return inline_specified_;
}

bool
class_::constructor::explicit_specified() const
{
	return explicit_specified_;
}



class_::destructor::destructor
(
	class_::access access,
	const bool is_inline_specified,
	const bool is_virtual_specified,
	const bool is_pure_specified,
	const bool is_implicitly_declared
):
	access_(access),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified),
	implicitly_declared_(is_implicitly_declared)
{
}

class_::destructor::destructor
(
	class_::access access,
	const bool is_inline_specified,
	const bool is_virtual_specified,
	const bool is_pure_specified
):
	access_(access),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified),
	implicitly_declared_(false)
{
}

class_::destructor::destructor(destructor&& o):
	access_(o.access_),
	inline_specified_(o.inline_specified_),
	virtual_specified_(o.virtual_specified_),
	pure_specified_(o.pure_specified_),
	implicitly_declared_(o.implicitly_declared_)
{
}

class_::access
class_::destructor::access() const
{
	return access_;
}

bool
class_::destructor::inline_specified() const
{
	return inline_specified_;
}

bool
class_::destructor::virtual_specified() const
{
	return virtual_specified_;
}

bool
class_::destructor::pure_specified() const
{
	return pure_specified_;
}

bool
class_::destructor::implicitly_declared() const
{
	return implicitly_declared_;
}




}}} //namespace scalpel::cpp::semantic_entities

