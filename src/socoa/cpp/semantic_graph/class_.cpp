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
    name_(name),
	enclosing_scope_(0)
{
}

class_::class_(class_&& c):
	name_(std::move(c.name_)),
	enclosing_scope_(0),
	classes_(std::move(c.classes_)),
	functions_(std::move(c.functions_)),
	members_(std::move(c.members_)),
	scopes_(std::move(c.scopes_)),
	named_items_(std::move(c.named_items_))
{
	assert(!c.enclosing_scope_);
}

const class_&
class_::operator=(class_&& c)
{
	assert(!c.enclosing_scope_);

	name_ = std::move(c.name_);
	enclosing_scope_ = 0;
	classes_ = std::move(c.classes_);
	functions_ = std::move(c.functions_);
	members_ = std::move(c.members_);
	scopes_ = std::move(c.scopes_);
	named_items_ = std::move(c.named_items_);

	return *this;
}

void
class_::accept(scope_visitor& v)
{
	v.visit(*this);
}

const std::string&
class_::get_name() const
{
    return name_;
}

bool
class_::has_that_name(const std::string& name) const
{
    return name_ == name;
}

const std::string
class_::get_full_name() const
{
//    std::string full_name;
//
//    if(has_enclosing_scope() && !get_enclosing_scope()->is_global()) //don't add a leading "::"
//    {
//        full_name = get_enclosing_scope()->get_full_name() + "::";
//    }
//    full_name += name_;
//
//    return full_name;
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
    return enclosing_scope_;
}

scope&
class_::get_enclosing_scope()
{
    return *enclosing_scope_;
}

const scope&
class_::get_enclosing_scope() const
{
    return *enclosing_scope_;
}

void
class_::set_enclosing_scope(class_& enclosing_scope)
{
    assert(!enclosing_scope_); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = &enclosing_scope;
}

void
class_::set_enclosing_scope(namespace_& enclosing_scope)
{
    assert(!enclosing_scope_); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = &enclosing_scope;
}

void
class_::clear_enclosing_scope()
{
	enclosing_scope_ = 0;
}

const std::list<class_::member_t>&
class_::get_members() const
{
    return members_;
}

const std::list<scope*>&
class_::get_scopes() const
{
	return scopes_;
}

const std::list<named_item*>&
class_::get_named_items() const
{
	return named_items_;
}
/*
const std::list<std::shared_ptr<class_>>&
class_::get_classes() const
{
    return nested_classes_;
}
*/

void
class_::add(class_&& nested_class)
{
	classes_.push_back(std::move(nested_class));

	class_* member_ptr = &classes_.back();

	member_ptr->set_enclosing_scope(*this);

	members_.push_back(member_ptr);
	scopes_.push_back(member_ptr);
	named_items_.push_back(member_ptr);
}

void
class_::add(function&& member)
{
    functions_.push_back(std::move(member));

	function* member_ptr = &functions_.back();

	member_ptr->set_enclosing_scope(*this);

	members_.push_back(member_ptr);
	scopes_.push_back(member_ptr);
	named_items_.push_back(member_ptr);
}

/*
const std::list<base_specifier>&
class_::get_base_specifiers() const
{
    return base_specifiers_;
}

void
class_::add(const base_specifier& specifier)
{
    base_specifiers_.push_back(specifier);
}
*/

}}} //namespace socoa::cpp::semantic_graph
