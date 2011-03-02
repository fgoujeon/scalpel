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

#include "merge_entities.hpp"

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

namespace
{
	std::unique_ptr<semantic_entities::namespace_>
	create_namespace(const linking_tree::namespace_& tree, const std::string& namespace_name);

	std::unique_ptr<semantic_entities::simple_function>
	create_simple_function(const simple_function& entity);
}

namespace
{
	std::unique_ptr<semantic_entities::namespace_>
	create_namespace(const linking_tree::namespace_& tree, const std::string& namespace_name)
	{
		std::unique_ptr<namespace_> new_namespace(new namespace_(namespace_name));

		for(auto i = tree.namespaces.begin(); i != tree.namespaces.end(); ++i)
		{
			const std::string& name = i->first;
			const detail::linking_tree::namespace_& subtree = i->second;
			new_namespace->add_member(create_namespace(subtree, name));
		}

		for(auto i = tree.simple_functions.list.begin(); i != tree.simple_functions.list.end(); ++i)
		{
			const std::string& entity_name = i->first;
			const std::vector<const simple_function*>& entities = i->second;

			assert(!entities.empty());

			//find a defined version of the entity
			const simple_function* defined_entity = 0;
			for(auto j = entities.begin(); j != entities.end(); ++j)
			{
				const simple_function* current_entity = *j;
				if(current_entity->defined())
				{
					if(defined_entity != 0) throw std::runtime_error(("multiple definition of " + entity_name).c_str());
					defined_entity = current_entity;
				}
			}

			const simple_function& selected_entity = defined_entity ? *defined_entity : *entities.front();
			new_namespace->add_member(create_simple_function(selected_entity));
		}

		return new_namespace;
	}

	std::unique_ptr<semantic_entities::simple_function>
	create_simple_function(const simple_function& entity)
	{
		std::unique_ptr<semantic_entities::simple_function> new_entity
		(
			new semantic_entities::simple_function
			(
				entity.name(),
				entity.return_type(),
				function_parameter_list(), //entity.parameters(),
				entity.variadic(),
				entity.is_static(),
				entity.is_inline()
			)
		);

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}
}

std::unique_ptr<semantic_graph>
merge_entities(const linking_tree::namespace_& tree)
{
	return create_namespace(tree, "");
}

}}}} //namespace scalpel::cpp::linking::detail

