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

namespace socoa { namespace cpp
{

semantic_graph::semantic_graph(syntax_tree&& tree):
	syntax_tree_(tree)
{
}

semantic_graph::semantic_graph(semantic_graph&& o):
	syntax_tree_(std::move(o.syntax_tree_)),
	root_node_(std::move(o.root_node_))
{
}

semantic_nodes::namespace_&
semantic_graph::root_node()
{
	return root_node_;
}

}} //namespace socoa::cpp

