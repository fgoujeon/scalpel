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

#include "semantic_analysis.hpp"
#include "detail/semantic_analysis/name_lookup.hpp"
#include "detail/semantic_analysis/basic_functions.hpp"
#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp
{

namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;
namespace detail = detail::semantic_analysis;

std::shared_ptr<semantic_graph>
analyze(const syntax_tree& tree)
{
	//create semantic graph
	std::shared_ptr<namespace_> global_namespace = namespace_::make_shared();

	auto opt_declaration_seq_node = get_declaration_seq(tree);
	if(opt_declaration_seq_node)
	{
		auto declaration_seq_node = *opt_declaration_seq_node;
		fill_namespace(global_namespace, declaration_seq_node);
	}

	return global_namespace;
}

std::shared_ptr<semantic_entities::namespace_>
create_namespace
(
	const syntax_nodes::namespace_definition& namespace_definition_node
)
{
	//get the name of the namespace
	std::string namespace_name;
	const optional_node<identifier>& identifier_node = get_identifier(namespace_definition_node);
	if(identifier_node)
	{
		namespace_name = identifier_node->value();
	}

	//create the namespace entity
	return namespace_::make_shared(namespace_name);
}

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::namespace_definition& namespace_definition_node
)
{
	const optional_node<declaration_seq>& opt_declaration_seq_node = get_declaration_seq(namespace_definition_node);
	if(opt_declaration_seq_node)
		fill_namespace(namespace_entity, *opt_declaration_seq_node);
}

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::declaration_seq& declaration_seq_node
)
{
	//add the declarations of the namespace definition in the namespace semantic entity
	for(auto i = declaration_seq_node.begin(); i != declaration_seq_node.end(); ++i)
	{
		auto declaration_node = i->main_node();

		if(const boost::optional<const block_declaration&> opt_block_declaration_node = get<block_declaration>(&declaration_node))
		{
			const block_declaration& block_declaration_node = *opt_block_declaration_node;

			if(const boost::optional<const simple_declaration&> opt_simple_declaration_node = get<simple_declaration>(&block_declaration_node))
				fill_namespace(namespace_entity, *opt_simple_declaration_node);
			//else if(const boost::optional<const asm_definition&> opt_asm_definition_node = get<asm_definition>(&block_declaration_node))
			//	analyze(*opt_asm_definition_node, namespace_entity);
			else if(const boost::optional<const namespace_alias_definition&> opt_namespace_alias_definition_node = get<namespace_alias_definition>(&block_declaration_node))
			{
				std::shared_ptr<namespace_alias> new_namespace_alias = create_namespace_alias(*opt_namespace_alias_definition_node, namespace_entity);
				namespace_entity->add_member(new_namespace_alias);
			}
			//else if(const boost::optional<const using_declaration&> opt_using_declaration_node = get<using_declaration>(&block_declaration_node))
			//	analyze(*opt_using_declaration_node, namespace_entity);
			else if(const boost::optional<const using_directive&> opt_using_directive_node = get<using_directive>(&block_declaration_node))
			{
				std::shared_ptr<namespace_> new_using_directive = create_using_directive(*opt_using_directive_node, namespace_entity);
				namespace_entity->add_using_directive_namespace(new_using_directive);
			}
		}
		else if(const boost::optional<const function_definition&> opt_function_definition_node = get<function_definition>(&declaration_node))
			analyze(*opt_function_definition_node, namespace_entity);
		//else if(const boost::optional<const template_declaration&> opt_template_declaration_node = get<template_declaration>(&declaration_node))
		//	analyze(*opt_template_declaration_node, namespace_entity);
		//else if(const boost::optional<const explicit_instantiation&> opt_explicit_instantiation_node = get<explicit_instantiation>(&declaration_node))
		//	analyze(*opt_explicit_instantiation_node, namespace_entity);
		//else if(const boost::optional<const explicit_specialization&> opt_explicit_specialization_node = get<explicit_specialization>(&declaration_node))
		//	analyze(*opt_explicit_specialization_node, namespace_entity);
		//else if(const boost::optional<const linkage_specification&> opt_linkage_specification_node = get<linkage_specification>(&declaration_node))
		//	analyze(*opt_linkage_specification_node, namespace_entity);
		else if(const boost::optional<const namespace_definition&> opt_namespace_definition_node = get<namespace_definition>(&declaration_node))
		{
			std::shared_ptr<namespace_> new_namespace = create_namespace(*opt_namespace_definition_node);
			namespace_entity->add_member(new_namespace);
			fill_namespace(new_namespace, *opt_namespace_definition_node);
		}
	}
}

