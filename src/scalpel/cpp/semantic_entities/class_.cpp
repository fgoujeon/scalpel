/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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
#include "typedef_.hpp"
#include "functions.hpp"
#include "variable.hpp"
#include "type_variant.hpp"
#include <memory>

namespace scalpel { namespace cpp { namespace semantic_entities
{

class_::class_(const std::string& name):
    name_(name),
	complete_(false)
{
	reset_destructor();
}

const std::string&
class_::name() const
{
    return name_;
}

bool
class_::has_enclosing_declarative_region() const
{
	return declarative_region_member_impl_.has_enclosing_declarative_region();
}

declarative_region_ptr_variant
class_::enclosing_declarative_region() const
{
	return declarative_region_member_impl_.enclosing_declarative_region();
}

void
class_::enclosing_declarative_region(const declarative_region_ptr_variant& decl_region)
{
	declarative_region_member_impl_.enclosing_declarative_region(decl_region);
}

const class_::open_declarative_region_ptr_variants_t&
class_::open_declarative_regions()
{
	return open_declarative_regions_;
}

const class_::class_ptrs_t&
class_::base_classes()
{
	return base_classes_;
}

const class_::class_ptrs_t&
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

class_::enums_t::range
class_::enums()
{
	return enums_;
}

const class_::enums_t&
class_::enums() const
{
	return enums_;
}

class_::typedefs_t::range
class_::typedefs()
{
	return typedefs_;
}

const class_::typedefs_t&
class_::typedefs() const
{
	return typedefs_;
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

destructor&
class_::get_destructor()
{
	return *destructor_;
}

const destructor&
class_::get_destructor() const
{
	return *destructor_;
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
	class_& base_class,
	const access acc,
	bool is_virtual
)
{
	base_classes_.push_back(&base_class);

	base_class_access_[&base_class] = acc;
	if(is_virtual) virtual_base_classes_.push_back(&base_class);
}

void
class_::add_member(std::unique_ptr<class_>&& member, const access acc)
{
	member->enclosing_declarative_region(this);

	open_declarative_regions_.push_back(member.get());
	member_access_[static_cast<const class_*>(member.get())] = acc;

	nested_classes_.push_back(std::move(member));
}

void
class_::add_member(std::unique_ptr<enum_>&& member, const access acc)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const enum_*>(member.get())] = acc;

    enums_.push_back(std::move(member));
}

void
class_::add_member(std::unique_ptr<typedef_>&& member, const access acc)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const typedef_*>(member.get())] = acc;

    typedefs_.push_back(std::move(member));
}

void
class_::add_member(std::unique_ptr<constructor>&& member, const access acc)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const constructor*>(member.get())] = acc;

    constructors_.push_back(std::move(member));
}

void
class_::set_destructor
(
	std::unique_ptr<destructor>&& member,
	const access acc
)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const destructor*>(member.get())] = acc;

	destructor_ = std::move(member);
}

void
class_::reset_destructor()
{
	set_destructor
	(
		std::unique_ptr<destructor>(new destructor(false)),
		access::PUBLIC
	);
}

void
class_::add_member
(
	std::unique_ptr<simple_member_function>&& member,
	const access acc
)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const simple_member_function*>(member.get())] = acc;

    simple_functions_.push_back(std::move(member));
}

void
class_::add_member
(
	std::unique_ptr<operator_member_function>&& member,
	const access acc
)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const operator_member_function*>(member.get())] = acc;

    operator_functions_.push_back(std::move(member));
}

void
class_::add_member
(
	std::unique_ptr<conversion_function>&& member,
	const access acc
)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const conversion_function*>(member.get())] = acc;

    conversion_functions_.push_back(std::move(member));
}

void
class_::add_member
(
	std::unique_ptr<variable>&& member,
	const access acc,
	const bool is_mutable
)
{
	member->enclosing_declarative_region(this);

	member_access_[static_cast<const variable*>(member.get())] = acc;
	if(is_mutable) mutable_member_variables_.push_back(member.get());

    variables_.push_back(std::move(member));
}

class_::access
class_::base_class_access(const class_& base_class) const
{
	auto it = base_class_access_.find(&base_class);
	if(it != base_class_access_.end())
		return it->second;
	else
		throw std::runtime_error("The given entity is not a base class of that class.");
}

bool
class_::is_virtual_base_class(const class_& base_class) const
{
	return std::find
	(
		virtual_base_classes_.begin(),
		virtual_base_classes_.end(),
		&base_class
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
class_::is_mutable_member_variable(const variable& member) const
{
	return std::find
	(
		mutable_member_variables_.begin(),
		mutable_member_variables_.end(),
		&member
	) != mutable_member_variables_.end();
}

}}} //namespace scalpel::cpp::semantic_entities

