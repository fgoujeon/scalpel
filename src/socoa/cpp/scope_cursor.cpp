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

namespace socoa { namespace cpp
{

//
//scope_cursor
//

semantic_graph::scope&
scope_cursor::get_scope()
{
	assert(current_scope_);
	return *current_scope_;
}

void
scope_cursor::set_scope(semantic_graph::scope& a_scope)
{
	current_scope_ = &a_scope;
}

void
scope_cursor::add_to_scope(semantic_graph::namespace_&& o)
{
	scope_visitor_namespace v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_scope(semantic_graph::class_&& o)
{
	scope_visitor_class v(o);
	current_scope_->accept(v);
}

void
scope_cursor::add_to_scope(semantic_graph::function&& o)
{
	scope_visitor_function v(o);
	current_scope_->accept(v);
}

void
scope_cursor::enter_last_added_scope()
{
	assert(!current_scope_->get_scopes().empty());
	current_scope_ = &current_scope_->get_scopes().back();
}

void
scope_cursor::leave_scope()
{
	assert(current_scope_->has_enclosing_scope());
	current_scope_ = &current_scope_->get_enclosing_scope();
}


//
//scope_cursor::scope_visitor_namespace
//

scope_cursor::scope_visitor_namespace::scope_visitor_namespace(semantic_graph::namespace_&& n):
	n_(std::move(n))
{
}

void
scope_cursor::scope_visitor_namespace::visit(semantic_graph::namespace_& o)
{
	o.add(n_);
}

void
scope_cursor::scope_visitor_namespace::visit(semantic_graph::class_&)
{
	assert(false);
}

void
scope_cursor::scope_visitor_namespace::visit(semantic_graph::function&)
{
	assert(false);
}


//
//scope_cursor::scope_visitor_class
//

scope_cursor::scope_visitor_class::scope_visitor_class(semantic_graph::class_&& c):
	c_(std::move(c))
{
}

void
scope_cursor::scope_visitor_class::visit(semantic_graph::namespace_& o)
{
	o.add(c_);
}

void
scope_cursor::scope_visitor_class::visit(semantic_graph::class_& o)
{
	o.add(c_);
}

void
scope_cursor::scope_visitor_class::visit(semantic_graph::function&)
{
	assert(false);
}


//
//scope_cursor::scope_visitor_function
//

scope_cursor::scope_visitor_function::scope_visitor_function(semantic_graph::function&& f):
	f_(std::move(f))
{
}

void
scope_cursor::scope_visitor_function::visit(semantic_graph::namespace_& o)
{
	o.add(f_);
}

void
scope_cursor::scope_visitor_function::visit(semantic_graph::class_& o)
{
	o.add(f_);
}

void
scope_cursor::scope_visitor_function::visit(semantic_graph::function&)
{
	assert(false);
}

}} //namespace socoa::cpp

