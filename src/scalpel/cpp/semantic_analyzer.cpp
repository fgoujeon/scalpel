/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "semantic_analyzer.hpp"
#include "detail/semantic_analysis/name_lookup.hpp"
#include "detail/semantic_analysis/basic_functions.hpp"
#include <scalpel/utility/null_deleter.hpp>
#include <iostream>
#include <stdexcept>

namespace scalpel { namespace cpp
{

using namespace syntax_nodes;
using namespace semantic_entities;
using namespace detail::semantic_analysis;

std::shared_ptr<semantic_graph>
semantic_analyzer::operator()(const syntax_tree& tree)
{
	//create semantic graph
	std::shared_ptr<namespace_> global_namespace = std::make_shared<namespace_>();

	//current scope = global namespace
	scope_cursor_.initialize(global_namespace);

	auto opt_declaration_seq_node = get_declaration_seq_node(tree);
	if(opt_declaration_seq_node)
		analyze(*opt_declaration_seq_node, global_namespace);

	return global_namespace;
}

std::shared_ptr<class_>
semantic_analyzer::create_class(const class_specifier& syntax_node)
{
	//get the name of the class
	std::string class_name;
	const optional_node<identifier_or_template_id>& opt_id_or_templ = get_identifier_or_template_id(get_class_head(syntax_node));
	if(opt_id_or_templ)
	{
		const boost::optional<const identifier&> id = get<identifier>(&*opt_id_or_templ);

		if(id)
		{
			class_name = id->value();
		}
	}

	//create the class
	assert(class_name != "");
	return std::make_shared<class_>(class_name);
}

void
semantic_analyzer::fill_class(std::shared_ptr<class_> c, const class_specifier& class_specifier_node)
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
				access = get_access(*opt_access_specifier_node);
			}

