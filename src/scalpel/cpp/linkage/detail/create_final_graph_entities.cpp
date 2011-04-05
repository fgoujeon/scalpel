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

#include "create_final_graph_entities.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/is_defined.hpp>

namespace scalpel { namespace cpp { namespace linkage { namespace detail
{

using namespace semantic_entities;

//private function declarations
namespace
{
	function_parameter_list
	create_function_parameter_list
	(
		const function_parameter_list& entity,
		const final_graph_entities& final_entities
	);

	std::unique_ptr<function_parameter>
	create_function_parameter
	(
		const function_parameter& entity,
		const final_graph_entities& final_entities
	);

	type_variant
	create_type
	(
		const type_variant& entity,
		const final_graph_entities& final_entities
	);

	template<class Enum>
	void
	copy_constants(const Enum& src, Enum& dest);
}

//private function definitions
namespace
{
	linked_namespace*
	create_entity
	(
		const namespace_& entity,
		const final_graph_entities&
	)
	{
		return new linked_namespace(entity.name());
	}

	linked_unnamed_namespace*
	create_entity
	(
		const unnamed_namespace&,
		const final_graph_entities&
	)
	{
		return new linked_unnamed_namespace();
	}

	class_*
	create_entity
	(
		const class_& entity,
		final_graph_entities& final_entities
	)
	{
		class_* new_class = new class_(entity.name());
		new_class->complete(entity.complete());

		final_entities.class_pairs.push_back(old_and_new_entity_pair<class_>{&entity, new_class});

		return new_class;
	}

	member_class*
	create_entity
	(
		const member_class& entity,
		final_graph_entities& final_entities
	)
	{
		member_class* new_class = new member_class(entity.name(), entity.access());
		new_class->complete(entity.complete());

		final_entities.member_class_pairs.push_back(old_and_new_entity_pair<member_class>{&entity, new_class});

		return new_class;
	}

	enum_*
	create_entity
	(
		const enum_& entity,
		const final_graph_entities&
	)
	{
		enum_* new_enum = new enum_(entity.name());
		copy_constants(entity, *new_enum);
		return new_enum;
	}

	member_enum*
	create_entity
	(
		const member_enum& entity,
		const final_graph_entities&
	)
	{
		member_enum* new_enum = new member_enum(entity.name(), entity.access());
		copy_constants(entity, *new_enum);
		return new_enum;
	}

	template<class Enum>
	void
	copy_constants(const Enum& src, Enum& dest)
	{
		for(auto i = src.constants().begin(); i != src.constants().end(); ++i)
		{
			const enum_constant& current_enum_constant = *i;
			dest.add
			(
				std::unique_ptr<enum_constant>
				(
					new enum_constant
					(
						current_enum_constant.name(),
						current_enum_constant.value()
					)
				)
			);
		}
	}

	typedef_*
	create_entity
	(
		const typedef_& entity,
		const final_graph_entities& final_entities
	)
	{
		return new typedef_(entity.name(), create_type(entity.type(), final_entities));
	}

	member_typedef*
	create_entity
	(
		const member_typedef& entity,
		const final_graph_entities& final_entities
	)
	{
		return new member_typedef(entity.name(), create_type(entity.type(), final_entities), entity.access());
	}

