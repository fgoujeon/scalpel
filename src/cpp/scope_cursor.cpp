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

#include <socoa/cpp/scope_cursor.h>

#include <cassert>
#include <iostream>

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
    last_encountered_scope_header_scope_.reset();
}

const std::shared_ptr<program_tree::name_tree_composite>
scope_cursor::get_current_scope() const
{
    return current_scope_;
}

void
scope_cursor::enter_scope(std::shared_ptr<program_tree::name_tree_composite> scope)
{
    current_scope_ = scope;

    std::string current_scope_name = current_scope_->get_full_name();
    std::cout << "entering in " << (current_scope_name == "" ? "global namespace" : current_scope_name) << std::endl;
}

void
scope_cursor::leave_current_scope()
{
    enter_scope(current_scope_->get_enclosing_scope());
}

void
scope_cursor::set_last_encountered_scope_header_scope(std::shared_ptr<program_tree::name_tree_composite> scope)
{
    last_encountered_scope_header_scope_ = scope;
}

void
scope_cursor::enter_last_encountered_scope_header_scope()
{
    assert(last_encountered_scope_header_scope_ && "no scope header had been encountered yet");
    enter_scope(last_encountered_scope_header_scope_);
    last_encountered_scope_header_scope_.reset();
}

}} //namespace socoa::cpp
