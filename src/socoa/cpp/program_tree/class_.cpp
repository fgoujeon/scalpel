/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#include "class_.h"

#include <iostream>
#include <cassert>
#include "namespace_.h"

namespace socoa { namespace cpp { namespace program_tree
{

class_::class_(const std::string& name):
    name_(name)
{
    std::cout << "new class " << get_full_name() << std::endl;
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
    std::string full_name;

    if(has_enclosing_scope() && !get_enclosing_scope()->is_global()) //don't add a leading "::"
    {
        full_name = get_enclosing_scope()->get_full_name() + "::";
    }
    full_name += name_;

    return full_name;
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
    return !enclosing_scope_.expired();
}

std::shared_ptr<name_tree_composite>
class_::get_enclosing_scope()
{
    return enclosing_scope_.lock();
}

const std::shared_ptr<name_tree_composite>
class_::get_enclosing_scope() const
{
    return enclosing_scope_.lock();
}

void
class_::set_enclosing_scope(std::shared_ptr<class_> enclosing_scope)
{
    assert(enclosing_scope_.expired()); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = enclosing_scope;
}

void
class_::set_enclosing_scope(std::shared_ptr<namespace_> enclosing_scope)
{
    assert(enclosing_scope_.expired()); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = enclosing_scope;
}

const std::vector<std::shared_ptr<name_tree_component>>&
class_::get_members() const
{
    return members_;
}

const std::vector<std::shared_ptr<class_>>&
class_::get_classes() const
{
    return nested_classes_;
}

void
class_::add(std::shared_ptr<class_> nested_class)
{
    nested_classes_.push_back(nested_class);
    add_member(nested_class);
}

const std::vector<base_specifier>&
class_::get_base_specifiers() const
{
    return base_specifiers_;
}

void
class_::add(const base_specifier& specifier)
{
    base_specifiers_.push_back(specifier);
}

void
class_::add_member(std::shared_ptr<class_member> member)
{
    //tell member that 'this' is its enclosing scope
    member->set_enclosing_scope(shared_from_this());

    //add member to private container
    members_.push_back(member);
}

}}} //namespace socoa::cpp::program_tree
