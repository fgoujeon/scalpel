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

class_::class_()
{
    std::cout << "new anonymous class" << std::endl;
}

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

    if(has_parent() && !get_parent()->is_global()) //don't add a leading "::"
    {
        full_name = get_parent()->get_full_name() + "::";
    }
    full_name += name_;

    return full_name;
}

bool
class_::is_global() const
{
    return !has_parent();
}

bool
class_::has_parent() const
{
    return !parent_.expired();;
}

std::shared_ptr<named_scope>
class_::get_parent()
{
    return parent_.lock();
}

const std::shared_ptr<named_scope>
class_::get_parent() const
{
    return parent_.lock();
}

void
class_::set_parent(std::shared_ptr<class_> parent)
{
    assert(parent_.expired()); //assert that member doesn't have any parent yet
    parent_ = parent;
}

void
class_::set_parent(std::shared_ptr<namespace_> parent)
{
    assert(parent_.expired()); //assert that member doesn't have any parent yet
    parent_ = parent;
}

const std::vector<std::shared_ptr<class_member>>&
class_::get_members() const
{
    return members_;
}

const std::vector<std::shared_ptr<class_>>&
class_::get_classes() const
{
    return classes_;
}

void
class_::add(std::shared_ptr<class_> member)
{
    classes_.push_back(member);
    add_member(member);
}

void
class_::clear()
{
    members_.clear();
    classes_.clear();
}

void
class_::add_member(std::shared_ptr<class_member> member)
{
    //tell member that 'this' is its parent
    member->set_parent(shared_from_this());

    //add member to private container
    members_.push_back(member);
}

}}} //namespace socoa::cpp::program_tree
