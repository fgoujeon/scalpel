/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "scope_cursor.hpp"
#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

//
//scope_cursor
//

scope_cursor::scope_cursor()
{
}

void
scope_cursor::initialize(std::shared_ptr<semantic_entities::scope> global_scope)
{
	scope_stack_.clear();
	scope_stack_.push_back(global_scope);
}

scope_cursor::scopes_t::const_range
scope_cursor::scope_stack() const
{
	return scope_stack_;
}

scope_cursor::scopes_t::range
scope_cursor::scope_stack()
{
	return scope_stack_;
}

/*
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
	return scope_stack_;
}
*/

std::shared_ptr<semantic_entities::scope>
scope_cursor::global_scope()
{
	assert(!scope_stack_.empty());
	return scope_stack_.front();
}

std::shared_ptr<semantic_entities::scope>
scope_cursor::current_scope()
{
	assert(!scope_stack_.empty());
	return scope_stack_.back();
}

void
scope_cursor::enter_scope(std::shared_ptr<semantic_entities::scope> a_scope)
{
	scope_stack_.push_back(a_scope);
}

void
scope_cursor::enter_last_added_scope()
{
	assert(!current_scope()->named_scopes().empty());
	enter_scope(current_scope()->named_scopes().back());
}

void
scope_cursor::leave_scope()
{
	scope_stack_.pop_back();
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