void
fill_namespace
(
	std::shared_ptr<semantic_entities::namespace_> namespace_entity,
	const syntax_nodes::simple_declaration& simple_declaration_node
)
{
	boost::optional<type_shared_ptr_variant> opt_undecorated_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_explicit_specifier = false;

	if(const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node))
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = detail::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = detail::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = detail::has_inline_specifier(decl_specifier_seq_node);
		has_explicit_specifier = detail::has_explicit_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(detail::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case detail::type_specifier_seq_type::CLASS_DECLARATION:
			{
				const syntax_nodes::class_specifier& class_specifier_node = detail::get_class_specifier(decl_specifier_seq_node);

				std::shared_ptr<class_> new_class = create_class(class_specifier_node);
				namespace_entity->add_member(new_class);
				fill_class(new_class, class_specifier_node);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case detail::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node = detail::get_class_elaborated_specifier(decl_specifier_seq_node);

				std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
				namespace_entity->add_member(new_class);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case detail::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_undecorated_type = create_type(decl_specifier_seq_node, namespace_entity);
				break;
			}
			case detail::type_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//decorate type
		if(opt_undecorated_type)
			opt_undecorated_type = decorate_type(*opt_undecorated_type, decl_specifier_seq_node);
	}

	if(const optional_node<init_declarator_list>& opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node))
	{
		const init_declarator_list& init_declarator_list_node = *opt_init_declarator_list_node;

		for(auto i = init_declarator_list_node.begin(); i != init_declarator_list_node.end(); ++i)
		{
			const init_declarator& init_declarator_node = i->main_node();
			const declarator& declarator_node = get_declarator(init_declarator_node);

			declarator_entity_shared_ptr_variant declarator_entity = create_entity
			(
				declarator_node,
				namespace_entity,
				opt_undecorated_type,
				has_typedef_specifier,
				has_static_specifier,
				has_inline_specifier,
				has_explicit_specifier
			);

			if(auto opt_simple_function_entity = get<std::shared_ptr<simple_function>>(&declarator_entity))
				namespace_entity->add_member(*opt_simple_function_entity);
			else if(auto opt_operator_function_entity = get<std::shared_ptr<operator_function>>(&declarator_entity))
				namespace_entity->add_member(*opt_operator_function_entity);
			else if(auto opt_variable_entity = get<std::shared_ptr<variable>>(&declarator_entity))
				namespace_entity->add_member(*opt_variable_entity);
			else if(auto opt_typedef_entity = get<std::shared_ptr<typedef_>>(&declarator_entity))
				namespace_entity->add_member(*opt_typedef_entity);
			else
				assert(false);
		}
	}
}

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

			//is it virtual inheritance?
			bool is_virtual = has_virtual_keyword(base_specifier_node);

			//get base class access
			class_::access access = class_::access::PRIVATE; //if nothing is specified, the access is private
			if(auto opt_access_specifier_node = get_access_specifier(base_specifier_node))
			{
				access = detail::get_access(*opt_access_specifier_node);
			}

			//get base class
			auto nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);
			std::shared_ptr<class_> base_class =
				detail::name_lookup::find<class_, false, false>(nested_identifier_or_template_id_node, class_entity)
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
				current_access = detail::get_access(access_specifier_node);
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
	boost::optional<type_shared_ptr_variant> opt_undecorated_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_explicit_specifier = false;
	bool has_virtual_specifier = false;
	bool has_mutable_specifier = false;

	if
	(
		const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
			get_decl_specifier_seq(member_declaration_member_declarator_list_node)
	)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = detail::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = detail::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = detail::has_inline_specifier(decl_specifier_seq_node);
		has_explicit_specifier = detail::has_explicit_specifier(decl_specifier_seq_node);
		has_virtual_specifier = detail::has_virtual_specifier(decl_specifier_seq_node);
		has_mutable_specifier = detail::has_mutable_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(detail::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case detail::type_specifier_seq_type::CLASS_DECLARATION:
			{
				const syntax_nodes::class_specifier& class_specifier_node =
					detail::get_class_specifier(decl_specifier_seq_node)
				;

				std::shared_ptr<class_> new_class = create_class(class_specifier_node);
				class_entity->add_member(new_class, current_access);
				fill_class(new_class, class_specifier_node);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case detail::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					detail::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
				class_entity->add_member(new_class, current_access);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case detail::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_undecorated_type = create_type(decl_specifier_seq_node, class_entity);
				break;
			}
			case detail::type_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//decorate type
		if(opt_undecorated_type)
			opt_undecorated_type = decorate_type(*opt_undecorated_type, decl_specifier_seq_node);
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
					opt_undecorated_type,
					has_typedef_specifier,
					has_static_specifier,
					has_inline_specifier,
					has_explicit_specifier
				);

				if(auto opt_constructor_entity = get<std::shared_ptr<class_::constructor>>(&declarator_entity))
					class_entity->add_member
					(
						*opt_constructor_entity,
						current_access
					);
				else if(auto opt_destructor_entity = get<std::shared_ptr<class_::destructor>>(&declarator_entity))
					class_entity->set_destructor
					(
						*opt_destructor_entity,
						current_access,
						has_virtual_specifier,
						detail::has_pure_specifier(member_declarator_declarator_node)
					);
				else if(auto opt_operator_function_entity = get<std::shared_ptr<operator_function>>(&declarator_entity))
					class_entity->add_member
					(
						*opt_operator_function_entity,
						current_access,
						detail::is_qualified<str::const_>(declarator_node),
						detail::is_qualified<str::volatile_>(declarator_node),
						has_virtual_specifier,
						detail::has_pure_specifier(member_declarator_declarator_node)
					);
				else if(auto opt_conversion_function_entity = get<std::shared_ptr<class_::conversion_function>>(&declarator_entity))
					class_entity->add_member
					(
						*opt_conversion_function_entity,
						current_access,
						detail::is_qualified<str::const_>(declarator_node),
						detail::is_qualified<str::volatile_>(declarator_node),
						has_virtual_specifier,
						detail::has_pure_specifier(member_declarator_declarator_node)
					);
				else if(auto opt_simple_function_entity = get<std::shared_ptr<simple_function>>(&declarator_entity))
					class_entity->add_member
					(
						*opt_simple_function_entity,
						current_access,
						detail::is_qualified<str::const_>(declarator_node),
						detail::is_qualified<str::volatile_>(declarator_node),
						has_virtual_specifier,
						detail::has_pure_specifier(member_declarator_declarator_node)
					);
				else if(auto opt_variable_entity = get<std::shared_ptr<variable>>(&declarator_entity))
					class_entity->add_member
					(
						*opt_variable_entity,
						current_access,
						has_mutable_specifier
					);
				else if(auto opt_typedef_entity = get<std::shared_ptr<typedef_>>(&declarator_entity))
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



