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

#include "list_entities.hpp"
#include "create_unique_id.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/get_members.hpp>
#include <scalpel/cpp/semantic_entities/generic_queries/detail/has_external_linkage.hpp>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

using namespace semantic_entities;

namespace
{
	void
	list_child_entities(const unnamed_namespace& parent_entity, entity_groups& groups);

	template<class Class>
	void
	list_child_entities(const Class& parent_entity, entity_groups& groups, const bool force_internal_linkage);

	template<class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_groups& groups, const bool force_internal_linkage);
}

namespace
{
	void
	list_child_entities(const namespace_& parent_entity, entity_groups& groups, const bool force_internal_linkage)
	{
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities(*i, groups, force_internal_linkage);
		}

		if(const unnamed_namespace* opt_unnamed_namespace = parent_entity.get_unnamed_namespace())
		{
			groups.internal_unnamed_namespaces.push_back(opt_unnamed_namespace);
			list_child_entities(*opt_unnamed_namespace, groups);
		}

		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities(*i, groups, force_internal_linkage);
		}

		list_child_entities_of_type<namespace_>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<class_>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<enum_>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<typedef_>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<operator_function>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<simple_function>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<variable>(parent_entity, groups, force_internal_linkage);
	}

	void
	list_child_entities(const unnamed_namespace& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities(*i, groups, true);
		}

		if(const unnamed_namespace* opt_unnamed_namespace = parent_entity.get_unnamed_namespace())
		{
			groups.internal_unnamed_namespaces.push_back(opt_unnamed_namespace);
			list_child_entities(*opt_unnamed_namespace, groups);
		}

		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities(*i, groups, true);
		}

		list_child_entities_of_type<namespace_>(parent_entity, groups, true);
		list_child_entities_of_type<class_>(parent_entity, groups, true);
		list_child_entities_of_type<enum_>(parent_entity, groups, true);
		list_child_entities_of_type<typedef_>(parent_entity, groups, true);
		list_child_entities_of_type<operator_function>(parent_entity, groups, true);
		list_child_entities_of_type<simple_function>(parent_entity, groups, true);
		list_child_entities_of_type<variable>(parent_entity, groups, true);
	}

	template<class Class>
	void
	list_child_entities(const Class& parent_entity, entity_groups& groups, const bool force_internal_linkage)
	{
		const utility::unique_ptr_vector<member_class>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities(*i, groups, force_internal_linkage);
		}

		list_child_entities_of_type<member_class>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<member_enum>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<member_typedef>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<constructor>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<destructor>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<operator_member_function>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<conversion_function>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<simple_member_function>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<member_variable>(parent_entity, groups, force_internal_linkage);
		list_child_entities_of_type<bit_field>(parent_entity, groups, force_internal_linkage);
	}

	template<class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_groups& groups, const bool force_internal_linkage)
	{
		typename generic_queries::detail::get_members_return_type<ChildEntity, true>::type entities =
			generic_queries::detail::get_members<ChildEntity>(parent_entity)
		;
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const ChildEntity& entity = *i;

			if(!force_internal_linkage && generic_queries::detail::has_external_linkage(entity))
			{
				const std::string unique_id = create_unique_id(entity);
				get_entity_groups_of_type<ChildEntity>(groups)[unique_id].push_back(&entity); //list and group by unique id
			}
			else
			{
				groups.internal_entities_of_type<ChildEntity>().push_back(&entity);
			}
		}
	}
}

entity_groups
list_entities(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs)
{
	entity_groups groups;

	//for each semantic graph...
	for(auto i = semantic_graphs.begin(); i != semantic_graphs.end(); ++i)
	{
		const semantic_graph& graph = *i;
		list_child_entities(graph, groups, false);
		groups.global_namespaces.push_back(&graph);
	}

	return groups;
}

}}}} //namespace scalpel::cpp::linkage::detail

