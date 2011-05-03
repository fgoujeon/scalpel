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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CLASS_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_CLASS_CONSTRUCTION_IPP

#include "enum_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "name_lookup.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"
#include "syntax_node_analysis/function_definition.hpp"
#include "syntax_node_analysis/class_specifier.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include "syntax_node_analysis/misc.hpp"
#include <scalpel/cpp/semantic_entities/generic_queries/detail/add_entity_to_declarative_region.hpp>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class Class>
std::unique_ptr<Class>
create_class(const syntax_nodes::class_specifier& class_specifier_node)
{
	return std::unique_ptr<Class>(new Class(syntax_node_analysis::get_identifier(class_specifier_node)));
}

template<class Class>
std::unique_ptr<Class>
create_member_class
(
	const syntax_nodes::class_specifier& class_specifier_node,
	const semantic_entities::member_access access
)
{
	return
		std::unique_ptr<Class>
		(
			new Class
			(
				syntax_node_analysis::get_identifier(class_specifier_node),
				access
			)
		)
	;
}

template<class Class>
std::unique_ptr<Class>
create_class
(
	const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//get the name of the class
	std::string class_name;
	const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(class_elaborated_specifier_node);

	if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
	{
		class_name = opt_identifier_node->value();
	}

	//create the class
	assert(class_name != "");
	return std::unique_ptr<Class>(new Class(class_name));
}

template<class Class>
std::unique_ptr<Class>
create_member_class
(
	const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node,
	const semantic_entities::member_access access
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//get the name of the class
	std::string class_name;
	const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(class_elaborated_specifier_node);

	if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
	{
		class_name = opt_identifier_node->value();
	}

	//create the class
	assert(class_name != "");
	return std::unique_ptr<Class>(new Class(class_name, access));
}

template<class Class>
void
fill_class
(
	Class& class_entity,
	const syntax_nodes::class_specifier& class_specifier_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	auto class_head_node = get_class_head(class_specifier_node);
	auto class_key_node = get_class_key(class_head_node);

	//default access: public for structs and unions, private for classes
	const member_access default_access =
		get<predefined_text_node<str::class_>>(&class_key_node) ?
		member_access::PRIVATE :
		member_access::PUBLIC
	;

	//get base classes
	if(const optional_node<base_clause>& opt_base_clause_node = get_base_clause(class_head_node))
	{
		fill_class(class_entity, default_access, *opt_base_clause_node);
	}

	//get the members of the class
	member_access current_access = default_access;
	auto opt_member_specification = get_member_specification(class_specifier_node);
	if(opt_member_specification)
	{
		auto member_specification_node = *opt_member_specification;
		for(auto i = member_specification_node.begin(); i != member_specification_node.end(); ++i) //for each part
		{
			auto part = *i;

			if(auto opt_member_declaration_node = get<member_declaration>(&part))
			{
				if(auto opt_member_declaration_function_definition_node = get<member_declaration_function_definition>(&*opt_member_declaration_node))
				{
					auto function_definition_node = get_function_definition(*opt_member_declaration_function_definition_node);
					fill_class
					(
						class_entity,
						current_access,
						function_definition_node
					);
				}
				else if(auto opt_member_declaration_member_declarator_list_node = get<member_declaration_member_declarator_list>(&*opt_member_declaration_node))
				{
					fill_class
					(
						class_entity,
						current_access,
						*opt_member_declaration_member_declarator_list_node
					);
				}
				else if(auto opt_member_declaration_unqualified_id_node = get<member_declaration_unqualified_id>(&*opt_member_declaration_node))
				{
				}
				else if(auto opt_using_declaration_node = get<using_declaration>(&*opt_member_declaration_node))
				{
					fill_class
					(
						class_entity,
						current_access,
						*opt_using_declaration_node
					);
				}
				else if(auto opt_template_declaration_node = get<template_declaration>(&*opt_member_declaration_node))
				{
				}
				else
				{
					assert(false);
				}
			}
			else if(auto opt_member_specification_access_specifier_node = get<member_specification_access_specifier>(&part))
			{
				auto access_specifier_node = get_access_specifier(*opt_member_specification_access_specifier_node);
				current_access = syntax_node_analysis::get_access(access_specifier_node);
			}
			else
			{
				assert(false);
			}
		}
	}

	class_entity.complete(true);
}

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access default_access,
	const syntax_nodes::base_clause& base_clause_node,
	typename boost::enable_if<semantic_entities::type_traits::has_base_classes<Class>>::type*
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const base_specifier_list& base_specifier_list_node = get_base_specifier_list(base_clause_node);
	for
	(
		auto i = base_specifier_list_node.begin();
		i != base_specifier_list_node.end();
		++i
	)
	{
		const base_specifier& base_specifier_node = *i;
		const nested_identifier_or_template_id& nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);

		//is it virtual inheritance?
		bool is_virtual = has_virtual_keyword(base_specifier_node);

		//get base class access
		member_access access = default_access;
		if(const optional_node<access_specifier>& opt_access_specifier_node = get_access_specifier(base_specifier_node))
		{
			access = syntax_node_analysis::get_access(*opt_access_specifier_node);
		}

		//get base class name
		std::string base_class_name;
		const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(nested_identifier_or_template_id_node);
		if(boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
			base_class_name = opt_identifier_node->value();
		else
			assert(false); //not managed yet

		//get base class
		typename utility::ptr_variant<class_, member_class>::type base =
			name_lookup::find
			<
				semantic_entity_analysis::identification_policies::by_name,
				false,
				false,
				class_,
				member_class
			>
			(
				has_leading_double_colon(nested_identifier_or_template_id_node),
				get_nested_name_specifier(nested_identifier_or_template_id_node),
				base_class_name,
				&class_entity
			)
		;

		class_entity.add_base_class(base_class(base, access, is_virtual));
	}
}