//
//function creation functions
//

std::shared_ptr<semantic_entities::operator_function>
create_operator_function
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::type_shared_ptr_variant type,
	const bool is_inline,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	//
	//get the overloaded operator
	//
	semantic_entities::operator_ op = semantic_entities::operator_::AMPERSAND;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = syntax_nodes::get<syntax_nodes::declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = syntax_nodes::get<syntax_nodes::id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = syntax_nodes::get<syntax_nodes::unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_operator_function_id_node = syntax_nodes::get<syntax_nodes::operator_function_id>(&unqualified_id_node);
	assert(opt_operator_function_id_node);
	auto operator_function_id_node = *opt_operator_function_id_node;
	auto operator_node = get_operator(operator_function_id_node);

	if(auto opt_simple_operator_node = syntax_nodes::get<syntax_nodes::simple_operator>(&operator_node))
	{
		auto simple_operator_node = *opt_simple_operator_node;

		if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::new_>>(&simple_operator_node))
			op = semantic_entities::operator_::NEW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::delete_>>(&simple_operator_node))
			op = semantic_entities::operator_::DELETE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow_asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW_ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_plus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_minus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::round_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::ROUND_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::square_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::SQUARE_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::comma>>(&simple_operator_node))
			op = semantic_entities::operator_::COMMA;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::tilde>>(&simple_operator_node))
			op = semantic_entities::operator_::TILDE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET;
		else
			assert(false);
	}
	else if(auto opt_array_operator_node = syntax_nodes::get<syntax_nodes::array_operator>(&operator_node))
	{
		auto array_operator_node = *opt_array_operator_node;

		if(syntax_nodes::get<syntax_nodes::new_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::NEW_ARRAY;
		else if(syntax_nodes::get<syntax_nodes::delete_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::DELETE_ARRAY;
		else
			assert(false);
	}
	else
	{
		assert(false);
	}

	return std::make_shared<semantic_entities::operator_function>
	(
		op,
		type,
		create_parameters(detail::get_parameter_declaration_list(declarator_node), current_declarative_region),
		is_inline
	);
}

semantic_entities::type_shared_ptr_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = syntax_nodes::get<syntax_nodes::declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = syntax_nodes::get<syntax_nodes::id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = syntax_nodes::get<syntax_nodes::unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_conversion_function_id_node = syntax_nodes::get<syntax_nodes::conversion_function_id>(&unqualified_id_node);
	assert(opt_conversion_function_id_node);
	auto conversion_function_id_node = *opt_conversion_function_id_node;

	auto type_specifier_seq_node = get_type_specifier_seq(conversion_function_id_node);
	type_shared_ptr_variant type = create_type(type_specifier_seq_node, current_declarative_region);

	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(conversion_function_id_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		type = decorate_type(type, ptr_operator_seq_node);
	}

	return type;
}

