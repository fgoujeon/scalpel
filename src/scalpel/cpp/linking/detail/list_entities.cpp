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

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	void
	list_child_entities(const unnamed_namespace& parent_entity, entity_groups& groups);

	template<bool ForceInternalLinkage, class Class>
	void
	list_child_entities(const Class& parent_entity, entity_groups& groups);

	template<class ChildEntity, bool ForceInternalLinkage, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_groups& groups);
}

namespace
{
	template<bool ForceInternalLinkage>
	void
	list_child_entities(const namespace_& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities<ForceInternalLinkage>(*i, groups);
		}

		if(const unnamed_namespace* opt_unnamed_namespace = parent_entity.get_unnamed_namespace())
		{
			groups.internal_unnamed_namespaces.push_back(opt_unnamed_namespace);
			list_child_entities(*opt_unnamed_namespace, groups);
		}

		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities<ForceInternalLinkage>(*i, groups);
		}

		list_child_entities_of_type<namespace_, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<class_, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<enum_, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<typedef_, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<operator_function, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<simple_function, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<variable, ForceInternalLinkage>(parent_entity, groups);
	}

	void
	list_child_entities(const unnamed_namespace& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		if(const unnamed_namespace* opt_unnamed_namespace = parent_entity.get_unnamed_namespace())
		{
			groups.internal_unnamed_namespaces.push_back(opt_unnamed_namespace);
			list_child_entities(*opt_unnamed_namespace, groups);
		}

		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities<true>(*i, groups);
		}

		list_child_entities_of_type<namespace_, true>(parent_entity, groups);
		list_child_entities_of_type<class_, true>(parent_entity, groups);
		list_child_entities_of_type<enum_, true>(parent_entity, groups);
		list_child_entities_of_type<typedef_, true>(parent_entity, groups);
		list_child_entities_of_type<operator_function, true>(parent_entity, groups);
		list_child_entities_of_type<simple_function, true>(parent_entity, groups);
		list_child_entities_of_type<variable, true>(parent_entity, groups);
	}

	template<bool ForceInternalLinkage, class Class>
	void
	list_child_entities(const Class& parent_entity, entity_groups& groups)
	{
		const utility::unique_ptr_vector<member_class>& child_classes = parent_entity.nested_classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			list_child_entities<ForceInternalLinkage>(*i, groups);
		}

		list_child_entities_of_type<member_class, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<member_enum, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<member_typedef, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<constructor, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<destructor, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<operator_member_function, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<conversion_function, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<simple_member_function, ForceInternalLinkage>(parent_entity, groups);
		list_child_entities_of_type<member_variable, ForceInternalLinkage>(parent_entity, groups);
	}



	template<class ChildEntity, bool ForceInternalLinkage, class ParentEntity>
	struct list_child_entities_of_type_impl;

	template<class ChildEntity, class ParentEntity>
	struct list_child_entities_of_type_impl<ChildEntity, false, ParentEntity>
	{
		static
		void
		list(const ParentEntity& parent_entity, entity_groups& groups)
		{
			typename generic_queries::detail::member_type_traits<ChildEntity, true>::return_type entities =
				generic_queries::detail::get_members<ChildEntity>(parent_entity)
			;
			for(auto i = entities.begin(); i != entities.end(); ++i)
			{
				const ChildEntity& entity = *i;
				const std::string unique_id = create_unique_id(entity);
				get_entity_groups_of_type<ChildEntity>(groups)[unique_id].push_back(&entity); //list and group by unique id
			}
		}
	};

	template<class ChildEntity, class ParentEntity>
	struct list_child_entities_of_type_impl<ChildEntity, true, ParentEntity>
	{
		static
		void
		list(const ParentEntity& parent_entity, entity_groups& groups)
		{
			typename generic_queries::detail::member_type_traits<ChildEntity, true>::return_type entities =
				generic_queries::detail::get_members<ChildEntity>(parent_entity)
			;
			for(auto i = entities.begin(); i != entities.end(); ++i)
			{
				const ChildEntity& entity = *i;
				groups.internal_entities_of_type<ChildEntity>().push_back(&entity);
			}
		}
	};

	template<class ChildEntity, bool ForceInternalLinkage, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_groups& groups)
	{
		list_child_entities_of_type_impl<ChildEntity, ForceInternalLinkage, ParentEntity>::list(parent_entity, groups);
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
		list_child_entities<false>(graph, groups);
		groups.global_namespaces.push_back(&graph);
	}

	return groups;
}

}}}} //namespace scalpel::cpp::linking::detail

