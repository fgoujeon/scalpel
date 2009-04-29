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

#include "scope_cursor.hpp"

namespace socoa { namespace cpp { namespace detail { namespace semantic_analysis
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
scope_cursor::initialize(semantic_nodes::scope& a_scope)
{
	global_scope_ = &a_scope;
	current_scope_ = &a_scope;
}

semantic_nodes::scope&
scope_cursor::get_global_scope()
{
	assert(global_scope_);
	return *global_scope_;
}

semantic_nodes::scope&
scope_cursor::get_current_scope()
{
	assert(current_scope_);
	return *current_scope_;
}

void
scope_cursor::add_to_current_scope(semantic_nodes::namespace_&& o)
{
	namespace_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_nodes::class_&& o)
{
	class_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_nodes::function&& o)
{
	function_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_current_scope(semantic_nodes::variable&& o)
{
	variable_adder v(o);
	current_scope_->accept(v);
}

void
scope_cursor::enter_last_added_scope()
{
	assert(!current_scope_->scopes().empty());
	current_scope_ = &current_scope_->scopes().back();
}

void
scope_cursor::leave_scope()
{
	assert(current_scope_->has_enclosing_scope());
	current_scope_ = &current_scope_->enclosing_scope();
}


//
//scope_cursor::namespace_adder
//

scope_cursor::namespace_adder::namespace_adder(semantic_nodes::namespace_&& n):
	n_(std::move(n))
{
}

void
scope_cursor::namespace_adder::visit(semantic_nodes::namespace_& o)
{
	o.add(n_);
}

void
scope_cursor::namespace_adder::visit(semantic_nodes::class_&)
{
	assert(false);
}

void
scope_cursor::namespace_adder::visit(semantic_nodes::function&)
{
	assert(false);
}


//
//scope_cursor::class_adder
//

scope_cursor::class_adder::class_adder(semantic_nodes::class_&& c):
	c_(std::move(c))
{
}

void
scope_cursor::class_adder::visit(semantic_nodes::namespace_& o)
{
	o.add(c_);
}

void
scope_cursor::class_adder::visit(semantic_nodes::class_& o)
{
	o.add(c_);
}

void
scope_cursor::class_adder::visit(semantic_nodes::function&)
{
	assert(false);
}


//
//scope_cursor::function_adder
//

scope_cursor::function_adder::function_adder(semantic_nodes::function&& f):
	f_(std::move(f))
{
}

void
scope_cursor::function_adder::visit(semantic_nodes::namespace_& o)
{
	o.add(f_);
}

void
scope_cursor::function_adder::visit(semantic_nodes::class_& o)
{
	o.add(f_);
}

void
scope_cursor::function_adder::visit(semantic_nodes::function&)
{
	assert(false);
}


//
//scope_cursor::variable_adder
//

scope_cursor::variable_adder::variable_adder(semantic_nodes::variable&& v):
	v_(std::move(v))
{
}

void
scope_cursor::variable_adder::visit(semantic_nodes::namespace_& o)
{
	o.add(v_);
}

void
scope_cursor::variable_adder::visit(semantic_nodes::class_& o)
{
	o.add(v_);
}

void
scope_cursor::variable_adder::visit(semantic_nodes::function& o)
{
	o.add(v_);
}

}}}} //namespace socoa::cpp::detail::semantic_analysis

