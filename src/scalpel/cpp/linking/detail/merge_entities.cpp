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
	std::unique_ptr<namespace_>
	create_namespace(const linking_tree::namespace_& tree, const std::string& namespace_name);

	std::unique_ptr<simple_function>
	create_simple_function(const simple_function& entity);

	function_parameter_list
	create_function_parameter_list(const function_parameter_list& entity);

	std::unique_ptr<function_parameter>
	create_function_parameter(const function_parameter& entity);

	type_variant
	create_type(const type_variant& entity);
}

namespace
{
	std::unique_ptr<namespace_>
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

	std::unique_ptr<simple_function>
	create_simple_function(const simple_function& entity)
	{
		std::unique_ptr<simple_function> new_entity
		(
			new simple_function
			(
				entity.name(),
				entity.return_type(),
				create_function_parameter_list(entity.parameters()),
				entity.variadic(),
				entity.is_static(),
				entity.is_inline()
			)
		);

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	function_parameter_list
	create_function_parameter_list(const function_parameter_list& entity)
	{
		function_parameter_list new_entity;

		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			new_entity.push_back(create_function_parameter(*i));
		}

		return new_entity;
	}

	std::unique_ptr<function_parameter>
	create_function_parameter(const function_parameter& entity)
	{
		return std::unique_ptr<function_parameter>(new function_parameter(create_type(entity.type()), entity.name()));
	}



	struct create_type_visitor_struct: utility::static_visitor<type_variant>
	{
		type_variant
		operator()(const array& type) const
		{
			return array(type.size(), create_type(type.qualified_type()));
		}

		type_variant
		operator()(const fundamental_type& type) const
		{
			return type;
		}

		type_variant
		operator()(const function_type& type) const
		{
			return function_type
			(
				create_type(type.return_type()),
				std::vector<type_variant>(), //TODO
				type.variadic(),
				type.const_qualified(),
				type.volatile_qualified()
			);
		}

		type_variant
		operator()(const class_* type) const
		{
			return type; //TODO
		}

		type_variant
		operator()(const member_class* type) const
		{
			return type; //TODO
		}

		type_variant
		operator()(const cv_qualified_type& type) const
		{
			return cv_qualified_type(create_type(type.qualified_type()), type.qualification());
		}

		type_variant
		operator()(const enum_* type) const
		{
			return type; //TODO
		}

		type_variant
		operator()(const member_enum* type) const
		{
			return type; //TODO
		}

		type_variant
		operator()(const pointer& type) const
		{
			return pointer(create_type(type.qualified_type()));
		}

		type_variant
		operator()(const pointer_to_member& type) const
		{
			return pointer_to_member
			(
				create_type(type.qualified_type()),
				pointer_to_member::parent_class_t(static_cast<class_*>(0)) //TODO
			);
		}

		type_variant
		operator()(const reference& type) const
		{
			return reference(create_type(type.qualified_type()));
		}
	};

	type_variant
	create_type(const type_variant& entity)
	{
		create_type_visitor_struct visitor;
		return utility::apply_visitor(visitor, entity);
	}
}

std::unique_ptr<semantic_graph>
merge_entities(const linking_tree::namespace_& tree)
{
	return create_namespace(tree, "");
}

}}}} //namespace scalpel::cpp::linking::detail

