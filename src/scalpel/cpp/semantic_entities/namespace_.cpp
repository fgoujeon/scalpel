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

#include "namespace_.hpp"
#include <scalpel/utility/are_pointed_objects_equal.hpp>

namespace scalpel { namespace cpp { namespace semantic_entities
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    name_(name)
{
}

std::shared_ptr<namespace_>
namespace_::make_shared()
{
	namespace_* ptr = new namespace_();
	return std::shared_ptr<namespace_>(ptr);
}

std::shared_ptr<namespace_>
namespace_::make_shared(const std::string& name)
{
	namespace_* ptr = new namespace_(name);
	return std::shared_ptr<namespace_>(ptr);
}

const std::string&
namespace_::name() const
{
    return name_;
}

bool
namespace_::has_declarative_region() const
{
	return declarative_region_member_impl_.has_declarative_region();
}

declarative_region_shared_ptr_variant
namespace_::declarative_region() const
{
	return declarative_region_member_impl_.declarative_region();
}

void
namespace_::declarative_region(const declarative_region_shared_ptr_variant& decl_region)
{
	declarative_region_member_impl_.declarative_region(decl_region);
}

bool
namespace_::is_open_to_outside() const
{
	return true;
}

const namespace_::declarative_regions_t&
namespace_::declarative_regions()
{
	return declarative_regions_;
}

namespace_::namespaces_t::range
namespace_::namespaces()
{
	return namespaces_;
}

const namespace_::namespaces_t&
namespace_::namespaces() const
{
	return namespaces_;
}

namespace_::classes_t::range
namespace_::classes()
{
	return classes_;
}

const namespace_::classes_t&
namespace_::classes() const
{
	return classes_;
}

namespace_::simple_functions_t::range
namespace_::simple_functions()
{
	return simple_functions_;
}

const namespace_::simple_functions_t&
namespace_::simple_functions() const
{
	return simple_functions_;
}

namespace_::operator_functions_t::range
namespace_::operator_functions()
{
	return operator_functions_;
}

const namespace_::operator_functions_t&
namespace_::operator_functions() const
{
	return operator_functions_;
}

namespace_::variables_t::range
namespace_::variables()
{
	return variables_;
}

const namespace_::variables_t&
namespace_::variables() const
{
	return variables_;
}

void
namespace_::add(std::shared_ptr<namespace_> member)
{
	member->declarative_region(shared_from_this());
    namespaces_.push_back(member);
	declarative_regions_.push_back(member);
}

void
namespace_::add(std::shared_ptr<class_> member)
{
	member->declarative_region(shared_from_this());
    classes_.push_back(member);
	declarative_regions_.push_back(member);
}

void
namespace_::add(std::shared_ptr<simple_function> member)
{
	member->declarative_region(shared_from_this());
    simple_functions_.push_back(member);
}

void
namespace_::add(std::shared_ptr<operator_function> member)
{
	member->declarative_region(shared_from_this());
    operator_functions_.push_back(member);
}

void
namespace_::add(std::shared_ptr<variable> member)
{
	member->declarative_region(shared_from_this());
    variables_.push_back(member);
}

bool
operator==(const namespace_& lhs, const namespace_& rhs)
{
	return
		lhs.name() == rhs.name() &&
		are_pointed_objects_equal(lhs.namespaces(), rhs.namespaces()) &&
		are_pointed_objects_equal(lhs.classes(), rhs.classes()) &&
		are_pointed_objects_equal(lhs.simple_functions(), rhs.simple_functions()) &&
		are_pointed_objects_equal(lhs.operator_functions(), rhs.operator_functions()) &&
		are_pointed_objects_equal(lhs.variables(), rhs.variables())
	;
}

bool
operator!=(const namespace_& lhs, const namespace_& rhs)
{
	return !operator==(lhs, rhs);
}

}}} //namespace scalpel::cpp::semantic_entities

