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
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name)
{
}

class_::class_(class_&& rhs):
	name_(std::move(rhs.name_)),
	nested_classes_(std::move(rhs.nested_classes_)),
	constructors_(std::move(rhs.constructors_)),
	destructor_(std::move(rhs.destructor_)),
	simple_functions_(std::move(rhs.simple_functions_)),
	operator_functions_(std::move(rhs.operator_functions_)),
	conversion_functions_(std::move(rhs.conversion_functions_)),
	variables_(std::move(rhs.variables_))
{
}

const class_&
class_::operator=(class_&& rhs)
{
	name_ = std::move(rhs.name_);
	nested_classes_ = std::move(rhs.nested_classes_);
	constructors_ = std::move(rhs.constructors_);
	destructor_ = std::move(rhs.destructor_);
	simple_functions_ = std::move(rhs.simple_functions_);
	operator_functions_ = std::move(rhs.operator_functions_);
	conversion_functions_ = std::move(rhs.conversion_functions_);
	variables_ = std::move(rhs.variables_);

	return *this;
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

bool
class_::is_open_to_outside() const
{
	return true;
}

const class_::declarative_region_shared_ptr_variants_t&
class_::declarative_regions()
{
	return declarative_regions_;
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
	if(!destructor_)
	{
		class_& mutable_this = const_cast<class_&>(*this);
		mutable_this.reset_destructor();
		//Since the implicitly declared destructor can't be set in class_'s
		//constructor (shared_from_this() can't be called from it), it is set
		//here.
	}
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
class_::add(std::shared_ptr<class_> member, const access acc)
{
	member->declarative_region(shared_from_this());
	nested_classes_.push_back(member);
	declarative_regions_.push_back(member);

	member_access_[std::shared_ptr<const class_>(member)] = acc;
}

void
class_::add(std::shared_ptr<constructor> member, const access acc)
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
class_::add
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
class_::add
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
class_::add
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
class_::add(std::shared_ptr<variable> member, const access acc)
{
	member->declarative_region(shared_from_this());
    variables_.push_back(member);

	std::shared_ptr<const variable> const_member(member);
	member_access_[const_member] = acc;
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



class_::constructor::constructor
(
	parameters_t&& parameters,
	const bool is_is_inline,
	const bool is_is_explicit
):
	impl_
	(
		"_",
		std::shared_ptr<const built_in_type>(&built_in_type::void_, scalpel::utility::null_deleter()),
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



class_::conversion_function::conversion_function
(
	std::shared_ptr<const type> return_type,
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

std::shared_ptr<const type>
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

}}} //namespace scalpel::cpp::semantic_entities

