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

#include "create_output_graph_entities.hpp"
#include <scalpel/cpp/semantic_entities/generic_functions/detail/is_defined.hpp>

namespace scalpel { namespace cpp { namespace linking { namespace detail
{

using namespace semantic_entities;

//namespace
//{
//	std::unique_ptr<namespace_>
//	create_namespace(const linking_tree::namespace_& tree, const std::string& namespace_name);
//
//	std::unique_ptr<simple_function>
//	create_simple_function(const simple_function& entity);
//
//	function_parameter_list
//	create_function_parameter_list(const function_parameter_list& entity);
//
//	std::unique_ptr<function_parameter>
//	create_function_parameter(const function_parameter& entity);
//
//	type_variant
//	create_type(const type_variant& entity);
//}
//
//namespace
//{
//	std::unique_ptr<namespace_>
//	create_namespace(const linking_tree::namespace_& tree, const std::string& namespace_name)
//	{
//		std::unique_ptr<namespace_> new_namespace(new namespace_(namespace_name));
//
//		for(auto i = tree.namespaces.begin(); i != tree.namespaces.end(); ++i)
//		{
//			const std::string& name = i->first;
//			const detail::linking_tree::namespace_& subtree = i->second;
//			new_namespace->add_member(create_namespace(subtree, name));
//		}
//
//		for(auto i = tree.simple_functions.list.begin(); i != tree.simple_functions.list.end(); ++i)
//		{
//			const std::string& entity_name = i->first;
//			const std::vector<const simple_function*>& entities = i->second;
//
//			assert(!entities.empty());
//
//			//find a defined version of the entity
//			const simple_function* defined_entity = 0;
//			for(auto j = entities.begin(); j != entities.end(); ++j)
//			{
//				const simple_function* current_entity = *j;
//				if(current_entity->defined())
//				{
//					if(defined_entity != 0) throw std::runtime_error(("multiple definition of " + entity_name).c_str());
//					defined_entity = current_entity;
//				}
//			}
//
//			const simple_function& selected_entity = defined_entity ? *defined_entity : *entities.front();
//			new_namespace->add_member(create_simple_function(selected_entity));
//		}
//
//		return new_namespace;
//	}
//
//	std::unique_ptr<simple_function>
//	create_simple_function(const simple_function& entity)
//	{
//		std::unique_ptr<simple_function> new_entity
//		(
//			new simple_function
//			(
//				entity.name(),
//				entity.return_type(),
//				create_function_parameter_list(entity.parameters()),
//				entity.variadic(),
//				entity.is_static(),
//				entity.is_inline()
//			)
//		);
//
//		if(entity.defined())
//			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));
//
//		return new_entity;
//	}
//
//	function_parameter_list
//	create_function_parameter_list(const function_parameter_list& entity)
//	{
//		function_parameter_list new_entity;
//
//		for(auto i = entity.begin(); i != entity.end(); ++i)
//		{
//			new_entity.push_back(create_function_parameter(*i));
//		}
//
//		return new_entity;
//	}
//
//	std::unique_ptr<function_parameter>
//	create_function_parameter(const function_parameter& entity)
//	{
//		return std::unique_ptr<function_parameter>(new function_parameter(create_type(entity.type()), entity.name()));
//	}
//
//
//
//	struct create_type_visitor_struct: utility::static_visitor<type_variant>
//	{
//		type_variant
//		operator()(const array& type) const
//		{
//			return array(type.size(), create_type(type.qualified_type()));
//		}
//
//		type_variant
//		operator()(const fundamental_type& type) const
//		{
//			return type;
//		}
//
//		type_variant
//		operator()(const function_type& type) const
//		{
//			return function_type
//			(
//				create_type(type.return_type()),
//				std::vector<type_variant>(), //TODO
//				type.variadic(),
//				type.const_qualified(),
//				type.volatile_qualified()
//			);
//		}
//
//		type_variant
//		operator()(const class_* type) const
//		{
//			return type; //TODO
//		}
//
//		type_variant
//		operator()(const member_class* type) const
//		{
//			return type; //TODO
//		}
//
//		type_variant
//		operator()(const cv_qualified_type& type) const
//		{
//			return cv_qualified_type(create_type(type.qualified_type()), type.qualification());
//		}
//
//		type_variant
//		operator()(const enum_* type) const
//		{
//			return type; //TODO
//		}
//
//		type_variant
//		operator()(const member_enum* type) const
//		{
//			return type; //TODO
//		}
//
//		type_variant
//		operator()(const pointer& type) const
//		{
//			return pointer(create_type(type.qualified_type()));
//		}
//
//		type_variant
//		operator()(const pointer_to_member& type) const
//		{
//			return pointer_to_member
//			(
//				create_type(type.qualified_type()),
//				pointer_to_member::parent_class_t(static_cast<class_*>(0)) //TODO
//			);
//		}
//
//		type_variant
//		operator()(const reference& type) const
//		{
//			return reference(create_type(type.qualified_type()));
//		}
//	};
//
//	type_variant
//	create_type(const type_variant& entity)
//	{
//		create_type_visitor_struct visitor;
//		return utility::apply_visitor(visitor, entity);
//	}
//}

namespace
{
	namespace_*
	create_entity(const namespace_& entity)
	{
		return new namespace_(entity.name());
	}

