/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "class_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "name_lookup.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

std::shared_ptr<class_>
create_class(const class_specifier& class_specifier_node)
{
	//get the name of the class
	std::string class_name;
	const optional_node<identifier_or_template_id>& opt_id_or_templ = get_identifier_or_template_id(get_class_head(class_specifier_node));
	if(opt_id_or_templ)
	{
		const boost::optional<const identifier&> id = get<identifier>(&*opt_id_or_templ);

		if(id)
		{
			class_name = id->value();
		}
	}

	//create the class
	return class_::make_shared(class_name);
}

std::shared_ptr<semantic_entities::class_>
create_class(const class_elaborated_specifier& class_elaborated_specifier_node)
{
	//get the name of the class
	std::string class_name;
	const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(class_elaborated_specifier_node);

	if(const boost::optional<const identifier&> opt_identifier_node = get<identifier>(&identifier_or_template_id_node))
	{
		class_name = opt_identifier_node->value();
	}

	//create the class
	assert(class_name != "");
	return class_::make_shared(class_name);
}

void
fill_class
(
	std::shared_ptr<class_> class_entity,
	const class_specifier& class_specifier_node
)
{
	auto class_head_node = get_class_head(class_specifier_node);

	//get base classes
	if(auto opt_base_clause_node = get_base_clause(class_head_node))
	{
		auto base_specifier_list_node = get_base_specifier_list(*opt_base_clause_node);
		for
		(
			auto i = base_specifier_list_node.begin();
			i != base_specifier_list_node.end();
			++i
		)
		{
			auto base_specifier_node = i->main_node();
			auto nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);

			//is it virtual inheritance?
			bool is_virtual = has_virtual_keyword(base_specifier_node);

			//get base class access
			class_::access access = class_::access::PRIVATE; //if nothing is specified, the access is private
			if(auto opt_access_specifier_node = get_access_specifier(base_specifier_node))
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
			std::shared_ptr<class_> base_class =
				name_lookup::find
				<
					semantic_entity_analysis::identification_policies::by_name,
					false,
					false,
					class_
				>
				(
					has_leading_double_colon(nested_identifier_or_template_id_node),
					get_nested_name_specifier(nested_identifier_or_template_id_node),
					base_class_name,
					class_entity
				)
			;

			class_entity->add_base_class(base_class, access, is_virtual);
		}
	}

	//default current_access
	auto class_key_node = get_class_key(class_head_node);
	class_::access current_access = class_::access::PUBLIC; //the default current_access is public...
	if(get<predefined_text_node<str::class_>>(&class_key_node)) //... unless the syntax node represents a class (neither a struct nor a union)
	{
		current_access = class_::access::PRIVATE;
	}

	//get the members of the class
	auto opt_member_specification = get_member_specification(class_specifier_node);
	if(opt_member_specification)
	{
		auto member_specification_node = *opt_member_specification;
		for(auto i = member_specification_node.begin(); i != member_specification_node.end(); ++i) //for each part
		{
			auto part = i->main_node();

			if(auto opt_member_declaration_node = get<member_declaration>(&part))
			{
				if(auto opt_member_declaration_function_definition_node = get<member_declaration_function_definition>(&*opt_member_declaration_node))
				{
					auto function_definition_node = get_function_definition(*opt_member_declaration_function_definition_node);
					//analyze(function_definition_node, class_entity);
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
}

void
fill_class
(
	const std::shared_ptr<semantic_entities::class_> class_entity,
	const class_::access current_access,
	const syntax_nodes::member_declaration_member_declarator_list& member_declaration_member_declarator_list_node
)
{
	boost::optional<type_shared_ptr_variant> opt_unqualified_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_virtual_specifier = false;
	bool has_explicit_specifier = false;
	bool has_mutable_specifier = false;

	if
	(
		const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
			get_decl_specifier_seq(member_declaration_member_declarator_list_node)
	)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = syntax_node_analysis::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = syntax_node_analysis::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = syntax_node_analysis::has_inline_specifier(decl_specifier_seq_node);
		has_virtual_specifier = syntax_node_analysis::has_virtual_specifier(decl_specifier_seq_node);
		has_explicit_specifier = syntax_node_analysis::has_explicit_specifier(decl_specifier_seq_node);
		has_mutable_specifier = syntax_node_analysis::has_mutable_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case syntax_node_analysis::type_specifier_seq_type::CLASS_DECLARATION:
			{
				const syntax_nodes::class_specifier& class_specifier_node =
					syntax_node_analysis::get_class_specifier(decl_specifier_seq_node)
				;

				std::shared_ptr<class_> new_class = create_class(class_specifier_node);
				class_entity->add_member(new_class, current_access);
				fill_class(new_class, class_specifier_node);

				opt_unqualified_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
				class_entity->add_member(new_class, current_access);

				opt_unqualified_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_unqualified_type = create_type(decl_specifier_seq_node, class_entity);
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
			auto member_declarator_node = j->main_node();
			if(auto opt_member_declarator_declarator_node = get<member_declarator_declarator>(&member_declarator_node))
			{
				auto member_declarator_declarator_node = *opt_member_declarator_declarator_node;
				auto declarator_node = get_declarator(member_declarator_declarator_node);

				declarator_entity_shared_ptr_variant declarator_entity = create_entity
				(
					declarator_node,
					class_entity,
					opt_unqualified_type,
					has_typedef_specifier,
					has_static_specifier,
					has_inline_specifier,
					has_virtual_specifier,
					has_explicit_specifier,
					true
				);

				if(auto opt_constructor_entity = get<constructor>(&declarator_entity))
					class_entity->add_member
					(
						*opt_constructor_entity,
						current_access
					);
				else if(auto opt_destructor_entity = get<destructor>(&declarator_entity))
					class_entity->set_destructor
					(
						*opt_destructor_entity,
						current_access
					);
				else if(auto opt_operator_function_entity = get<operator_member_function>(&declarator_entity))
					class_entity->add_member
					(
						*opt_operator_function_entity,
						current_access
					);
				else if(auto opt_conversion_function_entity = get<conversion_function>(&declarator_entity))
					class_entity->add_member
					(
						*opt_conversion_function_entity,
						current_access
					);
				else if(auto opt_simple_function_entity = get<simple_member_function>(&declarator_entity))
					class_entity->add_member
					(
						*opt_simple_function_entity,
						current_access
					);
				else if(auto opt_variable_entity = get<variable>(&declarator_entity))
					class_entity->add_member
					(
						*opt_variable_entity,
						current_access,
						has_mutable_specifier
					);
				else if(auto opt_typedef_entity = get<typedef_>(&declarator_entity))
					class_entity->add_member
					(
						*opt_typedef_entity,
						current_access
					);
				else
					assert(false);
			}
		}
	}
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