template<class Class>
void
fill_class
(
	Class&,
	const semantic_entities::member_access,
	const syntax_nodes::base_clause&,
	typename boost::disable_if<semantic_entities::type_traits::has_base_classes<Class>>::type*
)
{
	std::ostringstream oss;
	oss << "A union cannot have base classes.";
	throw std::runtime_error(oss.str().c_str());
}

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access current_access,
	const syntax_nodes::member_declaration_member_declarator_list& member_declaration_member_declarator_list_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	boost::optional<type_variant> opt_unqualified_type;
	bool has_typedef_specifier = false;
	bool has_friend_specifier = false;
	bool has_mutable_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_virtual_specifier = false;
	bool has_explicit_specifier = false;

	if
	(
		const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
			get_decl_specifier_seq(member_declaration_member_declarator_list_node)
	)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = syntax_node_analysis::has_typedef_specifier(decl_specifier_seq_node);
		has_friend_specifier = syntax_node_analysis::has_friend_specifier(decl_specifier_seq_node);
		has_mutable_specifier = syntax_node_analysis::has_mutable_specifier(decl_specifier_seq_node);
		has_static_specifier = syntax_node_analysis::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = syntax_node_analysis::has_inline_specifier(decl_specifier_seq_node);
		has_virtual_specifier = syntax_node_analysis::has_virtual_specifier(decl_specifier_seq_node);
		has_explicit_specifier = syntax_node_analysis::has_explicit_specifier(decl_specifier_seq_node);

		//friend specifications are not implemented yet
		if(has_friend_specifier) return;

		//create and/or get undecorated type
		switch(syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case syntax_node_analysis::type_specifier_seq_type::CLASS_DECLARATION:
			{
				const class_specifier& class_specifier_node =
					syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
				;
				const class_head& class_head_node = get_class_head(class_specifier_node);
				const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
					get_nested_name_specifier(class_head_node)
				;

				if(opt_nested_name_specifier_node)
				{
					//find the class
					class_* found_class =
						name_lookup::find<semantic_entity_analysis::identification_policies::by_name, false, false, class_>
						(
							false,
							opt_nested_name_specifier_node,
							syntax_node_analysis::get_identifier(class_specifier_node),
							&class_entity,
							false
						)
					;

					//and define it
					fill_class(*found_class, class_specifier_node);

					opt_unqualified_type = found_class;
				}
				else
				{
					std::unique_ptr<member_class> new_class = create_member_class<member_class>(class_specifier_node, current_access);
					member_class& added_class = add_class(class_entity, std::move(new_class));
					fill_class(added_class, class_specifier_node);

					opt_unqualified_type = &added_class;
				}

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::unique_ptr<member_class> new_class = create_member_class<member_class>(class_elaborated_specifier_node, current_access);
				member_class& added_class = add_class(class_entity, std::move(new_class));

				opt_unqualified_type = &added_class;

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::UNION_DECLARATION:
			{
				const class_specifier& class_specifier_node =
					syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
				;
				const class_head& class_head_node = get_class_head(class_specifier_node);
				const optional_node<nested_name_specifier>& opt_nested_name_specifier_node =
					get_nested_name_specifier(class_head_node)
				;

				if(opt_nested_name_specifier_node)
				{
					//find the class
					member_union* found_union =
						name_lookup::find<semantic_entity_analysis::identification_policies::by_name, false, false, member_union>
						(
							false,
							opt_nested_name_specifier_node,
							syntax_node_analysis::get_identifier(class_specifier_node),
							&class_entity,
							false
						)
					;

					//and define it
					fill_class(*found_union, class_specifier_node);

					opt_unqualified_type = found_union;
				}
				else
				{
					std::unique_ptr<member_union> new_union = create_member_class<member_union>(class_specifier_node, current_access);
					member_union& added_union = add_class(class_entity, std::move(new_union));
					fill_class(added_union, class_specifier_node);

					opt_unqualified_type = &added_union;
				}

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::UNION_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::unique_ptr<member_union> new_union = create_member_class<member_union>(class_elaborated_specifier_node, current_access);
				member_union& added_union = add_class(class_entity, std::move(new_union));

				opt_unqualified_type = &added_union;

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::ENUMERATION_DECLARATION:
			{
				const enum_specifier& enum_specifier_node =
					syntax_node_analysis::get_enum_specifier(decl_specifier_seq_node)
				;

				std::unique_ptr<member_enum> new_enum = create_member_enum(enum_specifier_node, current_access);
				member_enum& new_enum_ref = *new_enum;
				class_entity.add_member(std::move(new_enum));
				fill_enum(new_enum_ref, enum_specifier_node);

				opt_unqualified_type = &new_enum_ref;

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_unqualified_type = create_type(decl_specifier_seq_node, &class_entity);
				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//qualify type
		if(opt_unqualified_type)
			opt_unqualified_type = qualify_type(*opt_unqualified_type, decl_specifier_seq_node);
	}

	if
	(
		const optional_node<member_declarator_list>& opt_member_declarator_list_node =
			get_member_declarator_list(member_declaration_member_declarator_list_node)
	)
	{
		auto member_declarator_list_node = *opt_member_declarator_list_node;

		for
		(
			auto j = member_declarator_list_node.begin();
			j != member_declarator_list_node.end();
			++j
		)
		{
			auto member_declarator_node = *j;
			if(auto opt_member_declarator_declarator_node = get<member_declarator_declarator>(&member_declarator_node))
			{
				auto member_declarator_declarator_node = *opt_member_declarator_declarator_node;
				auto declarator_node = get_declarator(member_declarator_declarator_node);

				const bool has_pure_specifier = syntax_node_analysis::has_pure_specifier(member_declarator_declarator_node);

				declarator_entity_ptr_variant declarator_entity = create_entity
				(
					declarator_node,
					&class_entity,
					opt_unqualified_type,
					has_typedef_specifier,
					has_mutable_specifier,
					has_static_specifier,
					has_inline_specifier,
					has_virtual_specifier,
					has_explicit_specifier,
					has_pure_specifier,
					true,
					current_access
				);

				if(auto opt_constructor_entity = get<constructor*>(&declarator_entity))
					generic_queries::detail::add_entity_to_declarative_region(class_entity, std::unique_ptr<constructor>(*opt_constructor_entity));
				else if(auto opt_destructor_entity = get<destructor*>(&declarator_entity))
					generic_queries::detail::add_entity_to_declarative_region(class_entity, std::unique_ptr<destructor>(*opt_destructor_entity));
				else if(auto opt_operator_function_entity = get<operator_member_function*>(&declarator_entity))
					generic_queries::detail::add_entity_to_declarative_region(class_entity, std::unique_ptr<operator_member_function>(*opt_operator_function_entity));
				else if(auto opt_conversion_function_entity = get<conversion_function*>(&declarator_entity))
					generic_queries::detail::add_entity_to_declarative_region(class_entity, std::unique_ptr<conversion_function>(*opt_conversion_function_entity));
				else if(auto opt_simple_function_entity = get<simple_member_function*>(&declarator_entity))
					generic_queries::detail::add_entity_to_declarative_region(class_entity, std::unique_ptr<simple_member_function>(*opt_simple_function_entity));
				else if(auto opt_variable_entity = get<member_variable*>(&declarator_entity))
					class_entity.add_member(std::unique_ptr<member_variable>(*opt_variable_entity));
				else if(auto opt_typedef_entity = get<member_typedef*>(&declarator_entity))
					class_entity.add_member(std::unique_ptr<member_typedef>(*opt_typedef_entity));
				else
					assert(false);
			}
			else if
			(
				boost::optional<const member_declarator_bit_field_member&> opt_member_declarator_bit_field_member_node =
					get<member_declarator_bit_field_member>(&member_declarator_node)
			)
			{
				assert(opt_unqualified_type);

				class_entity.add_member
				(
					create_bit_field
					(
						*opt_member_declarator_bit_field_member_node,
						*opt_unqualified_type,
						has_mutable_specifier,
						current_access,
						class_entity
					)
				);
			}
			else
			{
				assert(false);
			}
		}
	}
}

namespace
{
	template<class Class>
	class add_function_to_class_visitor: public utility::static_visitor<void>
	{
		public:
			add_function_to_class_visitor(Class& class_entity):
				class_entity_(class_entity)
			{
			}

			template<class T>
			void
			operator()(T* function_entity) const
			{
				semantic_entities::generic_queries::detail::add_entity_to_declarative_region(class_entity_, std::unique_ptr<T>(function_entity));
			}

		private:
			Class& class_entity_;
	};
}

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access access,
	const syntax_nodes::function_definition& function_definition_node
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//make sure the function's name isn't qualified
	const declarator& declarator_node = syntax_node_analysis::get_declarator(function_definition_node);
	const bool has_leading_double_colon = syntax_node_analysis::has_leading_double_colon(declarator_node);
	const syntax_nodes::optional_node<syntax_nodes::nested_name_specifier>& opt_nested_name_specifier_node =
		syntax_node_analysis::get_nested_name_specifier(declarator_node)
	;
	if(has_leading_double_colon || opt_nested_name_specifier_node)
		throw std::runtime_error("error: invalid use of '::'");

	//create the function
	function_ptr_variant function_entity = create_function
	(
		function_definition_node,
		&class_entity,
		true,
		true,
		access
	);

	//add the function to the class
	add_function_to_class_visitor<Class> visitor(class_entity);
	utility::apply_visitor(visitor, function_entity);

	//define the function
	define_function
	(
		function_entity,
		function_definition_node,
		&class_entity
	);
}

template<class Class>
void
fill_class
(
	Class& class_entity,
	const semantic_entities::member_access access,
	const syntax_nodes::using_declaration& using_declaration_node,
	typename boost::enable_if<semantic_entities::type_traits::has_entity_aliases<Class>>::type*
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const unqualified_id& unqualified_id_node = get_unqualified_id(using_declaration_node);
	const optional_node<nested_name_specifier>& opt_nested_name_specifier_node = get_nested_name_specifier(using_declaration_node);

	if(has_typename_keyword(using_declaration_node))
		assert(false); //not implemented yet

	//find the designated entity(ies)'s declarative region
	open_declarative_region_ptr_variant found_declarative_region =
		name_lookup::find_declarative_region
		(
			has_leading_double_colon(using_declaration_node),
			opt_nested_name_specifier_node,
			&class_entity
		)
	;

	//find the designated entity(ies)
	if(boost::optional<const identifier&> opt_identifier_node = get<identifier>(&unqualified_id_node))
	{
		//first, try to find a class, enum, typedef or variable
		typename boost::optional<utility::ptr_variant<member_class, member_enum, member_typedef, member_variable, bit_field>::type> found_entity =
			name_lookup::find_local
			<
				semantic_entity_analysis::identification_policies::by_name,
				open_declarative_region_ptr_variant,
				true,
				false,
				member_class, member_enum, member_typedef, member_variable, bit_field
			>
			(
				opt_identifier_node->value(),
				found_declarative_region
			)
		;

		if(found_entity) //if an entity has been found
		{
			//add the entity alias to the class
			add_alias(class_entity, *found_entity, access);
		}
		else
		{
			//if no entity has been found, try to find functions
			std::set<simple_member_function*> found_entities =
				name_lookup::find_local
				<
					semantic_entity_analysis::identification_policies::by_name,
					open_declarative_region_ptr_variant,
					false,
					true,
					simple_member_function
				>
				(
					opt_identifier_node->value(),
					found_declarative_region
				)
			;

			//add the functions to the class (as entity aliases)
			for(auto i = found_entities.begin(); i != found_entities.end(); ++i)
			{
				simple_member_function& entity = **i;
				class_entity.add_member(member_entity_alias<simple_member_function>(entity, access));
			}
		}
	}
	else if(boost::optional<const operator_function_id&> opt_operator_function_id_node = get<operator_function_id>(&unqualified_id_node))
	{
		std::set<operator_member_function*> found_entities =
			name_lookup::find_local
			<
				semantic_entity_analysis::identification_policies::by_overloaded_operator,
				open_declarative_region_ptr_variant,
				false,
				true,
				operator_member_function
			>
			(
				get_operator_function_operator(get_operator(*opt_operator_function_id_node)),
				found_declarative_region
			)
		;

		//add the functions to the class (as entity aliases)
		for(auto i = found_entities.begin(); i != found_entities.end(); ++i)
		{
			operator_member_function& entity = **i;
			class_entity.add_member(member_entity_alias<operator_member_function>(entity, access));
		}
	}
	else if(boost::optional<const conversion_function_id&> opt_conversion_function_id_node = get<conversion_function_id>(&unqualified_id_node))
	{
		std::set<conversion_function*> found_entities =
			name_lookup::find_local
			<
				semantic_entity_analysis::identification_policies::by_return_type,
				open_declarative_region_ptr_variant,
				false,
				true,
				conversion_function
			>
			(
				get_conversion_function_type(*opt_conversion_function_id_node, &class_entity),
				found_declarative_region
			)
		;

		//add the functions to the class (as entity aliases)
		for(auto i = found_entities.begin(); i != found_entities.end(); ++i)
		{
			conversion_function& entity = **i;
			class_entity.add_member(member_entity_alias<conversion_function>(entity, access));
		}
	}
	else
	{
		assert(false); //not implemented yet
	}
}

template<class Class>
void
fill_class
(
	Class&,
	const semantic_entities::member_access,
	const syntax_nodes::using_declaration&,
	typename boost::disable_if<semantic_entities::type_traits::has_entity_aliases<Class>>::type*
)
{
	std::ostringstream oss;
	oss << "A union cannot have using declarations.";
	throw std::runtime_error(oss.str().c_str());
}

template<class ParentClass>
semantic_entities::member_class&
add_class
(
	ParentClass& parent_class_entity,
	std::unique_ptr<semantic_entities::member_class>&& class_entity
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	typename ParentClass::classes_t::range classes = parent_class_entity.classes();
	for(auto i = classes.begin(); i != classes.end(); ++i)
	{
		member_class& current_class = *i;
		if(!current_class.complete() && current_class.name() == class_entity->name())
			return current_class;
	}

	member_class& class_entity_ref = *class_entity;
	parent_class_entity.add_member(std::move(class_entity));
	return class_entity_ref;
}



template<class Class>
class add_alias_to_class_visitor: public utility::static_visitor<void>
{
	public:
		add_alias_to_class_visitor
		(
			Class& class_entity,
			const semantic_entities::member_access access
		):
			class_entity_(class_entity),
			access_(access)
		{
		}

		template<class Entity>
		void
		operator()(Entity* entity)
		{
			class_entity_.add_member(semantic_entities::member_entity_alias<Entity>(*entity, access_));
		}

	private:
		Class& class_entity_;
		const semantic_entities::member_access access_;
};

template<class Class, class... Entities>
void
add_alias
(
	Class& class_entity,
	const utility::variant<Entities...>& entity,
	const semantic_entities::member_access access
)
{
	add_alias_to_class_visitor<Class> visitor(class_entity, access);
	apply_visitor(visitor, entity);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

