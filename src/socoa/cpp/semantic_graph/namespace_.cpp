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

namespace socoa { namespace cpp { namespace semantic_graph
{

namespace_::namespace_():
	enclosing_scope_(0)
{
}

namespace_::namespace_(const std::string& name):
    name_(name),
	enclosing_scope_(0)
{
}

namespace_::namespace_(namespace_&& n):
	name_(std::move(n.name_)),
	enclosing_scope_(0),
	namespaces_(std::move(n.namespaces_)),
	classes_(std::move(n.classes_)),
	functions_(std::move(n.functions_)),
    members_(std::move(n.members_)),
    scopes_(std::move(n.scopes_)),
    named_items_(std::move(n.named_items_))
{
	assert(!n.enclosing_scope_);
}

const namespace_&
namespace_::operator=(namespace_&& n)
{
	assert(!n.enclosing_scope_);

	name_ = std::move(n.name_);
	enclosing_scope_ = 0;
	namespaces_ = std::move(n.namespaces_);
	classes_ = std::move(n.classes_);
	functions_ = std::move(n.functions_);
    members_ = std::move(n.members_);
    scopes_ = std::move(n.scopes_);
    named_items_ = std::move(n.named_items_);

	return *this;
}

void
namespace_::accept(scope_visitor& v)
{
	v.visit(*this);
}

const std::string&
namespace_::get_name() const
{
    return name_;
}

bool
namespace_::has_that_name(const std::string& name) const
{
    return name_ == name;
}

const std::string
namespace_::get_full_name() const
{
    std::string full_name;

//    if(has_enclosing_scope() && !get_enclosing_scope()->is_global()) //don't add a leading "::"
//    {
//        full_name = get_enclosing_scope()->get_full_name() + "::";
//    }
//    full_name += name_;

    return full_name;
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
    return enclosing_scope_;
}

scope&
namespace_::get_enclosing_scope()
{
    return *enclosing_scope_;
}

const scope&
namespace_::get_enclosing_scope() const
{
    return *enclosing_scope_;
}

void
namespace_::set_enclosing_scope(namespace_& enclosing_scope)
{
    assert(!enclosing_scope_); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = &enclosing_scope;
}

void
namespace_::clear_enclosing_scope()
{
	enclosing_scope_ = 0;
}

const std::list<namespace_::member_t>&
namespace_::get_members() const
{
    return members_;
}

const std::list<scope*>&
namespace_::get_scopes() const
{
	return scopes_;
}

const std::list<named_item*>&
namespace_::get_named_items() const
{
	return named_items_;
}

void
namespace_::add(namespace_&& member)
{
    namespaces_.push_back(std::move(member));

	namespace_* member_ptr = &namespaces_.back();

	member_ptr->set_enclosing_scope(*this);

	members_.push_back(member_ptr);
	scopes_.push_back(member_ptr);
	named_items_.push_back(member_ptr);
}

void
namespace_::add(class_&& member)
{
    classes_.push_back(std::move(member));

	class_* member_ptr = &classes_.back();

	member_ptr->set_enclosing_scope(*this);

	members_.push_back(member_ptr);
	scopes_.push_back(member_ptr);
	named_items_.push_back(member_ptr);
}

void
namespace_::add(function&& member)
{
    functions_.push_back(std::move(member));

	function* member_ptr = &functions_.back();

	member_ptr->set_enclosing_scope(*this);

	members_.push_back(member_ptr);
	scopes_.push_back(member_ptr);
	named_items_.push_back(member_ptr);
}

}}} //namespace socoa::cpp::semantic_graph
