/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_LINKAGE_DETAIL_ASSEMBLE_FINAL_GRAPH_HPP
#define SCALPEL_CPP_LINKAGE_DETAIL_ASSEMBLE_FINAL_GRAPH_HPP

#include "final_graph_entities.hpp"
#include "entity_groups.hpp"
#include <scalpel/cpp/semantic_graph.hpp>
#include <memory>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

std::unique_ptr<linked_semantic_graph>
assemble_final_graph
(
	const entity_groups& groups,
	final_graph_entities& final_entities
);

}}}} //namespace scalpel::cpp::linkage::detail

#endif

