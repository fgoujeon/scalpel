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

scope_cursor::scope_cursor():
	global_scope_(0),
	current_scope_(0),
	last_added_scope_(0)
{
}

void
scope_cursor::initialize(semantic_entities::scope& a_scope)
{
	global_scope_ = &a_scope;
	current_scope_ = &a_scope;
}

semantic_entities::scope&
scope_cursor::get_global_scope()
{
	assert(global_scope_);
	return *global_scope_;
}

semantic_entities::scope&
scope_cursor::get_current_scope()
{
	assert(current_scope_);
	return *current_scope_;
}

void
scope_cursor::add_to_current_scope(semantic_entities::namespace_&& o)
{
	namespace_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::class_&& o)
{
	class_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::function&& o)
{
	function_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::statement_block&& o)
{
	statement_block_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_entities::variable&& o)
{
	variable_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::enter_scope(semantic_entities::scope& a_scope)
{
	std::cout << "Entering " << a_scope.name() << "\n";
	current_scope_ = &a_scope;
}

void
scope_cursor::enter_last_added_scope()
{
	assert(!current_scope_->scopes().empty());
	enter_scope(current_scope_->scopes().back());
}

void
scope_cursor::leave_scope()
{
	assert(current_scope_->has_enclosing_scope());
	std::cout << "Leaving " << current_scope_->name() << "\n";
	current_scope_ = &current_scope_->enclosing_scope();
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

