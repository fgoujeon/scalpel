/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "function.hpp"

#include <iostream>
#include <cassert>
#include "namespace_.hpp"
#include "class_.hpp"

namespace scalpel { namespace cpp { namespace semantic_entities
{

function::function(const std::string& name):
    name_(name)
{
	std::cout << "New function " << name << "\n";
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
function::name() const
{
    return name_;
}

bool
function::is_a_type() const
{
    return false;
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
function::enclosing_scope()
{
    return scope_impl_.enclosing_scope();
}

const scope&
function::enclosing_scope() const
{
    return scope_impl_.enclosing_scope();
}

void
function::enclosing_scope(class_& enclosing_scope)
{
    scope_impl_.enclosing_scope(enclosing_scope);
}

void
function::enclosing_scope(namespace_& enclosing_scope)
{
    scope_impl_.enclosing_scope(enclosing_scope);
}

scope::scope_iterator_range
function::scopes()
{
	return scope_impl_.scopes();
}

scope::scope_const_iterator_range
function::scopes() const
{
	return scope_impl_.scopes();
}

scope::named_entity_iterator_range
function::named_entities()
{
	return scope_impl_.named_entities();
}

scope::named_entity_const_iterator_range
function::named_entities() const
{
	return scope_impl_.named_entities();
}

void
function::add(statement_block&& o)
{
	statement_blocks_.push_back(std::move(o));

	statement_block& member_ref = statement_blocks_.back();

	member_ref.enclosing_scope(*this);

	scope_impl_.add_to_scopes(member_ref);
}

void
function::add(variable&& v)
{
	variables_.push_back(std::move(v));

	variable& member_ref = variables_.back();

	member_ref.enclosing_scope(*this);

	scope_impl_.add_to_named_entities(member_ref);
}

}}} //namespace scalpel::cpp::semantic_entities