semantic_entities::simple_function::parameters_t
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	if(opt_parameter_declaration_list_node)
		return create_parameters(*opt_parameter_declaration_list_node, current_declarative_region);
	else
		return semantic_entities::simple_function::parameters_t();
}

semantic_entities::simple_function::parameters_t
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	std::list<simple_function::parameter> parameters;

	for
	(
		auto j = parameter_declaration_list_node.begin();
		j != parameter_declaration_list_node.end();
		++j
	)
	{
		auto parameter_declaration_node = j->main_node();
		auto decl_specifier_seq_node = get_decl_specifier_seq(parameter_declaration_node);

		semantic_entities::type_shared_ptr_variant type =
			decorate_type
			(
				create_type
				(
					decl_specifier_seq_node,
					current_declarative_region
				),
				decl_specifier_seq_node
			)
		;

		if(auto opt_declarator_node = get_declarator(parameter_declaration_node))
		{
			auto declarator_node = *opt_declarator_node;

			parameters.push_back
			(
				std::move
				(
					simple_function::parameter
					(
						decorate_type(type, declarator_node),
						detail::get_identifier(declarator_node).value()
					)
				)
			);
		}
		else if(auto opt_abstract_declarator_node = get_abstract_declarator(parameter_declaration_node))
		{
			auto abstract_declarator_node = *opt_abstract_declarator_node;

			if(boost::optional<const ptr_operator_seq&> opt_ptr_operator_seq_node = get<ptr_operator_seq>(&abstract_declarator_node))
			{
				type = decorate_type(type, *opt_ptr_operator_seq_node);
			}
			else if(boost::optional<const direct_abstract_declarator&> opt_direct_abstract_declarator_node = get<direct_abstract_declarator>(&abstract_declarator_node))
			{
				assert(false); //not managed yet
			}

			parameters.push_back
			(
				std::move
				(
					simple_function::parameter
					(
						type,
						""
					)
				)
			);
		}
		else
		{
			parameters.push_back
			(
				std::move
				(
					simple_function::parameter
					(
						type,
						""
					)
				)
			);
		}
	}

	return parameters;
}



//
//type creation functions
//

semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	return create_type(detail::to_type_specifier_seq(decl_specifier_seq_node), current_declarative_region);
}

