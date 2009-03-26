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

#include "function.hpp"

#include <iostream>
#include <cassert>
#include "namespace_.hpp"
#include "class_.hpp"

namespace socoa { namespace cpp { namespace semantic_graph
{

function::function(const std::string& name):
    name_(name),
	enclosing_scope_(0)
{
}

const std::string&
function::get_name() const
{
    return name_;
}

bool
function::has_that_name(const std::string& name) const
{
    return name_ == name;
}

const std::string
function::get_full_name() const
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
function::is_a_type() const
{
    return true;
}

bool
function::is_global() const
{
    return false;
}

bool
function::has_enclosing_scope() const
{
    return enclosing_scope_;
}

scope&
function::get_enclosing_scope()
{
    return *enclosing_scope_;
}

const scope&
function::get_enclosing_scope() const
{
    return *enclosing_scope_;
}

void
function::set_enclosing_scope(class_& enclosing_scope)
{
    assert(!enclosing_scope_); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = &enclosing_scope;
}

void
function::set_enclosing_scope(namespace_& enclosing_scope)
{
    assert(!enclosing_scope_); //assert that member doesn't have any enclosing scope yet
    enclosing_scope_ = &enclosing_scope;
}

const std::vector<scope*>&
function::get_scopes() const
{
	return scopes_;
}

const std::vector<named_item*>&
function::get_named_items() const
{
	return named_items_;
}

}}} //namespace socoa::cpp::semantic_graph
