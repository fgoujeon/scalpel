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

semantic_graph::scope&
scope_cursor::get_scope()
{
	assert(scope_);
	return *scope_;
}

void
scope_cursor::set_scope(semantic_graph::scope& a_scope)
{
	scope_ = &a_scope;
}

void
scope_cursor::add_to_scope(semantic_graph::namespace_&& o)
{
	scope_->accept(*this);
}

void
scope_cursor::add_to_scope(semantic_graph::class_&& o)
{
	scope_->accept(*this);
}

void
scope_cursor::visit(semantic_graph::namespace_& o)
{
}

void
scope_cursor::visit(semantic_graph::class_& o)
{
}

void
scope_cursor::visit(semantic_graph::function& o)
{
}

}} //namespace socoa::cpp