	class_*
	create_entity(const class_& entity)
	{
		return new class_(entity.name());
	}

	member_class*
	create_entity(const member_class& entity)
	{
		return new member_class(entity.name(), entity.access());
	}

	enum_*
	create_entity(const enum_& entity)
	{
		return new enum_(entity.name());
	}

	member_enum*
	create_entity(const member_enum& entity)
	{
		return new member_enum(entity.name(), entity.access());
	}

	typedef_*
	create_entity(const typedef_& entity)
	{
		return new typedef_(entity.name(), fundamental_type::VOID); //TODO
	}

	member_typedef*
	create_entity(const member_typedef& entity)
	{
		return new member_typedef(entity.name(), fundamental_type::VOID, entity.access()); //TODO
	}

	constructor*
	create_entity(const constructor& entity)
	{
		return new constructor
		(
			function_parameter_list(), //TODO
			entity.variadic(),
			entity.access(),
			entity.is_explicit(),
			entity.is_inline()
		);
	}

	destructor*
	create_entity(const destructor& entity)
	{
		return
			new destructor
			(
				entity.access(),
				entity.is_inline()
			)
		;
	}

	operator_member_function*
	create_entity(const operator_member_function& entity)
	{
		return
			new operator_member_function
			(
				entity.overloaded_operator(),
				fundamental_type::VOID, //TODO
				function_parameter_list(), //TODO
				entity.access(),
				entity.is_const(),
				entity.is_volatile(),
				entity.is_virtual(),
				entity.is_pure(),
				entity.is_inline()
			)
		;
	}

	conversion_function*
	create_entity(const conversion_function& entity)
	{
		return
			new conversion_function
			(
				fundamental_type::VOID, //TODO
				entity.access(),
				entity.is_const(),
				entity.is_volatile(),
				entity.is_explicit(),
				entity.is_virtual(),
				entity.is_pure(),
				entity.is_inline()
			)
		;
	}

	simple_member_function*
	create_entity(const simple_member_function& entity)
	{
		return
			new simple_member_function
			(
				entity.name(),
				fundamental_type::VOID, //TODO
				function_parameter_list(), //TODO
				entity.variadic(),
				entity.access(),
				entity.is_const(),
				entity.is_volatile(),
				entity.is_static(),
				entity.is_virtual(),
				entity.is_pure(),
				entity.is_inline()
			)
		;
	}

	operator_function*
	create_entity(const operator_function& entity)
	{
		return
			new operator_function
			(
				entity.overloaded_operator(),
				fundamental_type::VOID, //TODO
				function_parameter_list(), //TODO
				entity.is_static(),
				entity.is_inline()
			)
		;
	}

	simple_function*
	create_entity(const simple_function& entity)
	{
		return
			new simple_function
			(
				entity.name(),
				fundamental_type::VOID, //TODO
				function_parameter_list(), //TODO
				entity.variadic(),
				entity.is_static(),
				entity.is_inline()
			)
		;
	}

