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

#include <cassert>
#include <iostream>
#include "scope_cursor.h"

namespace socoa { namespace cpp
{

scope_cursor::scope_cursor(std::shared_ptr<program_tree::namespace_> global_namespace):
    global_namespace_(global_namespace),
    current_scope_(global_namespace)
{
}

void
scope_cursor::reset()
{
    enter_scope(global_namespace_);
    last_created_scope_.reset();
}

const std::shared_ptr<program_tree::named_scope>
scope_cursor::get_current_scope() const
{
    return current_scope_;
}

void
scope_cursor::enter_scope(std::shared_ptr<program_tree::named_scope> a_named_scope)
{
    current_scope_ = a_named_scope;

    std::string current_scope_name = current_scope_->get_full_name();
    std::cout << "entering in " << (current_scope_name == "" ? "global namespace" : current_scope_name) << std::endl;
}

void
scope_cursor::leave_current_scope()
{
    enter_scope(current_scope_->get_parent());
}

void
scope_cursor::set_last_created_scope(std::shared_ptr<program_tree::named_scope> a_named_scope)
{
    last_created_scope_ = a_named_scope;
}

void
scope_cursor::enter_last_created_scope()
{
    assert(last_created_scope_ && "no scope had been created yet");
    enter_scope(last_created_scope_);
    last_created_scope_.reset();
}

}} //namespace socoa::cpp