	constructor*
	create_entity
	(
		const constructor& entity,
		const final_graph_entities& final_entities
	)
	{
		constructor* new_entity =
			new constructor
			(
				create_function_parameter_list(entity.parameters(), final_entities),
				entity.variadic(),
				entity.access(),
				entity.is_explicit(),
				entity.is_inline()
			)
		;

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	destructor*
	create_entity
	(
		const destructor& entity,
		const final_graph_entities&
	)
	{
		destructor* new_entity =
			new destructor
			(
				entity.access(),
				entity.is_virtual(),
				entity.is_inline()
			)
		;

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	operator_member_function*
	create_entity
	(
		const operator_member_function& entity,
		const final_graph_entities& final_entities
	)
	{
		operator_member_function* new_entity =
			new operator_member_function
			(
				entity.overloaded_operator(),
				create_type(entity.return_type(), final_entities),
				create_function_parameter_list(entity.parameters(), final_entities),
				entity.access(),
				entity.is_const(),
				entity.is_volatile(),
				entity.is_virtual(),
				entity.is_pure(),
				entity.is_inline()
			)
		;

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	conversion_function*
	create_entity
	(
		const conversion_function& entity,
		const final_graph_entities& final_entities
	)
	{
		conversion_function* new_entity =
			new conversion_function
			(
				create_type(entity.return_type(), final_entities),
				entity.access(),
				entity.is_const(),
				entity.is_volatile(),
				entity.is_explicit(),
				entity.is_virtual(),
				entity.is_pure(),
				entity.is_inline()
			)
		;

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	simple_member_function*
	create_entity
	(
		const simple_member_function& entity,
		const final_graph_entities& final_entities
	)
	{
		simple_member_function* new_entity =
			new simple_member_function
			(
				entity.name(),
				create_type(entity.return_type(), final_entities),
				create_function_parameter_list(entity.parameters(), final_entities),
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

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	operator_function*
	create_entity
	(
		const operator_function& entity,
		const final_graph_entities& final_entities
	)
	{
		operator_function* new_entity =
			new operator_function
			(
				entity.overloaded_operator(),
				create_type(entity.return_type(), final_entities),
				create_function_parameter_list(entity.parameters(), final_entities),
				entity.is_static(),
				entity.is_inline()
			)
		;

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	simple_function*
	create_entity
	(
		const simple_function& entity,
		const final_graph_entities& final_entities
	)
	{
		simple_function* new_entity =
			new simple_function
			(
				entity.name(),
				create_type(entity.return_type(), final_entities),
				create_function_parameter_list(entity.parameters(), final_entities),
				entity.variadic(),
				entity.is_static(),
				entity.is_inline()
			)
		;

		if(entity.defined())
			new_entity->body(std::unique_ptr<statement_block>(new statement_block()));

		return new_entity;
	}

	variable*
	create_entity
	(
		const variable& entity,
		const final_graph_entities& final_entities
	)
	{
		return
			new variable
			(
				entity.name(),
				create_type(entity.type(), final_entities)
			)
		;
	}

	member_variable*
	create_entity
	(
		const member_variable& entity,
		const final_graph_entities& final_entities
	)
	{
		return
			new member_variable
			(
				entity.name(),
				create_type(entity.type(), final_entities),
				entity.is_static(),
				entity.is_mutable(),
				entity.access()
			)
		;
	}

	bit_field*
	create_entity
	(
		const bit_field& entity,
		const final_graph_entities& final_entities
	)
	{
		return
			new bit_field
			(
				entity.name(),
				create_type(entity.type(), final_entities),
				entity.size(),
				entity.is_mutable(),
				entity.access()
			)
		;
	}



	function_type::parameter_types_t
	create_function_parameter_types
	(
		const function_type::parameter_types_t& parameter_types,
		const final_graph_entities& final_entities
	)
	{
		function_type::parameter_types_t new_parameter_types;

		for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
		{
			new_parameter_types.push_back(create_type(*i, final_entities));
		}

		return new_parameter_types;
	}

	function_parameter_list
	create_function_parameter_list
	(
		const function_parameter_list& entity,
		const final_graph_entities& final_entities
	)
	{
		function_parameter_list new_entity;

		for(auto i = entity.begin(); i != entity.end(); ++i)
		{
			new_entity.push_back(create_function_parameter(*i, final_entities));
		}

		return new_entity;
	}

	std::unique_ptr<function_parameter>
	create_function_parameter
	(
		const function_parameter& entity,
		const final_graph_entities& final_entities
	)
	{
		return std::unique_ptr<function_parameter>
		(
			new function_parameter
			(
				create_type(entity.type(), final_entities),
				entity.name()
			)
		);
	}



	struct find_final_class_visitor: utility::static_visitor<class_ptr_variant>
	{
		public:
			find_final_class_visitor(const final_graph_entities& final_entities):
				final_entities_(final_entities)
			{
			}

			template<class Class>
			class_ptr_variant
			operator()(const Class* base)
			{
				auto it = final_entities_.get_map_of_linked_type<Class>().find(base);
				assert(it != final_entities_.get_map_of_linked_type<Class>().end());
				return it->second;
			}

		private:
			const final_graph_entities& final_entities_;
	};

	base_class
	create_base_class
	(
		const base_class& entity,
		const final_graph_entities& final_entities
	)
	{
		find_final_class_visitor visitor(final_entities);

		return
			base_class
			(
				apply_visitor(visitor, entity.base()),
				entity.access(),
				entity.is_virtual()
			)
		;
	}



	struct create_type_visitor_struct: utility::static_visitor<type_variant>
	{
		public:
			create_type_visitor_struct(const final_graph_entities& final_entities):
				final_entities_(final_entities)
			{
			}

			type_variant
			operator()(const array& type) const
			{
				return array(type.size(), create_type(type.qualified_type(), final_entities_));
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
					create_type(type.return_type(), final_entities_),
					create_function_parameter_types(type.parameter_types(), final_entities_),
					type.variadic(),
					type.const_qualified(),
					type.volatile_qualified()
				);
			}

			type_variant
			operator()(const class_* type) const
			{
				auto it = final_entities_.classes.find(type);
				assert(it != final_entities_.classes.end());
				return it->second;
			}

			type_variant
			operator()(const member_class* type) const
			{
				auto it = final_entities_.member_classes.find(type);
				assert(it != final_entities_.member_classes.end());
				return it->second;
			}

			type_variant
			operator()(const cv_qualified_type& type) const
			{
				return cv_qualified_type
				(
					create_type(type.qualified_type(), final_entities_),
					type.qualification()
				);
			}

			type_variant
			operator()(const enum_* type) const
			{
				auto it = final_entities_.enums.find(type);
				assert(it != final_entities_.enums.end());
				return it->second;
			}

			type_variant
			operator()(const member_enum* type) const
			{
				auto it = final_entities_.member_enums.find(type);
				assert(it != final_entities_.member_enums.end());
				return it->second;
			}

			type_variant
			operator()(const pointer& type) const
			{
				return pointer(create_type(type.qualified_type(), final_entities_));
			}

			type_variant
			operator()(const pointer_to_member& type) const
			{
				find_final_class_visitor visitor(final_entities_);

				return pointer_to_member
				(
					create_type(type.qualified_type(), final_entities_),
					apply_visitor(visitor, type.parent_class())
				);
			}

			type_variant
			operator()(const reference& type) const
			{
				return reference(create_type(type.qualified_type(), final_entities_));
			}

		private:
			const final_graph_entities& final_entities_;
	};

	type_variant
	create_type
	(
		const type_variant& entity,
		const final_graph_entities& final_entities
	)
	{
		create_type_visitor_struct visitor(final_entities);
		return utility::apply_visitor(visitor, entity);
	}
}

namespace
{
	void
	create_global_namespace
	(
		const entity_groups& groups,
		final_graph_entities& final_entities
	)
	{
		//create the global namespace
		final_entities.global_namespace = std::unique_ptr<linked_namespace>(new linked_namespace());

		for(auto i = groups.global_namespaces.begin(); i != groups.global_namespaces.end(); ++i)
		{
			//add links between the old global namespaces and the new one
			final_entities.namespaces.insert(std::pair<const namespace_*, linked_namespace*>(*i, final_entities.global_namespace.get()));
		}
	}

	template<class Entity, bool ErrorIfMultipleDefinition = true>
	void
	create_entities_of_type
	(
		const typename detail::entity_groups_of_type<typename nonlinked_type<Entity>::type>::type& groups,
		final_graph_entities& final_entities
	)
	{
		typedef typename nonlinked_type<Entity>::type nonlinked_entity_t;

		for(auto i = groups.begin(); i != groups.end(); ++i) //for each group (1 group = 1 output entity)
		{
			const std::string group_id = i->first;
			const std::vector<const nonlinked_entity_t*>& group = i->second;

			//find a defined version of the entity
			const nonlinked_entity_t* defined_entity = 0;
			for(auto j = group.begin(); j != group.end(); ++j)
			{
				const nonlinked_entity_t* current_entity = *j;
				if(generic_queries::detail::is_defined(*current_entity))
				{
					if(defined_entity != 0 && ErrorIfMultipleDefinition)
						throw std::runtime_error(("multiple definition of " + group_id).c_str());
					defined_entity = current_entity;
				}
			}

			//select the first entity if no defined entity has been found
			const nonlinked_entity_t& selected_entity = defined_entity ? *defined_entity : *group.front();

			//create a new entity by copying the selected one
			Entity* new_entity = create_entity(selected_entity, final_entities);

			//add links between groups' entities and the new entity
			for(auto j = group.begin(); j != group.end(); ++j)
			{
				final_entities.get_map_of_linked_type<Entity>().insert(std::pair<const nonlinked_entity_t*, Entity*>(*j, new_entity));
			}
		}
	}

	template<class Entity>
	void
	create_internal_entities_of_type
	(
		const entity_groups& groups,
		final_graph_entities& final_entities
	)
	{
		typedef typename nonlinked_type<Entity>::type nonlinked_entity_t;

		std::vector<const nonlinked_entity_t*> entities = groups.internal_entities_of_type<nonlinked_entity_t>();
		for(auto i = entities.begin(); i != entities.end(); ++i) //for each entity
		{
			const nonlinked_entity_t& entity = **i;

			//create a new entity by copying the selected one
			Entity* new_entity = create_entity(entity, final_entities);

			//add a link between the nonlinked entity and the new linked one
			final_entities.get_map_of_linked_type<Entity>().insert
			(
				std::pair<const nonlinked_entity_t*, Entity*>
				(
					&entity,
					new_entity
				)
			);
		}
	}

	template<class Class>
	void
	add_base_classes(final_graph_entities& final_entities)
	{
		for(auto i = final_entities.get_pairs_of_type<Class>().begin(); i != final_entities.get_pairs_of_type<Class>().end(); ++i)
		{
			const Class& old_entity = *(i->old_entity);
			Class& new_entity = *(i->new_entity);

			for(auto j = old_entity.base_classes().begin(); j != old_entity.base_classes().end(); ++j)
			{
				const base_class& current_base_class = *j;
				new_entity.add_base_class(create_base_class(current_base_class, final_entities));
			}
		}
	}
}

void
create_final_graph_entities
(
	const entity_groups& groups,
	final_graph_entities& final_entities
)
{
	create_global_namespace(groups, final_entities);

	create_entities_of_type<linked_namespace, false>(groups.namespaces, final_entities);
	create_internal_entities_of_type<linked_namespace>(groups, final_entities);

	create_internal_entities_of_type<linked_unnamed_namespace>(groups, final_entities);

	create_entities_of_type<class_, false>(groups.classes, final_entities);
	create_internal_entities_of_type<class_>(groups, final_entities);

	create_entities_of_type<member_class, false>(groups.member_classes, final_entities);
	create_internal_entities_of_type<member_class>(groups, final_entities);

	create_entities_of_type<enum_, false>(groups.enums, final_entities);
	create_internal_entities_of_type<enum_>(groups, final_entities);

	create_entities_of_type<member_enum, false>(groups.member_enums, final_entities);
	create_internal_entities_of_type<member_enum>(groups, final_entities);

	create_entities_of_type<typedef_, false>(groups.typedefs, final_entities);
	create_internal_entities_of_type<typedef_>(groups, final_entities);

	create_entities_of_type<member_typedef, false>(groups.member_typedefs, final_entities);
	create_internal_entities_of_type<member_typedef>(groups, final_entities);

	create_entities_of_type<constructor>(groups.constructors, final_entities);
	create_internal_entities_of_type<constructor>(groups, final_entities);

	create_entities_of_type<destructor>(groups.destructors, final_entities);
	create_internal_entities_of_type<destructor>(groups, final_entities);

	create_entities_of_type<operator_member_function>(groups.operator_member_functions, final_entities);
	create_internal_entities_of_type<operator_member_function>(groups, final_entities);

	create_entities_of_type<conversion_function>(groups.conversion_functions, final_entities);
	create_internal_entities_of_type<conversion_function>(groups, final_entities);

	create_entities_of_type<simple_member_function>(groups.simple_member_functions, final_entities);
	create_internal_entities_of_type<simple_member_function>(groups, final_entities);

	create_entities_of_type<operator_function>(groups.operator_functions, final_entities);
	create_internal_entities_of_type<operator_function>(groups, final_entities);

	create_entities_of_type<simple_function>(groups.simple_functions, final_entities);
	create_internal_entities_of_type<simple_function>(groups, final_entities);

	create_entities_of_type<variable>(groups.variables, final_entities);
	create_internal_entities_of_type<variable>(groups, final_entities);

	create_entities_of_type<member_variable>(groups.member_variables, final_entities);
	create_internal_entities_of_type<member_variable>(groups, final_entities);

	create_entities_of_type<bit_field>(groups.bit_fields, final_entities);
	create_internal_entities_of_type<bit_field>(groups, final_entities);

	add_base_classes<class_>(final_entities);
	add_base_classes<member_class>(final_entities);
}

}}}} //namespace scalpel::cpp::linkage::detail

