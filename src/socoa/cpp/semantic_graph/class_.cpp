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

#include "class_.hpp"

#include <iostream>
#include <cassert>
#include "namespace_.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

class_::class_(const std::string& name):
    name_(name)
{
	std::cout << "New class " << name << "\n";
}

class_::class_(class_&& c):
	scope_impl_(std::move(c.scope_impl_)),
	name_(std::move(c.name_)),
	classes_(std::move(c.classes_)),
	functions_(std::move(c.functions_)),
	members_(std::move(c.members_))
{
}

const class_&
class_::operator=(class_&& c)
{
	scope_impl_ = std::move(c.scope_impl_);
	name_ = std::move(c.name_);
	classes_ = std::move(c.classes_);
	functions_ = std::move(c.functions_);
	members_ = std::move(c.members_);

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

bool
class_::has_enclosing_scope() const
{
    return scope_impl_.has_enclosing_scope();
}

scope&
class_::enclosing_scope()
{
    return scope_impl_.enclosing_scope();
}

const scope&
class_::enclosing_scope() const
{
    return scope_impl_.enclosing_scope();
}

void
class_::enclosing_scope(class_& enclosing_scope)
{
    scope_impl_.enclosing_scope(enclosing_scope);
}

void
class_::enclosing_scope(namespace_& enclosing_scope)
{
    scope_impl_.enclosing_scope(enclosing_scope);
}

const std::list<class_::member_t>&
class_::members() const
{
    return members_;
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

void
class_::add(class_&& nested_class)
{
	classes_.push_back(std::move(nested_class));

	class_& member_ref = classes_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
class_::add(function&& member)
{
    functions_.push_back(std::move(member));

	function& member_ref = functions_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_scopes(member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

void
class_::add(variable&& member)
{
    variables_.push_back(std::move(member));

	variable& member_ref = variables_.back();

	member_ref.enclosing_scope(*this);

	members_.push_back(&member_ref);
	scope_impl_.add_to_named_entities(member_ref);
}

}}} //namespace socoa::cpp::semantic_graph
