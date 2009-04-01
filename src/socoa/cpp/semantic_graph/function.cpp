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
    name_(name)
{
}

function::function(function&& f):
	scope_impl_(std::move(f.scope_impl_)),
	name_(std::move(f.name_))
{
}

const function&
function::operator=(function&& f)
{
	scope_impl_ = std::move(f.scope_impl_);
	name_ = std::move(f.name_);

	return *this;
}

void
function::accept(scope_visitor& v)
{
	v.visit(*this);
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
    return scope_impl_.has_enclosing_scope();
}

scope&
function::get_enclosing_scope()
{
    return scope_impl_.get_enclosing_scope();
}

const scope&
function::get_enclosing_scope() const
{
    return scope_impl_.get_enclosing_scope();
}

void
function::set_enclosing_scope(class_& enclosing_scope)
{
    scope_impl_.set_enclosing_scope(enclosing_scope);
}

void
function::set_enclosing_scope(namespace_& enclosing_scope)
{
    scope_impl_.set_enclosing_scope(enclosing_scope);
}

scope::scope_const_iterator_range
function::get_scopes() const
{
	return scope_impl_.get_scopes();
}

const std::list<named_item*>&
function::get_named_items() const
{
	return scope_impl_.get_named_items();
}

}}} //namespace socoa::cpp::semantic_graph
