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

#include "namespace_.h"

#include <iostream>
#include <cassert>

namespace socoa { namespace cpp { namespace program_tree
{

namespace_::namespace_()
{
    std::cout << "new anonymous namespace" << std::endl;
}

namespace_::namespace_(const std::string& name):
    name_(name)
{
    std::cout << "new namespace " << get_full_name() << std::endl;
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

    if(has_parent() && !get_parent()->is_global()) //don't add a leading "::"
    {
        full_name = get_parent()->get_full_name() + "::";
    }
    full_name += name_;

    return full_name;
}

bool
namespace_::is_global() const
{
    return !has_parent();
}

const std::vector<std::shared_ptr<namespace_member>>&
namespace_::get_members() const
{
    return members_;
}

template <>
const std::vector<std::shared_ptr<namespace_>>&
namespace_::get_members() const
{
    return namespaces_;
}

template <>
const std::vector<std::shared_ptr<class_>>&
namespace_::get_members() const
{
    return classes_;
}

const std::vector<std::shared_ptr<namespace_>>&
namespace_::get_namespaces() const
{
    return namespaces_;
}

const std::vector<std::shared_ptr<class_>>&
namespace_::get_classes() const
{
    return classes_;
}

void
namespace_::add(std::shared_ptr<namespace_> member)
{
    namespaces_.push_back(member);
    add_member(member);
}

void
namespace_::add(std::shared_ptr<class_> member)
{
    classes_.push_back(member);
    add_member(member);
}

void
namespace_::clear()
{
    members_.clear();
    namespaces_.clear();
    classes_.clear();
}

void
namespace_::add_member(std::shared_ptr<namespace_member> member)
{
    //tell member that 'this' is its parent
    member->set_parent(shared_from_this());

    //add member to private container
    members_.push_back(member);
}

}}} //namespace socoa::cpp::program_tree
