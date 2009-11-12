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

#include "semantic_graph.hpp"

namespace scalpel { namespace cpp
{

semantic_graph::semantic_graph(semantic_entities::namespace_&& global_namespace, type_pool_t&& type_pool):
	global_namespace_(std::move(global_namespace)),
	type_pool_(std::move(type_pool))
{
}

semantic_graph::semantic_graph(semantic_graph&& o):
	global_namespace_(std::move(o.global_namespace_)),
	type_pool_(std::move(o.type_pool_))
{
}

const semantic_entities::namespace_&
semantic_graph::global_namespace() const
{
	return global_namespace_;
}

semantic_graph::type_pool_const_iterator_range
semantic_graph::type_pool() const
{
	return type_pool_;
}

}} //namespace scalpel::cpp

