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
#include <scalpel/cpp/semantic_entities/generic_queries/detail/add_entity_to_declarative_region.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/has_enclosing_declarative_region.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/enclosing_declarative_region.hpp>
#include <scalpel/utility/variant.hpp>
#include <iostream>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

using namespace semantic_entities;

namespace
{
	//add the given entity (final_entity) to the correct declarative region of
	//the final graph (found in final_entities, using enclosing_declarative_region)
	template<class Entity, class EnclosingDeclarativeRegion>
	void
	add_entity_to_final_graph
	(
		final_graph_entities& final_entities,
		Entity* final_entity,
		const EnclosingDeclarativeRegion& enclosing_declarative_region
	);
}

namespace
{
	template<class Entity>
	struct add_entity_to_final_graph_visitor: scalpel::utility::static_visitor<void>
	{
		public:
			add_entity_to_final_graph_visitor
			(
				final_graph_entities& final_entities,
				Entity* final_entity
			):
				entity_maps_(final_entities),
				final_entity_(final_entity)
			{
			}

			template<class EnclosingDeclarativeRegion>
			void
			operator()(const EnclosingDeclarativeRegion* enclosing_declarative_region) const
			{
				add_entity_to_final_graph<Entity, EnclosingDeclarativeRegion>
				(
					entity_maps_,
					final_entity_,
					*enclosing_declarative_region
				);
			}

			void
			operator()(const linked_namespace*) const
			{
				assert(false);
			}

			void
			operator()(const linked_unnamed_namespace*) const
			{
				assert(false);
			}

		private:
			final_graph_entities& entity_maps_;
			Entity* final_entity_;
	};

	template<class Entity, class EnclosingDeclarativeRegion>
	void
	add_entity_to_final_graph
	(
		final_graph_entities& final_entities,
		Entity* final_entity,
		const EnclosingDeclarativeRegion& enclosing_declarative_region
	)
	{
		typedef typename linked_type<EnclosingDeclarativeRegion>::type linked_enclosing_declarative_region_t;

		//find the corresponding final entity of the enclosing declarative region
		auto it = final_entities.get_map_of_linked_type<linked_enclosing_declarative_region_t>().find(&enclosing_declarative_region);
		assert(it != final_entities.get_map_of_linked_type<linked_enclosing_declarative_region_t>().end());
		typename linked_type<EnclosingDeclarativeRegion>::type* final_enclosing_declarative_region = it->second;

		//add the final entity to the final declarative region entity
		generic_queries::detail::add_entity_to_declarative_region(std::move(std::unique_ptr<Entity>(final_entity)), *final_enclosing_declarative_region);
	}

	template<class Entity, class... DeclarativeRegions>
	void
	add_entity_to_final_graph
	(
		final_graph_entities& final_entities,
		Entity* final_entity,
		const utility::variant<DeclarativeRegions...>& enclosing_declarative_region
	)
	{
		add_entity_to_final_graph_visitor<Entity> visitor(final_entities, final_entity);
		apply_visitor(visitor, enclosing_declarative_region);
	}

	template<class Entity>
	void
	assemble_entities_of_type
	(
		const entity_groups& groups,
		final_graph_entities& final_entities
	)
	{
		typedef typename nonlinked_type<Entity>::type nonlinked_entity_t;

		const typename entity_groups_of_type<nonlinked_entity_t>::type& groups_of_entity_type =
			get_entity_groups_of_type<nonlinked_entity_t>(groups)
		;
		for(auto i = groups_of_entity_type.begin(); i != groups_of_entity_type.end(); ++i)
		{
			assert(!i->second.empty());
			const nonlinked_entity_t* current_entity = i->second.front();

			//find the corresponding final entity
			auto it = final_entities.get_map_of_linked_type<Entity>().find(current_entity);
			assert(it != final_entities.get_map_of_linked_type<Entity>().end());
			Entity* final_entity = it->second;

			//add the final entity to the final graph
			assert(generic_queries::detail::has_enclosing_declarative_region(*current_entity));
			add_entity_to_final_graph
			(
				final_entities,
				final_entity,
				generic_queries::detail::get_enclosing_declarative_region(*current_entity)
			);
		}
	}

