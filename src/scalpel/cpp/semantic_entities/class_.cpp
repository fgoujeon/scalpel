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
#include "built_in_type_shared_ptrs.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name)
{
}

std::shared_ptr<class_>
class_::make_shared(const std::string& name)
{
	std::shared_ptr<class_> new_class(new class_(name));

	//set default constructor
	new_class->reset_destructor();

	return new_class;
}

const std::string&
class_::name() const
{
    return name_;
}

bool
class_::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
class_::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
class_::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}

const class_::open_declarative_region_shared_ptr_variants_t&
class_::open_declarative_regions()
{
	return open_declarative_regions_;
}

class_::classes_t::range
class_::base_classes()
{
	return base_classes_;
}

const class_::classes_t&
class_::base_classes() const
{
	return base_classes_;
}

class_::classes_t::range
class_::nested_classes()
{
	return nested_classes_;
}

const class_::classes_t&
class_::nested_classes() const
{
	return nested_classes_;
}

class_::constructors_t::range
class_::constructors()
{
	return constructors_;
}

const class_::constructors_t&
class_::constructors() const
{
	return constructors_;
}

std::shared_ptr<const class_::destructor>
class_::get_destructor() const
{
	return destructor_;
}

class_::simple_functions_t::range
class_::simple_functions()
{
	return simple_functions_;
}

const class_::simple_functions_t&
class_::simple_functions() const
{
	return simple_functions_;
}

class_::operator_functions_t::range
class_::operator_functions()
{
	return operator_functions_;
}

const class_::operator_functions_t&
class_::operator_functions() const
{
	return operator_functions_;
}

class_::conversion_functions_t::range
class_::conversion_functions()
{
	return conversion_functions_;
}

const class_::conversion_functions_t&
class_::conversion_functions() const
{
	return conversion_functions_;
}

class_::variables_t::range
class_::variables()
{
	return variables_;
}

const class_::variables_t&
class_::variables() const
{
	return variables_;
}

void
class_::add_base_class
(
	std::shared_ptr<class_> base_class,
	const access acc,
	bool is_virtual
)
{
	base_classes_.push_back(base_class);

	base_class_access_[base_class] = acc;
	if(is_virtual) virtual_base_classes_.push_back(base_class);
}

void
class_::add_member(std::shared_ptr<class_> member, const access acc)
{
	member->declarative_region(shared_from_this());
	nested_classes_.push_back(member);
	open_declarative_regions_.push_back(member);

	member_access_[std::shared_ptr<const class_>(member)] = acc;
}

void
class_::add_member(std::shared_ptr<constructor> member, const access acc)
{
	member->declarative_region(shared_from_this());
    constructors_.push_back(member);

	member_access_[std::shared_ptr<const constructor>(member)] = acc;
}

void
class_::set_destructor
(
	std::shared_ptr<destructor> member,
	const access acc,
	const bool is_virtual,
	const bool is_pure
)
{
	member->declarative_region(shared_from_this());
	destructor_ = member;

	std::shared_ptr<const destructor> const_member(member);
	member_access_[const_member] = acc;
	if(is_virtual) virtual_member_functions_.push_back(const_member);
	if(is_pure) pure_member_functions_.push_back(const_member);
}

void
class_::reset_destructor()
{
	set_destructor
	(
		std::make_shared<destructor>(false),
		access::PUBLIC,
		false,
		false
	);
}

void
class_::add_member
(
	std::shared_ptr<simple_function> member,
	const access acc,
	const bool is_const,
	const bool is_volatile,
	const bool is_virtual,
	const bool is_pure
)
{
	member->declarative_region(shared_from_this());
    simple_functions_.push_back(member);

	std::shared_ptr<const simple_function> const_member(member);
	member_access_[const_member] = acc;
	if(is_const) const_member_functions_.push_back(const_member);
	if(is_volatile) volatile_member_functions_.push_back(const_member);
	if(is_virtual) virtual_member_functions_.push_back(const_member);
	if(is_pure) pure_member_functions_.push_back(const_member);
}

void
class_::add_member
(
	std::shared_ptr<operator_function> member,
	const access acc,
	const bool is_const,
	const bool is_volatile,
	const bool is_virtual,
	const bool is_pure
)
{
	member->declarative_region(shared_from_this());
    operator_functions_.push_back(member);

	std::shared_ptr<const operator_function> const_member(member);
	member_access_[const_member] = acc;
	if(is_const) const_member_functions_.push_back(const_member);
	if(is_volatile) volatile_member_functions_.push_back(const_member);
	if(is_virtual) virtual_member_functions_.push_back(const_member);
	if(is_pure) pure_member_functions_.push_back(const_member);
}

