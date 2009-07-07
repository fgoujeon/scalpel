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

#include "scope_cursor.hpp"

#include <iostream>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//
//scope_cursor
//

scope_cursor::scope_cursor()
{
}

void
scope_cursor::initialize(semantic_entities::scope& global_scope)
{
	scope_stack_.clear();
	scope_stack_.push_back(&global_scope);
}

scope_cursor::scope_const_iterator_range
scope_cursor::scope_stack() const
{
	return scope_stack_;
}

scope_cursor::scope_iterator_range
scope_cursor::scope_stack()
{
	return scope_stack_;
}

scope_cursor::scope_const_iterator_range
scope_cursor::global_scope_stack() const
{
	scope_const_iterator first = scope_stack_.begin();
	scope_const_iterator last = scope_stack_.begin(); //we only want the first item
	++last;

	scope_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return scope_const_iterator_range(const_indirect_first, const_indirect_last);
}

scope_cursor::scope_iterator_range
scope_cursor::global_scope_stack()
{
	scope_iterator first = scope_stack_.begin();
	scope_iterator last = scope_stack_.begin(); //we only want the first item
	++last;

	scope_indirect_iterator indirect_first(first), indirect_last(last);

	return scope_iterator_range(indirect_first, indirect_last);
}

semantic_entities::scope&
scope_cursor::global_scope()
{
	assert(!scope_stack_.empty());
	return *scope_stack_.front();
}

semantic_entities::scope&
scope_cursor::current_scope()
{
	assert(!scope_stack_.empty());
	return *scope_stack_.back();
}

void
scope_cursor::add_to_current_scope(semantic_entities::namespace_&& o)
{
	namespace_adder v(o);
	current_scope().accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::class_&& o)
{
	class_adder v(o);
	current_scope().accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::function&& o)
{
	function_adder v(o);
	current_scope().accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::statement_block&& o)
{
	statement_block_adder v(o);
	current_scope().accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::variable&& o)
{
	variable_adder v(o);
	current_scope().accept(v);
}

void
scope_cursor::enter_scope(semantic_entities::scope& a_scope)
{
	std::cout << "Entering " << a_scope.name() << "\n";
	scope_stack_.push_back(&a_scope);
}

void
scope_cursor::enter_last_added_scope()
{
	assert(!current_scope().scopes().empty());
	enter_scope(current_scope().scopes().back());
}

void
scope_cursor::leave_scope()
{
	std::cout << "Leaving " << current_scope().name() << "\n";
	scope_stack_.pop_back();
}


//
//scope_cursor::namespace_adder
//

scope_cursor::namespace_adder::namespace_adder(semantic_entities::namespace_&& o):
	o_(std::move(o))
{
}

void
scope_cursor::namespace_adder::visit(semantic_entities::namespace_& scope)
{
	scope.add(o_);
}

void
scope_cursor::namespace_adder::visit(semantic_entities::class_&)
{
	assert(false);
}

void
scope_cursor::namespace_adder::visit(semantic_entities::function&)
{
	assert(false);
}

void
scope_cursor::namespace_adder::visit(semantic_entities::statement_block&)
{
	assert(false);
}


//
//scope_cursor::class_adder
//

scope_cursor::class_adder::class_adder(semantic_entities::class_&& o):
	o_(std::move(o))
{
}

void
scope_cursor::class_adder::visit(semantic_entities::namespace_& scope)
{
	scope.add(o_);
}

void
scope_cursor::class_adder::visit(semantic_entities::class_& scope)
{
	scope.add(o_);
}

void
scope_cursor::class_adder::visit(semantic_entities::function&)
{
	assert(false);
}

void
scope_cursor::class_adder::visit(semantic_entities::statement_block&)
{
	assert(false);
}


//
//scope_cursor::function_adder
//

scope_cursor::function_adder::function_adder(semantic_entities::function&& o):
	o_(std::move(o))
{
}

void
scope_cursor::function_adder::visit(semantic_entities::namespace_& scope)
{
	scope.add(o_);
}

void
scope_cursor::function_adder::visit(semantic_entities::class_& scope)
{
	scope.add(o_);
}

void
scope_cursor::function_adder::visit(semantic_entities::function&)
{
	assert(false);
}

void
scope_cursor::function_adder::visit(semantic_entities::statement_block&)
{
	assert(false);
}


//
//scope_cursor::statement_block_adder
//

scope_cursor::statement_block_adder::statement_block_adder(semantic_entities::statement_block&& o):
	o_(std::move(o))
{
}

void
scope_cursor::statement_block_adder::visit(semantic_entities::namespace_&)
{
	assert(false);
}

void
scope_cursor::statement_block_adder::visit(semantic_entities::class_&)
{
	assert(false);
}

void
scope_cursor::statement_block_adder::visit(semantic_entities::function& scope)
{
	scope.add(o_);
}

void
scope_cursor::statement_block_adder::visit(semantic_entities::statement_block& scope)
{
	scope.add(o_);
}


//
//scope_cursor::variable_adder
//

scope_cursor::variable_adder::variable_adder(semantic_entities::variable&& o):
	o_(std::move(o))
{
}

void
scope_cursor::variable_adder::visit(semantic_entities::namespace_& scope)
{
	scope.add(o_);
}

void
scope_cursor::variable_adder::visit(semantic_entities::class_& scope)
{
	scope.add(o_);
}

void
scope_cursor::variable_adder::visit(semantic_entities::function& scope)
{
	scope.add(o_);
}

void
scope_cursor::variable_adder::visit(semantic_entities::statement_block& scope)
{
	scope.add(o_);
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