semantic_entities::type_shared_ptr_variant
create_type
(
	const syntax_nodes::type_specifier_seq& type_specifier_seq_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_return_type;
	bool is_fundamental_type = false;
	bool bool_type = false;
	bool char_type = false;
	bool double_type = false;
	bool float_type = false;
	bool int_type = false;
	bool long_long_type = false;
	bool long_type = false;
	bool short_type = false;
	bool signed_type = false;
	bool unsigned_type = false;
	bool void_type = false;
	bool wchar_t_type = false;

	for
	(
		auto i = type_specifier_seq_node.begin();
		i < type_specifier_seq_node.end();
		++i
	)
	{
		const syntax_nodes::type_specifier& type_specifier_node = i->main_node();

		if(auto opt_simple_type_specifier_node = get<simple_type_specifier>(&type_specifier_node))
		{
			auto simple_type_specifier_node = *opt_simple_type_specifier_node;

			if(auto opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&simple_type_specifier_node))
			{
				auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;

				opt_return_type =
					to_type_shared_ptr_variant
					(
						detail::name_lookup::find
						<
							named_compound_type_shared_ptr_variant,
							false,
							false
						>
						(
							nested_identifier_or_template_id_node,
							current_declarative_region
						)
					)
				;
			}
			else if(auto opt_fundamental_type_specifier_node = get<fundamental_type_specifier>(&simple_type_specifier_node))
			{
				auto fundamental_type_specifier_node = *opt_fundamental_type_specifier_node;

				is_fundamental_type = true;

				if(get<predefined_text_node<str::char_>>(&fundamental_type_specifier_node))
					char_type = true;
				else if(get<predefined_text_node<str::wchar_t_>>(&fundamental_type_specifier_node))
					wchar_t_type = true;
				else if(get<predefined_text_node<str::bool_>>(&fundamental_type_specifier_node))
					bool_type = true;
				else if(get<predefined_text_node<str::short_>>(&fundamental_type_specifier_node))
					short_type = true;
				else if(get<predefined_text_node<str::int_>>(&fundamental_type_specifier_node))
					int_type = true;
				else if(get<predefined_text_node<str::long_>>(&fundamental_type_specifier_node))
					if(!long_type)
						long_type = true;
					else
						long_long_type = true;
				else if(get<predefined_text_node<str::signed_>>(&fundamental_type_specifier_node))
					signed_type = true;
				else if(get<predefined_text_node<str::unsigned_>>(&fundamental_type_specifier_node))
					unsigned_type = true;
				else if(get<predefined_text_node<str::float_>>(&fundamental_type_specifier_node))
					float_type = true;
				else if(get<predefined_text_node<str::double_>>(&fundamental_type_specifier_node))
					double_type = true;
				else if(get<predefined_text_node<str::void_>>(&fundamental_type_specifier_node))
					void_type = true;
			}
		}
	}

	if(is_fundamental_type)
	{
		assert(!opt_return_type);
		return get_fundamental_type
		(
			bool_type,
			char_type,
			double_type,
			float_type,
			int_type,
			long_long_type,
			long_type,
			short_type,
			signed_type,
			unsigned_type,
			void_type,
			wchar_t_type
		);
	}
	else
	{
		assert(opt_return_type);
		return *opt_return_type;
	}
}

semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const syntax_nodes::decl_specifier_seq& decl_specifier_seq_node
)
{
	for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
	{
		const decl_specifier& decl_specifier_node = i->main_node();

		if(const boost::optional<const type_specifier&> opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			const type_specifier& type_specifier_node = *opt_type_specifier_node;

			if(const boost::optional<const cv_qualifier&> opt_cv_qualifier_node = get<cv_qualifier>(&type_specifier_node))
			{
				const cv_qualifier& cv_qualifier_node = *opt_cv_qualifier_node;

				if(get<predefined_text_node<str::const_>>(&cv_qualifier_node))
					type = std::make_shared<const const_>(type);
				else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
					type = std::make_shared<const volatile_>(type);
			}
		}
	}

	return type;
}

semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const syntax_nodes::declarator& declarator_node
)
{
	//decorate type with hypothetical pointers and/or reference
	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		type = decorate_type(type, ptr_operator_seq_node);
	}

	//decorate type with hypothetical arrays
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			auto last_part_node = i->main_node();
			if(auto opt_array_part_node = syntax_nodes::get<syntax_nodes::direct_declarator_array_part>(&last_part_node))
			{
				if(get_conditional_expression(*opt_array_part_node))
				{
					type = std::make_shared<const semantic_entities::array>(0, type);
				}
				else
				{
					//int i[] == int i*
					type = std::make_shared<const semantic_entities::pointer>(type);
				}
			}
		}
	}

	return type;
}

bool
has_type_decorators(const syntax_nodes::declarator& declarator_node)
{
	//pointers?
	if(get_ptr_operator_seq(declarator_node))
	{
		return true;
	}

	//arrays?
	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for
		(
			auto i = last_part_seq_node.begin();
			i != last_part_seq_node.end();
			++i
		)
		{
			auto last_part_node = i->main_node();
			if(get<syntax_nodes::direct_declarator_array_part>(&last_part_node))
			{
				return true;
			}
		}
	}

	return false;
}

semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node
)
{
	for(auto i = ptr_operator_seq_node.begin(); i != ptr_operator_seq_node.end(); ++i)
	{
		auto ptr_operator_node = i->main_node();
		if(auto opt_ptr_ptr_operator_node = get<ptr_ptr_operator>(&ptr_operator_node))
		{
			auto ptr_ptr_operator_node = *opt_ptr_ptr_operator_node;

			type = std::make_shared<const pointer>(type);

			if(auto opt_cv_qualifier_seq_node = get_cv_qualifier_seq(ptr_ptr_operator_node))
			{
				auto cv_qualifier_seq_node = *opt_cv_qualifier_seq_node;
				for
				(
					auto i = cv_qualifier_seq_node.begin();
					i != cv_qualifier_seq_node.end();
					++i
				)
				{
					auto cv_qualifier_node = i->main_node();

					if(get<predefined_text_node<str::const_>>(&cv_qualifier_node))
					{
						type = std::make_shared<const const_>(type);
					}
					else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
					{
						type = std::make_shared<const volatile_>(type);
					}
				}
			}
		}
		else if(auto ref_ptr_operator_node = get<ref_ptr_operator>(&ptr_operator_node))
		{
			type = std::make_shared<const reference>(type);
		}
	}

	return type;
}

std::shared_ptr<const semantic_entities::fundamental_type>
get_fundamental_type
(
	const bool bool_type,
	const bool char_type,
	const bool double_type,
	const bool float_type,
	const bool int_type,
	const bool long_long_type,
	const bool long_type,
	const bool short_type,
	const bool signed_type,
	const bool unsigned_type,
	const bool void_type,
	const bool wchar_t_type
)
{
	if
	(
		bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::bool_;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::char_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::double_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::float_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		(signed_type || int_type) &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::int_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::long_double;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		//signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//int_type &&
		long_long_type &&
		//long_type &&
		!short_type &&
		//signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::long_long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		!long_type &&
		short_type &&
		//!signed_type &&
		!unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::short_int;
	}
	else if
	(
		!bool_type &&
		char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::unsigned_char;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::unsigned_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::unsigned_long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		long_long_type &&
		//!long_type &&
		!short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::unsigned_long_long_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		//!int_type &&
		!long_long_type &&
		!long_type &&
		short_type &&
		!signed_type &&
		unsigned_type &&
		!void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::unsigned_short_int;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		void_type &&
		!wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::void_;
	}
	else if
	(
		!bool_type &&
		!char_type &&
		!double_type &&
		!float_type &&
		!int_type &&
		!long_long_type &&
		!long_type &&
		!short_type &&
		!signed_type &&
		!unsigned_type &&
		!void_type &&
		wchar_t_type
	)
	{
		return fundamental_type_shared_ptrs::wchar_t_;
	}

	throw std::runtime_error("Incorrect built-in type");
}



//
//other entities' creation functions
//