void
class_::add_member
(
	std::shared_ptr<conversion_function> member,
	const access acc,
	const bool is_const,
	const bool is_volatile,
	const bool is_virtual,
	const bool is_pure
)
{
	member->declarative_region(shared_from_this());
    conversion_functions_.push_back(member);

	std::shared_ptr<const conversion_function> const_member(member);
	member_access_[const_member] = acc;
	if(is_const) const_member_functions_.push_back(const_member);
	if(is_volatile) volatile_member_functions_.push_back(const_member);
	if(is_virtual) virtual_member_functions_.push_back(const_member);
	if(is_pure) pure_member_functions_.push_back(const_member);
}

void
class_::add_member
(
	std::shared_ptr<variable> member,
	const access acc,
	const bool is_mutable
)
{
	member->declarative_region(shared_from_this());
    variables_.push_back(member);

	std::shared_ptr<const variable> const_member(member);
	member_access_[const_member] = acc;
	if(is_mutable) mutable_member_variables_.push_back(const_member);
}

class_::access
class_::base_class_access(std::shared_ptr<const class_> base_class) const
{
	auto it = base_class_access_.find(base_class);
	if(it != base_class_access_.end())
		return it->second;
	else
		throw std::runtime_error("The given entity is not a base class of that class.");
}

bool
class_::is_virtual_base_class(std::shared_ptr<const class_> base_class) const
{
	return std::find
	(
		virtual_base_classes_.begin(),
		virtual_base_classes_.end(),
		base_class
	) != virtual_base_classes_.end();
}

class_::access
class_::member_access(const member_t& member) const
{
	auto it = member_access_.find(member);
	if(it != member_access_.end())
		return it->second;
	else
		throw std::runtime_error("The given entity is not a member of that class.");
}

bool
class_::is_const_member_function(const member_t& member) const
{
	return std::find
	(
		const_member_functions_.begin(),
		const_member_functions_.end(),
		member
	) != const_member_functions_.end();
}

bool
class_::is_volatile_member_function(const member_t& member) const
{
	return std::find
	(
		volatile_member_functions_.begin(),
		volatile_member_functions_.end(),
		member
	) != volatile_member_functions_.end();
}

bool
class_::is_virtual_member_function(const member_t& member) const
{
	return std::find
	(
		virtual_member_functions_.begin(),
		virtual_member_functions_.end(),
		member
	) != virtual_member_functions_.end();
}

bool
class_::is_pure_member_function(const member_t& member) const
{
	return std::find
	(
		pure_member_functions_.begin(),
		pure_member_functions_.end(),
		member
	) != pure_member_functions_.end();
}

bool
class_::is_mutable_member_variable(std::shared_ptr<const variable> member) const
{
	return std::find
	(
		mutable_member_variables_.begin(),
		mutable_member_variables_.end(),
		member
	) != mutable_member_variables_.end();
}

bool
operator==(const class_& lhs, const class_& rhs)
{
	if(lhs.name() != rhs.name())
		return false;

	//base classes
	if(lhs.base_classes().size() != rhs.base_classes().size())
		return false;
	for
	(
		auto i = lhs.base_classes().begin(), j = rhs.base_classes().begin();
		i != lhs.base_classes().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.base_class_access(*i) != rhs.base_class_access(*j))
			return false;
		if(lhs.is_virtual_base_class(*i) != rhs.is_virtual_base_class(*j))
			return false;
	}

	//nested classes
	if(lhs.nested_classes().size() != rhs.nested_classes().size())
		return false;
	for
	(
		auto i = lhs.nested_classes().begin(), j = rhs.nested_classes().begin();
		i != lhs.nested_classes().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.member_access(*i) != rhs.member_access(*j))
			return false;
	}

	//constructors
	if(lhs.constructors().size() != rhs.constructors().size())
		return false;
	for
	(
		auto i = lhs.constructors().begin(), j = rhs.constructors().begin();
		i != lhs.constructors().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.member_access(*i) != rhs.member_access(*j))
			return false;
	}

	//destructor
	if(*lhs.get_destructor() != *rhs.get_destructor())
		return false;
	if(lhs.member_access(lhs.get_destructor()) != rhs.member_access(rhs.get_destructor()))
		return false;
	if(lhs.is_virtual_member_function(lhs.get_destructor()) != rhs.is_virtual_member_function(rhs.get_destructor()))
		return false;
	if(lhs.is_pure_member_function(lhs.get_destructor()) != rhs.is_pure_member_function(rhs.get_destructor()))
		return false;

	//simple functions
	if(lhs.simple_functions().size() != rhs.simple_functions().size())
		return false;
	for
	(
		auto i = lhs.simple_functions().begin(), j = rhs.simple_functions().begin();
		i != lhs.simple_functions().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.member_access(*i) != rhs.member_access(*j))
			return false;
		if(lhs.is_const_member_function(*i) != rhs.is_const_member_function(*j))
			return false;
		if(lhs.is_volatile_member_function(*i) != rhs.is_volatile_member_function(*j))
			return false;
		if(lhs.is_virtual_member_function(*i) != rhs.is_virtual_member_function(*j))
			return false;
		if(lhs.is_pure_member_function(*i) != rhs.is_pure_member_function(*j))
			return false;
	}

	//operator functions
	if(lhs.operator_functions().size() != rhs.operator_functions().size())
		return false;
	for
	(
		auto i = lhs.operator_functions().begin(), j = rhs.operator_functions().begin();
		i != lhs.operator_functions().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.member_access(*i) != rhs.member_access(*j))
			return false;
		if(lhs.is_const_member_function(*i) != rhs.is_const_member_function(*j))
			return false;
		if(lhs.is_volatile_member_function(*i) != rhs.is_volatile_member_function(*j))
			return false;
		if(lhs.is_virtual_member_function(*i) != rhs.is_virtual_member_function(*j))
			return false;
		if(lhs.is_pure_member_function(*i) != rhs.is_pure_member_function(*j))
			return false;
	}

	//conversion functions
	if(lhs.conversion_functions().size() != rhs.conversion_functions().size())
		return false;
	for
	(
		auto i = lhs.conversion_functions().begin(), j = rhs.conversion_functions().begin();
		i != lhs.conversion_functions().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.member_access(*i) != rhs.member_access(*j))
			return false;
		if(lhs.is_const_member_function(*i) != rhs.is_const_member_function(*j))
			return false;
		if(lhs.is_volatile_member_function(*i) != rhs.is_volatile_member_function(*j))
			return false;
		if(lhs.is_virtual_member_function(*i) != rhs.is_virtual_member_function(*j))
			return false;
		if(lhs.is_pure_member_function(*i) != rhs.is_pure_member_function(*j))
			return false;
	}

	//variables
	if(lhs.variables().size() != rhs.variables().size())
		return false;
	for
	(
		auto i = lhs.variables().begin(), j = rhs.variables().begin();
		i != lhs.variables().end();
		++i, ++j
	)
	{
		if(**i != **j)
			return false;
		if(lhs.member_access(*i) != rhs.member_access(*j))
			return false;
		if(lhs.is_mutable_member_variable(*i) != rhs.is_mutable_member_variable(*j))
			return false;
	}

	return true;
}