	variable*
	create_entity(const variable& entity)
	{
		return
			new variable
			(
				entity.name(),
				fundamental_type::VOID //TODO
			)
		;
	}

	member_variable*
	create_entity(const member_variable& entity)
	{
		return
			new member_variable
			(
				entity.name(),
				fundamental_type::VOID, //TODO
				entity.is_static(),
				entity.is_mutable(),
				entity.access()
			)
		;
	}
}

namespace
{
	void
	create_global_namespace
	(
		const entity_groups& groups,
		old_to_new_entity_maps& entity_maps
	)
	{
		//create the global namespace
		entity_maps.global_namespace = std::unique_ptr<namespace_>(new namespace_());

		for(auto i = groups.global_namespaces.begin(); i != groups.global_namespaces.end(); ++i)
		{
			//add links between the old global namespaces and the new one
			entity_maps.namespaces.insert(std::pair<const namespace_*, namespace_*>(*i, entity_maps.global_namespace.get()));
		}
	}

	template<class Entity, bool ErrorIfMultipleDefinition = true>
	void
	create_entities_of_type
	(
		const typename detail::entity_groups_of_type<Entity>::type& groups,
		old_to_new_entity_maps& entity_maps
	)
	{
		for(auto i = groups.begin(); i != groups.end(); ++i) //for each group (1 group = 1 output entity)
		{
			const std::string group_id = i->first;
			const std::vector<const Entity*>& group = i->second;

			//find a defined version of the entity
			const Entity* defined_entity = 0;
			for(auto j = group.begin(); j != group.end(); ++j)
			{
				const Entity* current_entity = *j;
				if(generic_functions::detail::is_defined(*current_entity))
				{
					if(defined_entity != 0 && ErrorIfMultipleDefinition)
						throw std::runtime_error(("multiple definition of " + group_id).c_str());
					defined_entity = current_entity;
				}
			}

			//select the first entity if no defined entity has been found
			const Entity& selected_entity = defined_entity ? *defined_entity : *group.front();

			//create a new entity by copying the selected one
			Entity* new_entity = create_entity(selected_entity);

			//add links between groups' entities and the new entity
			for(auto j = group.begin(); j != group.end(); ++j)
			{
				entity_maps.get<Entity>().insert(std::pair<const Entity*, Entity*>(*j, new_entity));
			}
		}
	}
}

void
create_output_graph_entities
(
	const entity_groups& groups,
	old_to_new_entity_maps& entity_maps
)
{
	create_global_namespace(groups, entity_maps);
	create_entities_of_type<semantic_entities::namespace_, false>(groups.namespaces, entity_maps);
	create_entities_of_type<semantic_entities::class_, false>(groups.classes, entity_maps);
	create_entities_of_type<semantic_entities::member_class, false>(groups.member_classes, entity_maps);
	create_entities_of_type<semantic_entities::enum_, false>(groups.enums, entity_maps);
	create_entities_of_type<semantic_entities::member_enum, false>(groups.member_enums, entity_maps);
	create_entities_of_type<semantic_entities::typedef_, false>(groups.typedefs, entity_maps);
	create_entities_of_type<semantic_entities::member_typedef, false>(groups.member_typedefs, entity_maps);
	create_entities_of_type<semantic_entities::constructor>(groups.constructors, entity_maps);
	create_entities_of_type<semantic_entities::destructor>(groups.destructors, entity_maps);
	create_entities_of_type<semantic_entities::operator_member_function>(groups.operator_member_functions, entity_maps);
	create_entities_of_type<semantic_entities::conversion_function>(groups.conversion_functions, entity_maps);
	create_entities_of_type<semantic_entities::simple_member_function>(groups.simple_member_functions, entity_maps);
	create_entities_of_type<semantic_entities::operator_function>(groups.operator_functions, entity_maps);
	create_entities_of_type<semantic_entities::simple_function>(groups.simple_functions, entity_maps);
	create_entities_of_type<semantic_entities::variable>(groups.variables, entity_maps);
	create_entities_of_type<semantic_entities::member_variable>(groups.member_variables, entity_maps);
}

}}}} //namespace scalpel::cpp::linking::detail

