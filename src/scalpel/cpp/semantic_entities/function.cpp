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

function::function(const std::string& name, std::unique_ptr<type> return_type):
    name_(name),
	return_type_(std::move(return_type))
{
	std::cout << "New function " << name << "\n";
}

function::function(function&& f):
	scope_impl_(std::move(f.scope_impl_)),
	name_(std::move(f.name_)),
	statement_block_(std::move(f.statement_block_)),
	return_type_(std::move(f.return_type_))
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

const type&
function::return_type() const
{
	return *return_type_;
}

}}} //namespace scalpel::cpp::semantic_entities
