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
#include <scalpel/cpp/semantic_entities/generic_functions/detail/get_enclosing_declarative_region.hpp>
#include <scalpel/utility/variant.hpp>
#include <iostream>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	template<class Entity>
	struct find_and_add_visitor: scalpel::utility::static_visitor<void>
	{
		public:
			find_and_add_visitor
			(
				old_to_new_entity_maps& entity_maps,
				Entity* final_entity
			):
				entity_maps_(entity_maps),
				final_entity_(final_entity)
			{
			}

			template<class EnclosingDeclarativeRegion>
			void
			operator()(const EnclosingDeclarativeRegion* enclosing_declarative_region) const
			{
				//find the corresponding final entity of the enclosing declarative region
				auto it = entity_maps_.get<EnclosingDeclarativeRegion>().find(enclosing_declarative_region);
				assert(it != entity_maps_.get<EnclosingDeclarativeRegion>().end());
				EnclosingDeclarativeRegion* final_enclosing_declarative_region = it->second;

				//add the final entity to the final declarative region entity
				final_enclosing_declarative_region->add_member(std::move(std::unique_ptr<Entity>(final_entity_)));
			}

		private:
			old_to_new_entity_maps& entity_maps_;
			Entity* final_entity_;
	};

	template<class Entity>
	void
	assemble_entities_of_type
	(
		const entity_groups& groups,
		old_to_new_entity_maps& entity_maps
	)
	{
		for(auto i = get_entity_groups_of_type<Entity>(groups).begin(); i != get_entity_groups_of_type<Entity>(groups).end(); ++i)
		{
			assert(!i->second.empty());
			const Entity* current_entity = i->second.front();

			//find the corresponding final entity
			auto it = entity_maps.get<Entity>().find(current_entity);
			assert(it != entity_maps.get<Entity>().end());
			Entity* final_entity = it->second;

			//get the enclosing declarative region of the input entity
			assert(current_entity->has_enclosing_declarative_region());
			auto enclosing_declarative_region = generic_functions::detail::get_enclosing_declarative_region(*current_entity);

			//find the corresponding final entity of the enclosing declarative region
			//and
			//add the final entity to the final declarative region entity
			find_and_add_visitor<Entity> visitor(entity_maps, final_entity);
			apply_visitor(visitor, enclosing_declarative_region);
		}
	}
}

std::unique_ptr<semantic_graph>
assemble_final_graph
(
	const entity_groups& groups,
	old_to_new_entity_maps& entity_maps
)
{
	assemble_entities_of_type<namespace_>(groups, entity_maps);
	assemble_entities_of_type<class_>(groups, entity_maps);
	assemble_entities_of_type<member_class>(groups, entity_maps);
	assemble_entities_of_type<enum_>(groups, entity_maps);
	assemble_entities_of_type<member_enum>(groups, entity_maps);
	assemble_entities_of_type<typedef_>(groups, entity_maps);
	assemble_entities_of_type<member_typedef>(groups, entity_maps);
	assemble_entities_of_type<constructor>(groups, entity_maps);
	assemble_entities_of_type<destructor>(groups, entity_maps);
	assemble_entities_of_type<operator_member_function>(groups, entity_maps);
	assemble_entities_of_type<conversion_function>(groups, entity_maps);
	assemble_entities_of_type<simple_member_function>(groups, entity_maps);
	assemble_entities_of_type<operator_function>(groups, entity_maps);
	assemble_entities_of_type<simple_function>(groups, entity_maps);
	assemble_entities_of_type<variable>(groups, entity_maps);
	assemble_entities_of_type<member_variable>(groups, entity_maps);

	return std::move(entity_maps.global_namespace);
}

}}}} //namespace scalpel::cpp::linking::detail

