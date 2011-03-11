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

#include "assemble_final_graph.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

std::unique_ptr<semantic_graph>
assemble_final_graph
(
	const entity_groups& groups,
	const old_to_new_entity_maps& entity_maps
)
{
	namespace_* final_graph = 0;

	//assemble namespaces
	for(auto i = get_entity_groups_of_type<namespace_>(groups).begin(); i != get_entity_groups_of_type<namespace_>(groups).end(); ++i)
	{
		assert(!i->second.empty());
		const namespace_* current_entity = i->second.front();

		//find the corresponding final entity
		auto it = entity_maps.get<namespace_>().find(current_entity);
		assert(it != entity_maps.get<namespace_>().end());
		namespace_* final_entity = it->second;

		//get the enclosing declarative region of the input entity
		const namespace_* enclosing_declarative_region = current_entity->enclosing_declarative_region();

		if(enclosing_declarative_region)
		{
			//find the corresponding final entity of the enclosing declarative region
			auto it2 = entity_maps.get<namespace_>().find(enclosing_declarative_region);
			assert(it2 != entity_maps.get<namespace_>().end());
			namespace_* final_decl_region = it2->second;

			//add the final entity to the final declarative region entity
			final_decl_region->add_member(std::unique_ptr<namespace_>(final_entity));
		}
		else
		{
			assert(final_graph == 0 || final_graph == final_entity);
			final_graph = final_entity;
		}
	}

	assert(final_graph);
	return std::unique_ptr<namespace_>(final_graph);
}

}}}} //namespace scalpel::cpp::linking::detail

