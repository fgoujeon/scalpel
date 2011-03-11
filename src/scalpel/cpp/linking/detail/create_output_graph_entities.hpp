/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_LINKING_DETAIL_CREATE_OUTPUT_GRAPH_ENTITIES_HPP
#define SCALPEL_CPP_LINKING_DETAIL_CREATE_OUTPUT_GRAPH_ENTITIES_HPP

#include "old_to_new_entity_maps.hpp"
#include "entity_groups.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

void
create_output_graph_entities
(
	const entity_groups& groups,
	old_to_new_entity_maps& entity_maps
);

}}}} //namespace scalpel::cpp::linking::detail

#endif