	template<class Entity>
	void
	assemble_internal_entities_of_type
	(
		const entity_groups& groups,
		final_graph_entities& final_entities
	)
	{
		typedef typename nonlinked_type<Entity>::type nonlinked_entity_t;

		const std::vector<const nonlinked_entity_t*>& entities = groups.internal_entities_of_type<nonlinked_entity_t>();
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const nonlinked_entity_t* current_entity = *i;

			//find the corresponding final entity
			auto it = final_entities.get_map_of_linked_type<Entity>().find(current_entity);
			assert(it != final_entities.get_map_of_linked_type<Entity>().end());
			Entity* final_entity = it->second;

			//add the final entity to the final graph
			assert(generic_queries::detail::has_enclosing_declarative_region(*current_entity));
			add_entity_to_final_graph
			(
				final_entities,
				final_entity,
				generic_queries::detail::get_enclosing_declarative_region(*current_entity)
			);
		}
	}
}

std::unique_ptr<linked_namespace>
assemble_final_graph
(
	const entity_groups& groups,
	final_graph_entities& final_entities
)
{
	assemble_entities_of_type<linked_namespace>(groups, final_entities);
	assemble_entities_of_type<class_>(groups, final_entities);
	assemble_entities_of_type<member_class>(groups, final_entities);
	assemble_entities_of_type<union_>(groups, final_entities);
	assemble_entities_of_type<member_union>(groups, final_entities);
	assemble_entities_of_type<enum_>(groups, final_entities);
	assemble_entities_of_type<member_enum>(groups, final_entities);
	assemble_entities_of_type<typedef_>(groups, final_entities);
	assemble_entities_of_type<member_typedef>(groups, final_entities);
	assemble_entities_of_type<constructor>(groups, final_entities);
	assemble_entities_of_type<destructor>(groups, final_entities);
	assemble_entities_of_type<operator_member_function>(groups, final_entities);
	assemble_entities_of_type<conversion_function>(groups, final_entities);
	assemble_entities_of_type<simple_member_function>(groups, final_entities);
	assemble_entities_of_type<operator_function>(groups, final_entities);
	assemble_entities_of_type<simple_function>(groups, final_entities);
	assemble_entities_of_type<variable>(groups, final_entities);
	assemble_entities_of_type<member_variable>(groups, final_entities);
	assemble_entities_of_type<static_member_variable>(groups, final_entities);
	assemble_entities_of_type<bit_field>(groups, final_entities);
	assemble_entities_of_type<enum_constant<int>>(groups, final_entities);

	assemble_internal_entities_of_type<linked_namespace>(groups, final_entities);
	assemble_internal_entities_of_type<linked_unnamed_namespace>(groups, final_entities);
	assemble_internal_entities_of_type<class_>(groups, final_entities);
	assemble_internal_entities_of_type<member_class>(groups, final_entities);
	assemble_internal_entities_of_type<union_>(groups, final_entities);
	assemble_internal_entities_of_type<member_union>(groups, final_entities);
	assemble_internal_entities_of_type<anonymous_union>(groups, final_entities);
	assemble_internal_entities_of_type<anonymous_member_union>(groups, final_entities);
	assemble_internal_entities_of_type<enum_>(groups, final_entities);
	assemble_internal_entities_of_type<member_enum>(groups, final_entities);
	assemble_internal_entities_of_type<typedef_>(groups, final_entities);
	assemble_internal_entities_of_type<member_typedef>(groups, final_entities);
	assemble_internal_entities_of_type<constructor>(groups, final_entities);
	assemble_internal_entities_of_type<destructor>(groups, final_entities);
	assemble_internal_entities_of_type<operator_member_function>(groups, final_entities);
	assemble_internal_entities_of_type<conversion_function>(groups, final_entities);
	assemble_internal_entities_of_type<simple_member_function>(groups, final_entities);
	assemble_internal_entities_of_type<operator_function>(groups, final_entities);
	assemble_internal_entities_of_type<simple_function>(groups, final_entities);
	assemble_internal_entities_of_type<variable>(groups, final_entities);
	assemble_internal_entities_of_type<member_variable>(groups, final_entities);
	assemble_internal_entities_of_type<static_member_variable>(groups, final_entities);
	assemble_internal_entities_of_type<bit_field>(groups, final_entities);
	assemble_internal_entities_of_type<enum_constant<int>>(groups, final_entities);

	return std::move(final_entities.global_namespace);
}

}}}} //namespace scalpel::cpp::linkage::detail