bool
operator!=(const class_& lhs, const class_& rhs)
{
	return !operator==(lhs, rhs);
}



class_::constructor::constructor
(
	parameters_t&& parameters,
	const bool is_is_inline,
	const bool is_is_explicit
):
	impl_
	(
		"_",
		built_in_type_shared_ptrs::void_,
		std::move(parameters),
		is_is_inline,
		false
	),
	is_explicit_(is_is_explicit)
{
}

class_::constructor::constructor(constructor&& o):
	impl_(std::move(o.impl_)),
	is_explicit_(o.is_explicit_)
{
}

bool
class_::constructor::operator==(const constructor& rhs) const
{
	return
		is_explicit_ == rhs.is_explicit_ &&
		impl_ == rhs.impl_
	;
}

bool
class_::constructor::operator!=(const constructor& rhs) const
{
	return !operator==(rhs);
}

const class_::constructor::parameters_t&
class_::constructor::parameters() const
{
	return impl_.parameters();
}

bool
class_::constructor::is_inline() const
{
	return impl_.is_inline();
}

bool
class_::constructor::is_explicit() const
{
	return is_explicit_;
}

bool
class_::constructor::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
class_::constructor::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
class_::constructor::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}



class_::destructor::destructor
(
	const bool is_is_inline
):
	is_inline_(is_is_inline)
{
}

class_::destructor::destructor(destructor&& o):
	is_inline_(o.is_inline_)
{
}

bool
class_::destructor::is_inline() const
{
	return is_inline_;
}

bool
class_::destructor::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
class_::destructor::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
class_::destructor::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}

bool
operator==(const class_::destructor& lhs, const class_::destructor& rhs)
{
	return lhs.is_inline() == rhs.is_inline();
}

bool
operator!=(const class_::destructor& lhs, const class_::destructor& rhs)
{
	return !operator==(lhs, rhs);
}



class_::conversion_function::conversion_function
(
	const type_shared_ptr_variant& return_type,
	const bool is_is_inline
):
	return_type_(return_type),
	is_inline_(is_is_inline)
{
}

class_::conversion_function::conversion_function(conversion_function&& o):
	return_type_(std::move(o.return_type_)),
	is_inline_(o.is_inline_)
{
}

const type_shared_ptr_variant&
class_::conversion_function::return_type() const
{
	return return_type_;
}

bool
class_::conversion_function::is_inline() const
{
	return is_inline_;
}

bool
class_::conversion_function::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
class_::conversion_function::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
class_::conversion_function::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}

bool
operator==(const class_::conversion_function& lhs, const class_::conversion_function& rhs)
{
	return
		lhs.is_inline() == rhs.is_inline() &&
		lhs.return_type() == rhs.return_type()
	;
}

bool
operator!=(const class_::conversion_function& lhs, const class_::conversion_function& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

