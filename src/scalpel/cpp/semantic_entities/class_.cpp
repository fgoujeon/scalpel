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

#include "class_.hpp"
#include "namespace_.hpp"
#include "built_in_type.hpp"
#include <scalpel/utility/null_deleter.hpp>
#include <iostream>
#include <memory>
#include <cassert>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name),
	destructor_(new destructor(access::PUBLIC, true, false, false, true)) //implicitly declared destructor
{
	std::cout << "New class " << name << '\n';
}

class_::class_(class_&& c):
	name_(std::move(c.name_)),
	named_scopes_(std::move(c.named_scopes_)),
	named_entities_(std::move(c.named_entities_)),
	nested_classes_(std::move(c.nested_classes_)),
	constructors_(std::move(c.constructors_)),
	destructor_(std::move(c.destructor_)),
	functions_(std::move(c.functions_)),
	operator_functions_(std::move(c.operator_functions_)),
	conversion_functions_(std::move(c.conversion_functions_)),
	variables_(std::move(c.variables_))
{
}

const class_&
class_::operator=(class_&& c)
{
	name_ = std::move(c.name_);
	named_scopes_ = std::move(c.named_scopes_);
	named_entities_ = std::move(c.named_entities_);
	nested_classes_ = std::move(c.nested_classes_);
	constructors_ = std::move(c.constructors_);
	destructor_ = std::move(c.destructor_);
	functions_ = std::move(c.functions_);
	operator_functions_ = std::move(c.operator_functions_);
	conversion_functions_ = std::move(c.conversion_functions_);
	variables_ = std::move(c.variables_);

	return *this;
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

named_scope::named_scope_iterator_range
class_::named_scopes()
{
	return named_scopes_.pointers();
}

named_scope::named_scope_const_iterator_range
class_::named_scopes() const
{
	return named_scopes_.pointers();
}

named_scope::named_entity_iterator_range
class_::named_entities()
{
	return named_entities_.pointers();
}

named_scope::named_entity_const_iterator_range
class_::named_entities() const
{
	return named_entities_.pointers();
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

class_::conversion_function_const_iterator_range
class_::conversion_functions() const
{
	return conversion_functions_;
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
class_::add(std::shared_ptr<nested_class> member)
{
	nested_classes_.push_back(member);
	named_scopes_.push_back(member);
	named_entities_.push_back(member);
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
	named_scope_impl_.add_to_named_entities(member_ref);
	*/
}

void
class_::add(std::shared_ptr<member_operator_function> member)
{
    operator_functions_.push_back(member);
	//named_scope_impl_.add_to_named_entities(member);
}

void
class_::add(std::shared_ptr<conversion_function> member)
{
    conversion_functions_.push_back(member);
	//named_scope_impl_.add_to_named_entities(member);
}

void
class_::add(std::shared_ptr<member_variable> member)
{
    variables_.push_back(member);
	//named_scope_impl_.add_to_named_entities(member);
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



class_::member<class_>::member(std::shared_ptr<class_> c, class_::access a):
	entity_(c),
	access_(a)
{
}

class_::member<class_>::member(const nested_class& o):
	entity_(o.entity_),
	access_(o.access_)
{
}

class_::member<class_>::member(nested_class&& o):
	entity_(std::move(o.entity_)),
	access_(std::move(o.access_))
{
}

class_::access
class_::member<class_>::access() const
{
	return access_;
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



class_::conversion_function::conversion_function
(
	std::shared_ptr<const type> t,
	class_::access access,
	const bool is_const_qualified,
	const bool is_volatile_qualified,
	const bool is_inline_specified,
	const bool is_virtual_specified,
	const bool is_pure_specified
):
	type_(t),
	access_(access),
	const_qualified_(is_const_qualified),
	volatile_qualified_(is_volatile_qualified),
	inline_specified_(is_inline_specified),
	virtual_specified_(is_virtual_specified),
	pure_specified_(is_pure_specified)
{
}

class_::conversion_function::conversion_function(conversion_function&& o):
	type_(std::move(o.type_)),
	access_(o.access_),
	const_qualified_(o.const_qualified_),
	volatile_qualified_(o.volatile_qualified_),
	inline_specified_(o.inline_specified_),
	virtual_specified_(o.virtual_specified_),
	pure_specified_(o.pure_specified_)
{
}

std::shared_ptr<const type>
class_::conversion_function::get_type() const
{
	return type_;
}

class_::access
class_::conversion_function::access() const
{
	return access_;
}

bool
class_::conversion_function::const_qualified() const
{
	return const_qualified_;
}

bool
class_::conversion_function::volatile_qualified() const
{
	return volatile_qualified_;
}

bool
class_::conversion_function::inline_specified() const
{
	return inline_specified_;
}

bool
class_::conversion_function::virtual_specified() const
{
	return virtual_specified_;
}

bool
class_::conversion_function::pure_specified() const
{
	return pure_specified_;
}

}}} //namespace scalpel::cpp::semantic_entities

