/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "namespace_.hpp"

#include <iostream>
#include <cassert>

namespace socoa { namespace cpp { namespace semantic_nodes
{

namespace_::namespace_()
{
}

namespace_::namespace_(const std::string& name):
    name_(name)
{
	std::cout << "New namespace " << name << "\n";
}

namespace_::namespace_(namespace_&& n):
	scope_impl_(std::move(n.scope_impl_)),
	name_(std::move(n.name_)),
	namespaces_(std::move(n.namespaces_)),
	classes_(std::move(n.classes_)),
	functions_(std::move(n.functions_)),
    members_(std::move(n.members_))
{
}

const namespace_&
namespace_::operator=(namespace_&& n)
{
	scope_impl_ = std::move(n.scope_impl_);
	name_ = std::move(n.name_);
	namespaces_ = std::move(n.namespaces_);
	classes_ = std::move(n.classes_);
	functions_ = std::move(n.functions_);
    members_ = std::move(n.members_);

	return *this;
}

void
namespace_::accept(scope_visitor& v)
{
	v.visit(*this);
}

const std::string&
namespace_::name() const
{
    return name_;
}

bool
namespace_::is_a_type() const
{
    return false;
}

bool
namespace_::is_global() const
{
    return !has_enclosing_scope();
}

bool
namespace_::has_enclosing_scope() const
{
    return scope_impl_.has_enclosing_scope();
}

scope&
namespace_::enclosing_scope()
{
    return scope_impl_.enclosing_scope();
}

const scope&
namespace_::enclosing_scope() const
{
    return scope_impl_.enclosing_scope();
}

void
namespace_::enclosing_scope(namespace_& enclosing_scope)
{
	return scope_impl_.enclosing_scope(enclosing_scope);
}

const std::list<namespace_::member_t>&
namespace_::members() const
{
    return members_;
}

scope::scope_iterator_range
namespace_::scopes()
{
	return scope_impl_.scopes();
}

scope::scope_const_iterator_range
namespace_::scopes() const
{
	return scope_impl_.scopes();
}

scope::named_entity_iterator_range
namespace_::named_entities()
{
	return scope_impl_.named_entities();
}

scope::named_entity_const_iterator_range
namespace_::named_entities() const
{
	return scope_impl_.named_entities();
}

void
namespace_::add(namespace_&& member)
{
    namespaces_.push_back(std::move(member));

	namespace_& member_ref = namespaces_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
namespace_::add(class_&& member)
{
    classes_.push_back(std::move(member));

	class_& member_ref = classes_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
namespace_::add(function&& member)
{
    functions_.push_back(std::move(member));

	function& member_ref = functions_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
namespace_::add(variable&& member)
{
    variables_.push_back(std::move(member));

	variable& member_ref = variables_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

}}} //namespace socoa::cpp::semantic_nodes