			//get base class
			auto nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);
			std::shared_ptr<class_> base = find_class(nested_identifier_or_template_id_node);

			c->add(std::make_shared<class_::base_class>(base, access, is_virtual));
		}
	}

	//default current_access
	auto class_key_node = get_class_key(class_head_node);
	class_::access current_access = class_::access::PUBLIC; //the default current_access is public->..
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
					//analyze(function_definition_node, c);
				}
				else if(auto opt_member_declaration_member_declarator_list_node = get<member_declaration_member_declarator_list>(&*opt_member_declaration_node))
				{
					auto opt_decl_specifier_seq_node = get_decl_specifier_seq(*opt_member_declaration_member_declarator_list_node);
					auto opt_member_declarator_list_node = get_member_declarator_list(*opt_member_declaration_member_declarator_list_node);

					if(opt_member_declarator_list_node)
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
								if(opt_decl_specifier_seq_node)
								{
									auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
									if(is_function_declaration(declarator_node))
									{
										if(is_operator_function_declaration(declarator_node)) //operator function
										{
											c->add
											(
												std::make_shared<class_::member_operator_function>
												(
													create_operator_function(decl_specifier_seq_node, declarator_node),
													current_access,
													is_qualified<str::const_>(declarator_node),
													is_qualified<str::volatile_>(declarator_node),
													has_inline_specifier(decl_specifier_seq_node),
													has_virtual_specifier(decl_specifier_seq_node),
													has_pure_specifier(member_declarator_declarator_node)
												)
											);
										}
										else if(is_conversion_function_declaration(declarator_node)) //conversion function
										{
											c->add
											(
												std::make_shared<class_::conversion_function>
												(
													get_conversion_function_type(declarator_node),
													current_access,
													is_qualified<str::const_>(declarator_node),
													is_qualified<str::volatile_>(declarator_node),
													has_inline_specifier(decl_specifier_seq_node),
													has_virtual_specifier(decl_specifier_seq_node),
													has_pure_specifier(member_declarator_declarator_node)
												)
											);
										}
										else if(c->name() == get_function_name(declarator_node)) //constructor or destructor
										{
											if(!is_destructor_declaration(declarator_node)) //constructor
											{
												c->add
												(
													std::make_shared<class_::constructor>
													(
														std::move(create_parameters(declarator_node)),
														current_access,
														has_inline_specifier(decl_specifier_seq_node),
														has_explicit_specifier(decl_specifier_seq_node)
													)
												);
											}
											else //destructor
											{
												c->set_destructor
												(
													std::make_shared<class_::destructor>
													(
														current_access,
														has_inline_specifier(decl_specifier_seq_node),
														has_virtual_specifier(decl_specifier_seq_node),
														has_pure_specifier(member_declarator_declarator_node)
													)
												);
											}
										}
										else //simple function
										{
											c->add
											(
												std::make_shared<class_::member_function>
												(
													create_function(decl_specifier_seq_node, declarator_node),
													current_access,
													is_qualified<str::const_>(declarator_node),
													is_qualified<str::volatile_>(declarator_node),
													has_inline_specifier(decl_specifier_seq_node),
													has_virtual_specifier(decl_specifier_seq_node),
													has_pure_specifier(member_declarator_declarator_node)
												)
											);
										}
									}
									else //variable
									{
										c->add
										(
											std::make_shared<class_::member_variable>
											(
												create_variable(decl_specifier_seq_node, declarator_node),
												current_access
											)
										);
									}
								}
								else
								{
									if(is_conversion_function_declaration(declarator_node)) //conversion function
									{
										c->add
										(
											std::make_shared<class_::conversion_function>
											(
												get_conversion_function_type(declarator_node),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												false,
												false,
												false
											)
										);
									}
									else if(c->name() == get_function_name(declarator_node)) //constructor or destructor
									{
										if(!is_destructor_declaration(declarator_node)) //constructor
										{
											c->add
											(
												std::make_shared<class_::constructor>
												(
													std::move(create_parameters(declarator_node)),
													current_access,
													false,
													false
												)
											);
										}
										else //destructor
										{
											c->set_destructor
											(
												std::make_shared<class_::destructor>
												(
													current_access,
													false,
													false,
													false
												)
											);
										}
									}
								}
							}
						}
					}
					else if(opt_decl_specifier_seq_node)
					{
						auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
						for(auto j = decl_specifier_seq_node.begin(); j != decl_specifier_seq_node.end(); ++j)
						{
							auto decl_specifier_node = j->main_node();
							if(auto opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
							{
								auto type_specifier_node = *opt_type_specifier_node;
								if(auto opt_class_specifier_node = get<class_specifier>(&type_specifier_node))
								{
									auto class_specifier_node = *opt_class_specifier_node;

									std::shared_ptr<class_> new_class = create_class(class_specifier_node);
									std::shared_ptr<class_::nested_class> new_nested_class =
										std::make_shared<class_::nested_class>
										(
											new_class,
											current_access
										)
									;
									c->add(new_nested_class);
									scope_cursor_.enter_scope(new_nested_class);
									fill_class(new_class, class_specifier_node);
									scope_cursor_.leave_scope();
								}
							}
						}
					}
					else
					{
						assert(false);
					}
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
				current_access = get_access(access_specifier_node);
			}
			else
			{
				assert(false);
			}
		}
	}
}

std::shared_ptr<semantic_entities::function>
semantic_analyzer::create_function(const decl_specifier_seq& decl_specifier_seq_node, const declarator& declarator_node)
{
	return std::make_shared<function>
	(
		get_function_name(declarator_node),
		create_type(decl_specifier_seq_node, declarator_node),
		create_parameters(declarator_node),
		has_static_specifier(decl_specifier_seq_node)
	);
}

