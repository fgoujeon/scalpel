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
namespace_::has_enclosing_declarative_region() const
{
	return !enclosing_declarative_region_.expired();
}

std::shared_ptr<namespace_>
namespace_::enclosing_declarative_region()
{
	return std::shared_ptr<namespace_>(enclosing_declarative_region_);
}

std::shared_ptr<const namespace_>
namespace_::enclosing_declarative_region() const
{
	return std::shared_ptr<const namespace_>(enclosing_declarative_region_);
}

void
namespace_::enclosing_declarative_region(std::shared_ptr<namespace_> enclosing_declarative_region)
{
	enclosing_declarative_region_ = enclosing_declarative_region;
}

const namespace_::open_declarative_region_shared_ptr_variants_t&
namespace_::open_declarative_regions()
{
	return open_declarative_regions_;
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

namespace_::typedefs_t::range
namespace_::typedefs()
{
	return typedefs_;
}

const namespace_::typedefs_t&
namespace_::typedefs() const
{
	return typedefs_;
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

namespace_::namespace_aliases_t::range
namespace_::namespace_aliases()
{
	return namespace_aliases_;
}

const namespace_::namespace_aliases_t&
namespace_::namespace_aliases() const
{
	return namespace_aliases_;
}

const namespace_::weak_namespaces_t&
namespace_::using_directive_namespaces() const
{
	return using_directive_namespaces_;
}

void
namespace_::add_member(std::shared_ptr<namespace_> member)
{
	member->enclosing_declarative_region(shared_from_this());
    namespaces_.push_back(member);
	open_declarative_regions_.push_back(member);
}

void
namespace_::add_member(std::shared_ptr<class_> member)
{
	member->enclosing_declarative_region(shared_from_this());
    classes_.push_back(member);
	open_declarative_regions_.push_back(member);
}

void
namespace_::add_member(std::shared_ptr<typedef_> member)
{
	member->enclosing_declarative_region(shared_from_this());
    typedefs_.push_back(member);
}

void
namespace_::add_member(std::shared_ptr<simple_function> member)
{
	member->enclosing_declarative_region(shared_from_this());
    simple_functions_.push_back(member);
}

void
namespace_::add_member(std::shared_ptr<operator_function> member)
{
	member->enclosing_declarative_region(shared_from_this());
    operator_functions_.push_back(member);
}

void
namespace_::add_member(std::shared_ptr<variable> member)
{
	member->enclosing_declarative_region(shared_from_this());
    variables_.push_back(member);
}

void
namespace_::add_member(std::shared_ptr<namespace_alias> member)
{
    namespace_aliases_.push_back(member);
	open_declarative_regions_.push_back(member);
}

void
namespace_::add_using_directive_namespace(std::shared_ptr<namespace_> n)
{
	using_directive_namespaces_.push_back(n);
}

}}} //namespace scalpel::cpp::semantic_entities

