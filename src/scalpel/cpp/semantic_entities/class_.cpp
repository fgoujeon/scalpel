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
	//implicitly declared destructor
	set_destructor
	(
		std::make_shared<destructor>(false),
		access::PUBLIC,
		false,
		false
	);
}

class_::class_(class_&& c):
	name_(std::move(c.name_)),
	named_entities_(std::move(c.named_entities_)),
	named_declarative_regions_(std::move(c.named_declarative_regions_)),
	nested_classes_(std::move(c.nested_classes_)),
	constructors_(std::move(c.constructors_)),
	destructor_(std::move(c.destructor_)),
	simple_functions_(std::move(c.simple_functions_)),
	operator_functions_(std::move(c.operator_functions_)),
	conversion_functions_(std::move(c.conversion_functions_)),
	variables_(std::move(c.variables_))
{
}

const class_&
class_::operator=(class_&& c)
{
	name_ = std::move(c.name_);
	named_entities_ = std::move(c.named_entities_);
	named_declarative_regions_ = std::move(c.named_declarative_regions_);
	nested_classes_ = std::move(c.nested_classes_);
	constructors_ = std::move(c.constructors_);
	destructor_ = std::move(c.destructor_);
	simple_functions_ = std::move(c.simple_functions_);
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
class_::is_global() const
{
    return false;
}

bool
class_::is_open_to_outside() const
{
	return true;
}

class_::named_entities_t::range
class_::named_entities()
{
	return named_entities_;
}

const class_::named_entities_t&
class_::named_entities() const
{
	return named_entities_;
}

class_::named_declarative_regions_t::range
class_::named_declarative_regions()
{
	return named_declarative_regions_;
}

const class_::named_declarative_regions_t&
class_::named_declarative_regions() const
{
	return named_declarative_regions_;
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
	bool virtual_specified
)
{
	base_classes_.push_back(base_class);

	switch(acc)
	{
		case PUBLIC:
			public_base_classes_.push_back(base_class);
			break;
		case PROTECTED:
			protected_base_classes_.push_back(base_class);
			break;
		case PRIVATE:
			private_base_classes_.push_back(base_class);
			break;
	}
	if(virtual_specified) virtual_base_classes_.push_back(base_class);
}

void
class_::add(std::shared_ptr<class_> member, const access acc)
{
	nested_classes_.push_back(member);
	named_entities_.push_back(member);
	named_declarative_regions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
}

void
class_::add(std::shared_ptr<constructor> member, const access acc)
{
    constructors_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
}

void
class_::set_destructor
(
	std::shared_ptr<destructor> member,
	const access acc,
	const bool virtual_specified,
	const bool pure_specified
)
{
	destructor_ = member;

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
	if(virtual_specified) virtual_member_functions_.push_back(member);
	if(pure_specified) pure_member_functions_.push_back(member);
}

void
class_::add
(
	std::shared_ptr<simple_function> member,
	const access acc,
	const bool const_qualified,
	const bool volatile_qualified,
	const bool virtual_specified,
	const bool pure_specified
)
{
    simple_functions_.push_back(member);
	named_entities_.push_back(member);
	named_declarative_regions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
	if(const_qualified) const_member_functions_.push_back(member);
	if(volatile_qualified) volatile_member_functions_.push_back(member);
	if(virtual_specified) virtual_member_functions_.push_back(member);
	if(pure_specified) pure_member_functions_.push_back(member);
}

void
class_::add
(
	std::shared_ptr<operator_function> member,
	const access acc,
	const bool const_qualified,
	const bool volatile_qualified,
	const bool virtual_specified,
	const bool pure_specified
)
{
    operator_functions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
	if(const_qualified) const_member_functions_.push_back(member);
	if(volatile_qualified) volatile_member_functions_.push_back(member);
	if(virtual_specified) virtual_member_functions_.push_back(member);
	if(pure_specified) pure_member_functions_.push_back(member);
}

void
class_::add
(
	std::shared_ptr<conversion_function> member,
	const access acc,
	const bool const_qualified,
	const bool volatile_qualified,
	const bool virtual_specified,
	const bool pure_specified
)
{
    conversion_functions_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
	if(const_qualified) const_member_functions_.push_back(member);
	if(volatile_qualified) volatile_member_functions_.push_back(member);
	if(virtual_specified) virtual_member_functions_.push_back(member);
	if(pure_specified) pure_member_functions_.push_back(member);
}

void
class_::add(std::shared_ptr<variable> member, const access acc)
{
    variables_.push_back(member);
	named_entities_.push_back(member);

	switch(acc)
	{
		case PUBLIC:
			public_members_.push_back(member);
			break;
		case PROTECTED:
			protected_members_.push_back(member);
			break;
		case PRIVATE:
			private_members_.push_back(member);
			break;
	}
}



class_::constructor::constructor
(
	parameters_t&& parameters,
	const bool is_inline_specified,
	const bool is_explicit_specified
):
	impl_
	(
		"_",
		std::shared_ptr<const built_in_type>(&built_in_type::void_, scalpel::utility::null_deleter()),
		std::move(parameters),
		is_inline_specified,
		false
	),
	explicit_specified_(is_explicit_specified)
{
}

class_::constructor::constructor(constructor&& o):
	impl_(std::move(o.impl_)),
	explicit_specified_(o.explicit_specified_)
{
}

const class_::constructor::parameters_t&
class_::constructor::parameters() const
{
	return impl_.parameters();
}

bool
class_::constructor::inline_specified() const
{
	return impl_.inline_specified();
}

bool
class_::constructor::explicit_specified() const
{
	return explicit_specified_;
}



class_::destructor::destructor
(
	const bool is_inline_specified
):
	inline_specified_(is_inline_specified)
{
}

class_::destructor::destructor(destructor&& o):
	inline_specified_(o.inline_specified_)
{
}

bool
class_::destructor::inline_specified() const
{
	return inline_specified_;
}



class_::conversion_function::conversion_function
(
	std::shared_ptr<const type> return_type,
	const bool is_inline_specified
):
	return_type_(return_type),
	inline_specified_(is_inline_specified)
{
}

class_::conversion_function::conversion_function(conversion_function&& o):
	return_type_(std::move(o.return_type_)),
	inline_specified_(o.inline_specified_)
{
}

std::shared_ptr<const type>
class_::conversion_function::return_type() const
{
	return return_type_;
}

bool
class_::conversion_function::inline_specified() const
{
	return inline_specified_;
}

}}} //namespace scalpel::cpp::semantic_entities

