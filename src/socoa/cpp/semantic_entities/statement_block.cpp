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

#include "statement_block.hpp"

#include <iostream>
#include <cassert>
#include <socoa/util/extern_strings.hpp>
#include "namespace_.hpp"
#include "class_.hpp"

namespace socoa { namespace cpp { namespace semantic_entities
{

statement_block::statement_block()
{
	std::cout << "New statement block\n";
}

statement_block::statement_block(statement_block&& o):
	scope_impl_(std::move(o.scope_impl_))
{
}

const statement_block&
statement_block::operator=(statement_block&& o)
{
	scope_impl_ = std::move(o.scope_impl_);

	return *this;
}

void
statement_block::accept(scope_visitor& v)
{
	v.visit(*this);
}

const std::string&
statement_block::name() const
{
    return util::extern_strings::empty;
}

bool
statement_block::is_a_type() const
{
    return false;
}

bool
statement_block::is_global() const
{
    return false;
}

bool
statement_block::has_enclosing_scope() const
{
    return scope_impl_.has_enclosing_scope();
}

scope&
statement_block::enclosing_scope()
{
    return scope_impl_.enclosing_scope();
}

const scope&
statement_block::enclosing_scope() const
{
    return scope_impl_.enclosing_scope();
}

void
statement_block::enclosing_scope(function& enclosing_scope)
{
    scope_impl_.enclosing_scope(enclosing_scope);
}

void
statement_block::enclosing_scope(statement_block& enclosing_scope)
{
    scope_impl_.enclosing_scope(enclosing_scope);
}

scope::scope_iterator_range
statement_block::scopes()
{
	return scope_impl_.scopes();
}

scope::scope_const_iterator_range
statement_block::scopes() const
{
	return scope_impl_.scopes();
}

scope::named_entity_iterator_range
statement_block::named_entities()
{
	return scope_impl_.named_entities();
}

scope::named_entity_const_iterator_range
statement_block::named_entities() const
{
	return scope_impl_.named_entities();
}

void
statement_block::add(statement_block&& o)
{
	statement_blocks_.push_back(std::move(o));

	statement_block& member_ref = statement_blocks_.back();

	member_ref.enclosing_scope(*this);

	scope_impl_.add_to_scopes(member_ref);
}

void
statement_block::add(variable&& v)
{
	variables_.push_back(std::move(v));
}

}}} //namespace socoa::cpp::semantic_entities