std::shared_ptr<semantic_entities::operator_function>
semantic_analyzer::create_operator_function(const decl_specifier_seq& decl_specifier_seq_node, const declarator& declarator_node)
{
	//get the overloaded operator
	semantic_entities::operator_ op = semantic_entities::operator_::AMPERSAND;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = get<id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = get<unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_operator_function_id_node = get<operator_function_id>(&unqualified_id_node);
	assert(opt_operator_function_id_node);
	auto operator_function_id_node = *opt_operator_function_id_node;
	auto operator_node = get_operator(operator_function_id_node);

	if(auto opt_simple_operator_node = get<simple_operator>(&operator_node))
	{
		auto simple_operator_node = *opt_simple_operator_node;

		if(get<predefined_text_node<str::new_>>(&simple_operator_node))
			op = semantic_entities::operator_::NEW;
		else if(get<predefined_text_node<str::delete_>>(&simple_operator_node))
			op = semantic_entities::operator_::DELETE;
		else if(get<predefined_text_node<str::double_right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL;
		else if(get<predefined_text_node<str::double_left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL;
		else if(get<predefined_text_node<str::arrow_asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW_ASTERISK;
		else if(get<predefined_text_node<str::plus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS_EQUAL;
		else if(get<predefined_text_node<str::minus_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS_EQUAL;
		else if(get<predefined_text_node<str::asterisk_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK_EQUAL;
		else if(get<predefined_text_node<str::slash_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH_EQUAL;
		else if(get<predefined_text_node<str::percent_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT_EQUAL;
		else if(get<predefined_text_node<str::circumflex_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX_EQUAL;
		else if(get<predefined_text_node<str::ampersand_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND_EQUAL;
		else if(get<predefined_text_node<str::pipe_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE_EQUAL;
		else if(get<predefined_text_node<str::double_left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_LEFT_ANGLE_BRACKET;
		else if(get<predefined_text_node<str::double_right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_RIGHT_ANGLE_BRACKET;
		else if(get<predefined_text_node<str::double_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_EQUAL;
		else if(get<predefined_text_node<str::exclamation_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION_EQUAL;
		else if(get<predefined_text_node<str::left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET_EQUAL;
		else if(get<predefined_text_node<str::right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET_EQUAL;
		else if(get<predefined_text_node<str::double_ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_AMPERSAND;
		else if(get<predefined_text_node<str::double_pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PIPE;
		else if(get<predefined_text_node<str::double_plus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_PLUS;
		else if(get<predefined_text_node<str::double_minus>>(&simple_operator_node))
			op = semantic_entities::operator_::DOUBLE_MINUS;
		else if(get<predefined_text_node<str::arrow>>(&simple_operator_node))
			op = semantic_entities::operator_::ARROW;
		else if(get<predefined_text_node<str::round_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::ROUND_BRACKETS;
		else if(get<predefined_text_node<str::square_brackets>>(&simple_operator_node))
			op = semantic_entities::operator_::SQUARE_BRACKETS;
		else if(get<predefined_text_node<str::comma>>(&simple_operator_node))
			op = semantic_entities::operator_::COMMA;
		else if(get<predefined_text_node<str::plus>>(&simple_operator_node))
			op = semantic_entities::operator_::PLUS;
		else if(get<predefined_text_node<str::minus>>(&simple_operator_node))
			op = semantic_entities::operator_::MINUS;
		else if(get<predefined_text_node<str::asterisk>>(&simple_operator_node))
			op = semantic_entities::operator_::ASTERISK;
		else if(get<predefined_text_node<str::slash>>(&simple_operator_node))
			op = semantic_entities::operator_::SLASH;
		else if(get<predefined_text_node<str::percent>>(&simple_operator_node))
			op = semantic_entities::operator_::PERCENT;
		else if(get<predefined_text_node<str::circumflex>>(&simple_operator_node))
			op = semantic_entities::operator_::CIRCUMFLEX;
		else if(get<predefined_text_node<str::ampersand>>(&simple_operator_node))
			op = semantic_entities::operator_::AMPERSAND;
		else if(get<predefined_text_node<str::pipe>>(&simple_operator_node))
			op = semantic_entities::operator_::PIPE;
		else if(get<predefined_text_node<str::tilde>>(&simple_operator_node))
			op = semantic_entities::operator_::TILDE;
		else if(get<predefined_text_node<str::exclamation>>(&simple_operator_node))
			op = semantic_entities::operator_::EXCLAMATION;
		else if(get<predefined_text_node<str::equal>>(&simple_operator_node))
			op = semantic_entities::operator_::EQUAL;
		else if(get<predefined_text_node<str::left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::LEFT_ANGLE_BRACKET;
		else if(get<predefined_text_node<str::right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::operator_::RIGHT_ANGLE_BRACKET;
		else
			assert(false);
	}
	else if(auto opt_array_operator_node = get<array_operator>(&operator_node))
	{
		auto array_operator_node = *opt_array_operator_node;

		if(get<new_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::NEW_ARRAY;
		else if(get<delete_array_operator>(&array_operator_node))
			op = semantic_entities::operator_::DELETE_ARRAY;
		else
			assert(false);
	}
	else
	{
		assert(false);
	}

	//get the function's return type
	std::shared_ptr<const type> return_type = create_type(decl_specifier_seq_node, declarator_node);

	//get the function's parameter list
	std::list<function::parameter> parameters = create_parameters(declarator_node);

	return std::make_shared<operator_function>
	(
		op,
		return_type,
		std::move(parameters),
		has_static_specifier(decl_specifier_seq_node)
	);
}

function::parameters_t
semantic_analyzer::create_parameters(const declarator& declarator_node)
{
	std::list<function::parameter> parameters;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	if(auto opt_last_part_seq_node = get_last_part_seq(direct_declarator_node))
	{
		auto last_part_seq_node = *opt_last_part_seq_node;
		for(auto i = last_part_seq_node.begin(); i != last_part_seq_node.end(); ++i)
		{
			auto last_part_node = i->main_node();
			if(auto opt_function_part_node = get<direct_declarator_function_part>(&last_part_node))
			{
				if(auto opt_parameter_declaration_clause_node = get_parameter_declaration_clause(*opt_function_part_node))
				{
					if(auto opt_parameter_declaration_list_node = get_parameter_declaration_list(*opt_parameter_declaration_clause_node))
					{
						auto parameter_declaration_list_node = *opt_parameter_declaration_list_node;
						for
						(
							auto j = parameter_declaration_list_node.begin();
							j != parameter_declaration_list_node.end();
							++j
						)
						{
							auto parameter_declaration_node = j->main_node();
							auto decl_specifier_seq_node = get_decl_specifier_seq(parameter_declaration_node);

							if(auto opt_declarator_node = get_declarator(parameter_declaration_node))
							{
								auto declarator_node = *opt_declarator_node;

								//get parameter name
								std::string name;
								auto direct_declarator_node = get_direct_declarator(declarator_node);
								auto first_part_node = get_first_part(direct_declarator_node);
								if(auto opt_declarator_id_node = get<declarator_id>(&first_part_node))
								{
									auto declarator_id_node = *opt_declarator_id_node;
									if(auto opt_id_expression_node = get<id_expression>(&declarator_id_node))
									{
										auto id_expression_node = *opt_id_expression_node;
										if(auto opt_unqualified_id_node = get<unqualified_id>(&id_expression_node))
										{
											auto unqualified_id_node = *opt_unqualified_id_node;
											if(auto opt_identifier_node = get<identifier>(&unqualified_id_node))
											{
												auto identifier_node = *opt_identifier_node;
												name = identifier_node.value();
											}
										}
									}
								}

								parameters.push_back
								(
									std::move
									(
										function::parameter
										(
											create_type(decl_specifier_seq_node, declarator_node),
											name
										)
									)
								);
							}
							else if(auto opt_abstract_declarator_node = get_abstract_declarator(parameter_declaration_node))
							{
								auto abstract_declarator_node = *opt_abstract_declarator_node;

								parameters.push_back
								(
									std::move
									(
										function::parameter
										(
											create_type(decl_specifier_seq_node, abstract_declarator_node),
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
										function::parameter
										(
											create_type(decl_specifier_seq_node),
											""
										)
									)
								);
							}
						}
					}
				}
			}
		}
	}

	return parameters;
}

std::shared_ptr<const type>
semantic_analyzer::create_type(const decl_specifier_seq& decl_specifier_seq_node, const declarator& declarator_node)
{
	std::shared_ptr<const type> return_type = create_type(decl_specifier_seq_node);

	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

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
			if(auto array_part = get<direct_declarator_array_part>(&last_part_node))
			{
				return_type = std::make_shared<array>(0, return_type);
			}
		}
	}

	if(!return_type)
	{
		throw std::runtime_error("Semantic analysis error: type not found");
	}
	return return_type;
}

std::shared_ptr<const type>
semantic_analyzer::create_type
(
	const decl_specifier_seq& decl_specifier_seq_node,
	const abstract_declarator& abstract_declarator_node
)
{
	std::shared_ptr<const type> return_type = create_type(decl_specifier_seq_node);

	if(auto opt_ptr_operator_seq_node = get<ptr_operator_seq>(&abstract_declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

	if(!return_type)
	{
		throw std::runtime_error("Semantic analysis error: type not found");
	}
	return return_type;
}

std::shared_ptr<const type>
semantic_analyzer::create_type
(
	const decl_specifier_seq& decl_specifier_seq_node
)
{
	std::shared_ptr<const type> return_type;
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
	bool const_qualified = false;
	bool volatile_qualified = false;

	for
	(
		auto i = decl_specifier_seq_node.begin();
		i < decl_specifier_seq_node.end();
		++i
	)
	{
		const decl_specifier& decl_specifier_node = i->main_node();

		//auto opt_function_specifier_node = get<function_specifier>(&decl_specifier_node);
		//auto opt_storage_class_specifier_node = get<storage_class_specifier>(&decl_specifier_node);
		//predefined_text_node<str::friend_>
		//predefined_text_node<str::typedef_>

		if(auto opt_type_specifier_node = get<type_specifier>(&decl_specifier_node))
		{
			auto type_specifier_node = *opt_type_specifier_node;
			get_type_info
			(
				type_specifier_node,
				return_type,
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
				wchar_t_type,
				const_qualified,
				volatile_qualified
			);
		}
	}

	if(!return_type)
	{
		return_type = get_built_in_type
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

	assert(return_type);

	return_type = decorate_type(return_type, const_qualified, volatile_qualified);

	return return_type;
}

std::shared_ptr<const semantic_entities::type>
semantic_analyzer::get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node
)
{
	std::shared_ptr<const type> return_type;
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
	bool const_qualified = false;
	bool volatile_qualified = false;

	auto direct_declarator_node = get_direct_declarator(declarator_node);
	auto direct_declarator_node_first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&direct_declarator_node_first_part_node);
	assert(opt_declarator_id_node);
	auto declarator_id_node = *opt_declarator_id_node;
	auto opt_id_expression_node = get<id_expression>(&declarator_id_node);
	assert(opt_id_expression_node);
	auto id_expression_node = *opt_id_expression_node;
	auto opt_unqualified_id_node = get<unqualified_id>(&id_expression_node);
	assert(opt_unqualified_id_node);
	auto unqualified_id_node = *opt_unqualified_id_node;
	auto opt_conversion_function_id_node = get<conversion_function_id>(&unqualified_id_node);
	assert(opt_conversion_function_id_node);
	auto conversion_function_id_node = *opt_conversion_function_id_node;

	auto type_specifier_seq_node = get_type_specifier_seq(conversion_function_id_node);
	for(auto i = type_specifier_seq_node.begin(); i != type_specifier_seq_node.end(); ++i)
	{
		auto type_specifier_node = i->main_node();
		get_type_info
		(
			type_specifier_node,
			return_type,
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
			wchar_t_type,
			const_qualified,
			volatile_qualified
		);
	}

	if(!return_type)
	{
		return_type = get_built_in_type
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

	assert(return_type);

	return_type = decorate_type(return_type, const_qualified, volatile_qualified);

	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(conversion_function_id_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		return_type = decorate_type(return_type, ptr_operator_seq_node);
	}

	if(!return_type)
	{
		throw std::runtime_error("Semantic analysis error: type not found");
	}
	return return_type;
}

std::shared_ptr<const semantic_entities::type>
semantic_analyzer::decorate_type
(
	std::shared_ptr<const semantic_entities::type> return_type,
	const bool const_qualified,
	const bool volatile_qualified
)
{
	if(const_qualified)
		return_type = std::make_shared<const_>(return_type);
	if(volatile_qualified)
		return_type = std::make_shared<volatile_>(return_type);

	return return_type;
}

std::shared_ptr<const semantic_entities::type>
semantic_analyzer::decorate_type
(
	std::shared_ptr<const semantic_entities::type> return_type,
	const syntax_nodes::ptr_operator_seq& ptr_operator_seq_node
)
{
	for(auto i = ptr_operator_seq_node.begin(); i != ptr_operator_seq_node.end(); ++i)
	{
		auto ptr_operator_node = i->main_node();
		if(auto opt_ptr_ptr_operator_node = get<ptr_ptr_operator>(&ptr_operator_node))
		{
			auto ptr_ptr_operator_node = *opt_ptr_ptr_operator_node;

			return_type = std::make_shared<pointer>(return_type);

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
						return_type = std::make_shared<const_>(return_type);
					}
					else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
					{
						return_type = std::make_shared<volatile_>(return_type);
					}
				}
			}
		}
		else if(auto ref_ptr_operator_node = get<ref_ptr_operator>(&ptr_operator_node))
		{
			return_type = std::make_shared<reference>(return_type);
		}
	}

	return return_type;
}

void
semantic_analyzer::get_type_info
(
	const syntax_nodes::type_specifier& type_specifier_node,
	std::shared_ptr<const semantic_entities::type>& t,
	bool& bool_type,
	bool& char_type,
	bool& double_type,
	bool& float_type,
	bool& int_type,
	bool& long_long_type,
	bool& long_type,
	bool& short_type,
	bool& signed_type,
	bool& unsigned_type,
	bool& void_type,
	bool& wchar_t_type,
	bool& const_qualified,
	bool& volatile_qualified
)
{
	//simple_type_specifier
	//class_specifier
	//enum_specifier
	//elaborated_type_specifier
	//cv_qualifier
	//typeof_expression

	if(auto opt_simple_type_specifier_node = get<simple_type_specifier>(&type_specifier_node))
	{
		auto simple_type_specifier_node = *opt_simple_type_specifier_node;
		//simple_template_type_specifier,

		if(auto opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&simple_type_specifier_node))
		{
			auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
			std::shared_ptr<named_entity> found_name = name_lookup::find_name(scope_cursor_.scope_stack(), nested_identifier_or_template_id_node);
			if(auto found_type = std::dynamic_pointer_cast<const type>(found_name))
			{
				t = found_type;
			}
		}
		else if(auto opt_built_in_type_specifier_node = get<built_in_type_specifier>(&simple_type_specifier_node))
		{
			auto built_in_type_specifier_node = *opt_built_in_type_specifier_node;

			if(get<predefined_text_node<str::char_>>(&built_in_type_specifier_node))
			{
				char_type = true;
			}
			else if(get<predefined_text_node<str::wchar_t_>>(&built_in_type_specifier_node))
			{
				wchar_t_type = true;
			}
			else if(get<predefined_text_node<str::bool_>>(&built_in_type_specifier_node))
			{
				bool_type = true;
			}
			else if(get<predefined_text_node<str::short_>>(&built_in_type_specifier_node))
			{
				short_type = true;
			}
			else if(get<predefined_text_node<str::int_>>(&built_in_type_specifier_node))
			{
				int_type = true;
			}
			else if(get<predefined_text_node<str::long_>>(&built_in_type_specifier_node))
			{
				if(!long_type)
					long_type = true;
				else
					long_long_type = true;
			}
			else if(get<predefined_text_node<str::signed_>>(&built_in_type_specifier_node))
			{
				signed_type = true;
			}
			else if(get<predefined_text_node<str::unsigned_>>(&built_in_type_specifier_node))
			{
				unsigned_type = true;
			}
			else if(get<predefined_text_node<str::float_>>(&built_in_type_specifier_node))
			{
				float_type = true;
			}
			else if(get<predefined_text_node<str::double_>>(&built_in_type_specifier_node))
			{
				double_type = true;
			}
			else if(get<predefined_text_node<str::void_>>(&built_in_type_specifier_node))
			{
				void_type = true;
			}
		}
	}
	else if(auto opt_cv_qualifier_node = get<cv_qualifier>(&type_specifier_node))
	{
		auto cv_qualifier_node = *opt_cv_qualifier_node;
		//predefined_text_node<str::const_>
		//predefined_text_node<str::volatile_>
		//predefined_text_node<str::restrict_>
		//predefined_text_node<str::__restrict___>
		//predefined_text_node<str::__restrict_>

		if(get<predefined_text_node<str::const_>>(&cv_qualifier_node))
		{
			const_qualified = true;
		}
		else if(get<predefined_text_node<str::volatile_>>(&cv_qualifier_node))
		{
			volatile_qualified = true;
		}
	}
}

std::shared_ptr<const semantic_entities::built_in_type>
semantic_analyzer::get_built_in_type
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
		return std::shared_ptr<const built_in_type>(&built_in_type::bool_, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::char_, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::double_, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::float_, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::int_, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::long_double, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::long_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::long_long_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::short_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::unsigned_char, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::unsigned_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::unsigned_long_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::unsigned_long_long_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::unsigned_short_int, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::void_, scalpel::utility::null_deleter());
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
		return std::shared_ptr<const built_in_type>(&built_in_type::wchar_t_, scalpel::utility::null_deleter());
	}

	throw std::runtime_error("Incorrect built-in type");
}

std::shared_ptr<semantic_entities::class_>
semantic_analyzer::find_class
(
	const syntax_nodes::nested_identifier_or_template_id& nested_identifier_or_template_id_node
)
{
	std::shared_ptr<named_entity> found_name = name_lookup::find_name(scope_cursor_.scope_stack(), nested_identifier_or_template_id_node);

	if(std::shared_ptr<class_> found_class = std::dynamic_pointer_cast<class_>(found_name))
	{
		return found_class;
	}
	else if(std::shared_ptr<class_::nested_class> found_class = std::dynamic_pointer_cast<class_::nested_class>(found_name))
	{
		return found_class->entity();
	}

	throw std::runtime_error("Type not found");
}

std::vector<std::shared_ptr<variable>>
semantic_analyzer::create_variables
(
	const decl_specifier_seq& decl_specifier_seq_node,
	const init_declarator_list& init_declarator_list_node
)
{
	std::vector<std::shared_ptr<variable>> variables;

	//for each variable
	for
	(
		auto i = init_declarator_list_node.begin();
		i != init_declarator_list_node.end();
		++i
	)
	{
		auto init_declarator_node = i->main_node();
		auto declarator_node = get_declarator(init_declarator_node);
		variables.push_back
		(
			create_variable
			(
				decl_specifier_seq_node,
				declarator_node
			)
		);
	}

	return variables;
}

std::shared_ptr<variable>
semantic_analyzer::create_variable
(
	const decl_specifier_seq& decl_specifier_seq_node,
	const declarator& declarator_node
)
{
	auto direct_declarator_node = get_direct_declarator(declarator_node);

	auto first_part_node = get_first_part(direct_declarator_node);
	auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
	if(opt_declarator_id_node)
	{
		auto declarator_id_node = *opt_declarator_id_node;
		if(auto id_expression_node = get<id_expression>(&declarator_id_node))
		{
			if(auto unqualified_id_node = get<unqualified_id>(&*id_expression_node))
			{
				if(auto identifier_node = get<identifier>(&*unqualified_id_node))
				{
					return std::make_shared<variable>
					(
						create_type(decl_specifier_seq_node, declarator_node),
						std::move(identifier_node->value()),
						has_static_specifier(decl_specifier_seq_node)
					);
				}
			}
		}
	}

	throw std::runtime_error("Cannot create variable");
}

}} //namespace scalpel::cpp