declarator_entity_shared_ptr_variant
create_entity
(
	const syntax_nodes::declarator& declarator_node,
	const declarative_region_shared_ptr_variant current_declarative_region,
	boost::optional<semantic_entities::type_shared_ptr_variant> opt_type,
	const bool has_typedef_specifier,
	const bool has_static_specifier,
	const bool has_inline_specifier,
	const bool has_explicit_specifier
)
{
	//decorate type with hypothetical pointers, references and arrays
	if(has_type_decorators(declarator_node))
	{
		//if there's no type to decorate, there's an error
		if(!opt_type)
			throw std::runtime_error("create_entity error 1");

		opt_type = decorate_type(*opt_type, declarator_node);
	}

	switch(detail::get_declarator_type(declarator_node))
	{
		case detail::declarator_type::SIMPLE_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				return semantic_entities::simple_function::make_shared
				(
					detail::get_identifier(declarator_node).value(),
					*opt_type,
					create_parameters(detail::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_static_specifier
				);
			else
				return std::make_shared<semantic_entities::class_::constructor>
				(
					create_parameters(detail::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_explicit_specifier
				);
		}
		case detail::declarator_type::DESTRUCTOR_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 2");

			return std::make_shared<semantic_entities::class_::destructor>
			(
				has_inline_specifier
			);
		}
		case detail::declarator_type::OPERATOR_FUNCTION_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 3");

			return create_operator_function
			(
				declarator_node,
				*opt_type,
				has_inline_specifier,
				current_declarative_region
			);
		}
		case detail::declarator_type::CONVERSION_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 3b");

			return std::make_shared<semantic_entities::class_::conversion_function>
			(
				get_conversion_function_type(declarator_node, current_declarative_region),
				has_inline_specifier
			);
		}
		case detail::declarator_type::VARIABLE_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 4");

			if(has_typedef_specifier)
			{
				return std::make_shared<semantic_entities::typedef_>
				(
					detail::get_identifier(declarator_node).value(),
					*opt_type
				);
			}
			else
			{
				return std::make_shared<semantic_entities::variable>
				(
					detail::get_identifier(declarator_node).value(),
					*opt_type,
					has_static_specifier
				);
			}
		}
	}

	throw std::runtime_error("create_entity error 5");
}

std::shared_ptr<namespace_alias>
create_namespace_alias
(
	const syntax_nodes::namespace_alias_definition& namespace_alias_definition_node,
	std::shared_ptr<namespace_> current_namespace
)
{
	const qualified_namespace_specifier& qualified_namespace_specifier_node =
		get_qualified_namespace_specifier(namespace_alias_definition_node)
	;

	//convert the qualified-namespace-specifier node to a nested-identifier-or-template-id node
	syntax_nodes::nested_identifier_or_template_id nested_identifier_or_template_id_node
	(
		has_leading_double_colon(qualified_namespace_specifier_node) ?
			predefined_text_node<str::double_colon>() :
			optional_node<predefined_text_node<str::double_colon>>()
		,
		space(""),
		get_nested_name_specifier(qualified_namespace_specifier_node),
		space(""),
		get_identifier(qualified_namespace_specifier_node)
	);

	//find the namespace designated by the namespace alias
	std::shared_ptr<namespace_> found_namespace =
		get_namespace
		(
			detail::name_lookup::find<namespace_or_namespace_alias_shared_ptr_variant>
			(
				nested_identifier_or_template_id_node,
				current_namespace
			)
		)
	;

	//create the namespace alias semantic entity
	return std::make_shared<namespace_alias>
	(
		get_identifier(namespace_alias_definition_node).value(),
		found_namespace
	);
}

std::shared_ptr<semantic_entities::namespace_>
create_using_directive
(
	const syntax_nodes::using_directive& using_directive_node,
	std::shared_ptr<semantic_entities::namespace_> current_namespace
)
{
	//convert the using-directive node to a nested-identifier-or-template-id node
	syntax_nodes::nested_identifier_or_template_id nested_identifier_or_template_id_node
	(
		has_leading_double_colon(using_directive_node) ?
			predefined_text_node<str::double_colon>() :
			optional_node<predefined_text_node<str::double_colon>>()
		,
		space(""),
		get_nested_name_specifier(using_directive_node),
		space(""),
		get_identifier(using_directive_node)
	);

	//find the namespace designated by the using directive
	return get_namespace
	(
		detail::name_lookup::find<namespace_or_namespace_alias_shared_ptr_variant>
		(
			nested_identifier_or_template_id_node,
			current_namespace
		)
	);
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp

