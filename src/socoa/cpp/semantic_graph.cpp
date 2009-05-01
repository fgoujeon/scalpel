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

#include "semantic_graph.hpp"

#include <iostream>

namespace socoa { namespace cpp
{

semantic_graph::semantic_graph():
	root_node_(new semantic_nodes::namespace_())
{
}

semantic_graph::semantic_graph(semantic_graph&& o):
	root_node_(std::move(o.root_node_))
{
}

semantic_nodes::namespace_&
semantic_graph::root_node()
{
	return *root_node_;
}

semantic_graph::scope_const_iterator_range
semantic_graph::lastly_closed_scope_iterator() const
{
	scope_const_iterator first = lastly_closed_scopes_.begin();
	scope_const_iterator last = lastly_closed_scopes_.end();

	scope_const_indirect_iterator const_indirect_first(first), const_indirect_last(last);

	return scope_const_iterator_range(const_indirect_first, const_indirect_last);
}

semantic_graph::scope_const_reverse_iterator_range
semantic_graph::lastly_closed_scope_reverse_iterator() const
{
	scope_const_reverse_iterator first = lastly_closed_scopes_.rbegin();
	scope_const_reverse_iterator last = lastly_closed_scopes_.rend();

	scope_const_reverse_indirect_iterator const_reverse_indirect_first(first), const_reverse_indirect_last(last);

	return scope_const_reverse_iterator_range(const_reverse_indirect_first, const_reverse_indirect_last);
}

void
semantic_graph::lastly_closed_scopes(const scopes_t& scopes)
{
	lastly_closed_scopes_ = scopes;
}

}} //namespace socoa::cpp

