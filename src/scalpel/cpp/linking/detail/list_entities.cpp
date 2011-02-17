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
#include "../../semantic_analysis/detail/semantic_entity_analysis/get_members.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	void
	list_child_entities(const class_& parent_entity, entity_tree& tree);

	template<class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_tree& tree);
}

namespace
{
	void
	list_child_entities(const namespace_& parent_entity, entity_tree& tree)
	{
		//create and fill namespace subtrees
		const utility::unique_ptr_vector<namespace_>& child_namespaces = parent_entity.namespaces();
		for(auto i = child_namespaces.begin(); i != child_namespaces.end(); ++i)
		{
			const namespace_& child_namespace = *i;
			const std::string& namespace_name = child_namespace.name();

			auto it = tree.subtrees.find(namespace_name);
			if(it == tree.subtrees.end())
			{
				it = tree.subtrees.insert(std::pair<std::string, entity_tree>(namespace_name, entity_tree(entity_tree::tree_type::NAMESPACE))).first;
			}

			list_child_entities(child_namespace, it->second);
		}

		//create and fill class subtrees
		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			const class_& child_class = *i;
			const std::string& class_name = child_class.name();

			auto it = tree.subtrees.find(class_name);
			if(it == tree.subtrees.end())
			{
				it = tree.subtrees.insert(std::pair<std::string, entity_tree>(class_name, entity_tree(entity_tree::tree_type::CLASS))).first;
			}

			list_child_entities(child_class, it->second);
		}

		//fill current tree
		list_child_entities_of_type<enum_>(parent_entity, tree);
		list_child_entities_of_type<typedef_>(parent_entity, tree);
		list_child_entities_of_type<operator_function>(parent_entity, tree);
		list_child_entities_of_type<simple_function>(parent_entity, tree);
		list_child_entities_of_type<variable>(parent_entity, tree);
	}

	void
	list_child_entities(const class_& parent_entity, entity_tree& tree)
	{
		//create and fill class subtrees
		const utility::unique_ptr_vector<class_>& child_classes = parent_entity.nested_classes();
		for(auto i = child_classes.begin(); i != child_classes.end(); ++i)
		{
			const class_& child_class = *i;
			const std::string& class_name = child_class.name();

			auto it = tree.subtrees.find(class_name);
			if(it == tree.subtrees.end())
			{
				it = tree.subtrees.insert(std::pair<std::string, entity_tree>(class_name, entity_tree(entity_tree::tree_type::CLASS))).first;
			}

			list_child_entities(child_class, it->second);
		}

		//fill current tree
		list_child_entities_of_type<enum_>(parent_entity, tree);
		list_child_entities_of_type<typedef_>(parent_entity, tree);
		list_child_entities_of_type<constructor>(parent_entity, tree);
		list_child_entities_of_type<destructor>(parent_entity, tree);
		list_child_entities_of_type<operator_member_function>(parent_entity, tree);
		list_child_entities_of_type<conversion_function>(parent_entity, tree);
		list_child_entities_of_type<simple_member_function>(parent_entity, tree);
		list_child_entities_of_type<variable>(parent_entity, tree);
	}

	template<class ChildEntity, class ParentEntity>
	void
	list_child_entities_of_type(const ParentEntity& parent_entity, entity_tree& tree)
	{
		typename semantic_analysis::detail::semantic_entity_analysis::member_type_traits<ChildEntity, true>::return_type entities =
			semantic_analysis::detail::semantic_entity_analysis::get_members<ChildEntity>(parent_entity)
		;
		for(auto i = entities.begin(); i != entities.end(); ++i)
		{
			const ChildEntity& entity = *i;
			tree.entities<ChildEntity>().list[create_unique_id(entity)].push_back(&entity);
		}
	}
}

entity_tree
list_entities(const utility::unique_ptr_vector<semantic_graph>& semantic_graphs)
{
	entity_tree tree(entity_tree::tree_type::NAMESPACE);

	//for each semantic graph...
	for(auto i = semantic_graphs.begin(); i != semantic_graphs.end(); ++i)
	{
		const semantic_graph& graph = *i;
		list_child_entities(graph, tree);
	}

	return tree;
}

}}}} //namespace scalpel::cpp::linking::detail

