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

#include <iostream>
#include <stdexcept>
#include <scalpel/utility/null_deleter.hpp>
#include "detail/semantic_analysis/name_lookup.hpp"
#include "detail/semantic_analysis/basic_functions.hpp"

namespace scalpel { namespace cpp
{

using namespace syntax_nodes;
using namespace semantic_entities;
using namespace detail::semantic_analysis;

semantic_analyzer::alternative_visitor::alternative_visitor(semantic_analyzer& analyzer):
	analyzer_(analyzer)
{
}

semantic_analyzer::semantic_analyzer():
	alternative_visitor_(*this)
{
}

std::shared_ptr<semantic_graph>
semantic_analyzer::operator()(const syntax_tree& tree)
{
	//create semantic graph
	std::shared_ptr<namespace_> global_namespace = std::make_shared<namespace_>();

	//current scope = global namespace
	scope_cursor_.initialize(global_namespace);

	auto opt_declaration_seq_node = get_declaration_seq_node(tree);

	if(opt_declaration_seq_node)
	{
		auto declaration_seq_node = *opt_declaration_seq_node;
		for
		(
			auto i = declaration_seq_node.begin();
			i != declaration_seq_node.end();
			++i
		)
		{
			analyze_alternative(i->main_node());
		}
	}

	return global_namespace;
}

void
semantic_analyzer::analyze(const asm_definition&)
{
}

void
semantic_analyzer::analyze(const break_statement&)
{
}

void
semantic_analyzer::analyze(const case_statement&)
{
}

void
semantic_analyzer::analyze(const class_head&)
{
}

void
semantic_analyzer::analyze(const class_specifier& class_specifier_node)
{
	std::shared_ptr<class_> new_class = create_class(class_specifier_node);
	scope_cursor_.add_to_current_scope(new_class);
	scope_cursor_.enter_scope(new_class);
	fill_class(*new_class, class_specifier_node);
	scope_cursor_.leave_scope();
}

void
semantic_analyzer::analyze(const classic_labeled_statement&)
{
}

void
semantic_analyzer::analyze(const compound_statement& syntax_node, const bool create_statement_block)
{
	if(create_statement_block)
	{
		std::shared_ptr<statement_block> s = std::make_shared<statement_block>();
		scope_cursor_.add_to_current_scope(s);
		scope_cursor_.enter_last_added_scope();
	}

	auto opt_statement_seq_node = get_statement_seq(syntax_node);
	if(opt_statement_seq_node)
	{
		analyze(*opt_statement_seq_node);
	}

	if(create_statement_block)
	{
		scope_cursor_.leave_scope();
	}
}

void
semantic_analyzer::analyze(const continue_statement&)
{
}

void
semantic_analyzer::analyze(const conversion_function_id&)
{
}

void
semantic_analyzer::analyze(const ctor_initializer&)
{
}

void
semantic_analyzer::analyze(const cv_qualifier&)
{
}

void
semantic_analyzer::analyze(const declarator&)
{
}

void
semantic_analyzer::analyze(const default_statement&)
{
}

void
semantic_analyzer::analyze(const destructor_name&)
{
}

void
semantic_analyzer::analyze(const direct_declarator&)
{
}

void
semantic_analyzer::analyze(const direct_declarator_array_part&)
{
}

void
semantic_analyzer::analyze(const direct_declarator_function_part&)
{
}

void
semantic_analyzer::analyze(const do_while_statement& syntax_node)
{
	analyze(get_statement(syntax_node));
}

void
semantic_analyzer::analyze(const elaborated_type_specifier&)
{
}

void
semantic_analyzer::analyze(const explicit_instantiation&)
{
}

void
semantic_analyzer::analyze(const explicit_specialization&)
{
}

void
semantic_analyzer::analyze(const expression_statement&)
{
}

void
semantic_analyzer::analyze(const for_statement& syntax_node)
{
	analyze(get_statement(syntax_node));
}

void
semantic_analyzer::analyze(const function_definition& function_definition_node)
{
	auto direct_declarator_node = get_direct_declarator(get_declarator(function_definition_node));

	//
	//get the enclosing scope of the function
	//
	std::shared_ptr<scope> enclosing_scope;

	const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);
	boost::optional<const declarator_id&> direct_node_id = get<declarator_id>(&first_part_node);
	if(direct_node_id)
	{
		boost::optional<const id_expression&> id_expression_node = get<id_expression>(direct_node_id);
		if(id_expression_node)
		{
			boost::optional<const unqualified_id&> unqualified_id_node = get<unqualified_id>(id_expression_node);
			boost::optional<const qualified_id&> a_qualified_id = get<qualified_id>(id_expression_node);

			if(unqualified_id_node)
			{
				enclosing_scope = scope_cursor_.current_scope();
			}
			else if(a_qualified_id)
			{
			//	const qualified_identifier* const a_qualified_identifier =
			//		boost::get<qualified_identifier>(a_qualified_id)
			//	;
				boost::optional<const qualified_nested_id&> a_qualified_nested_id = get<qualified_nested_id>(a_qualified_id);
			//	const qualified_operator_function_id* const a_qualified_operator_function_id =
			//	   	boost::get<qualified_operator_function_id>(a_qualified_id)
			//	;
			//	const qualified_template_id* const a_qualified_template_id =
			//	   	boost::get<qualified_template_id>(a_qualified_id)
			//	;

				if(a_qualified_nested_id)
				{
					bool leading_double_colon = has_double_colon(*a_qualified_nested_id);
					const nested_name_specifier& a_nested_name_specifier = get_nested_name_specifier(*a_qualified_nested_id);

					if(leading_double_colon)
					{
						enclosing_scope = name_lookup::find_scope(scope_cursor_.global_scope_stack(), a_nested_name_specifier);
					}
					else
					{
						enclosing_scope = name_lookup::find_scope(scope_cursor_.scope_stack(), a_nested_name_specifier);
					}
				}
			}
			else
			{
				assert(false);
			}
		}
	}

	if(auto opt_decl_specifier_seq_node = get_decl_specifier_seq(function_definition_node))
	{
		//create a function object
		auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		auto declarator_node = get_declarator(function_definition_node);
		std::shared_ptr<function> new_function = create_function(decl_specifier_seq_node, declarator_node);

		//find the corresponding function semantic node (must exist if the function has already been declared)
		std::shared_ptr<scope> function_scope;
		if(enclosing_scope)
		{
			auto scopes = enclosing_scope->scopes();
			for(auto i = scopes.begin(); i != scopes.end(); ++i)
			{
				std::shared_ptr<scope> scope = *i;

				///\todo check the function's signature
				if(scope->name() == new_function->name())
				{
					function_scope = scope;
					break;
				}
			}
		}

		//if the function hasn't been declared, this definition serves as a declaration
		if(!function_scope)
		{
			scope_cursor_.add_to_current_scope(new_function);
			function_scope = scope_cursor_.current_scope()->scopes().back();
		}

		//enter and leave the function body
		if(function_scope)
		{
			/*
			scope_cursor_.enter_scope(*function_scope);

			if(auto opt_simple_function_definition = get<simple_function_definition>(&function_definition_node))
			{
				auto compound_statement_node = get_compound_statement(*opt_simple_function_definition);
				analyze(compound_statement_node, false);
			}

			scope_cursor_.leave_scope();
			*/
		}
	}
}

void
semantic_analyzer::analyze(const goto_statement&)
{
}

void
semantic_analyzer::analyze(const handler& syntax_node)
{
	analyze(get_compound_statement(syntax_node));
}

void
semantic_analyzer::analyze(const identifier&)
{
}

void
semantic_analyzer::analyze(const if_statement& syntax_node)
{
	analyze(get_statement(syntax_node));

	auto opt_else_statement_node = get_else_statement(syntax_node);
	if(opt_else_statement_node)
		analyze(*opt_else_statement_node);
}

void
semantic_analyzer::analyze(const init_declarator&)
{
}

void
semantic_analyzer::analyze(const linkage_specification&)
{
}

void
semantic_analyzer::analyze(const mem_initializer&)
{
}

void
semantic_analyzer::analyze(const member_declaration_function_definition&)
{
}

void
semantic_analyzer::analyze(const member_declaration_member_declarator_list&)
{
}

void
semantic_analyzer::analyze(const member_declaration_unqualified_id&)
{
}

void
semantic_analyzer::analyze(const member_declarator_bit_field_member&)
{
}

void
semantic_analyzer::analyze(const member_declarator_declarator&)
{
}

void
semantic_analyzer::analyze(const member_specification&)
{
}

void
semantic_analyzer::analyze(const member_specification_access_specifier&)
{
}

void
semantic_analyzer::analyze(const namespace_alias_definition&)
{
}

void
semantic_analyzer::analyze(const namespace_definition& syntax_node)
{
	//get the namespace name
	std::string namespace_name;
	const optional_node<identifier>& identifier_node = get_identifier(syntax_node);
	if(identifier_node)
	{
		namespace_name = identifier_node->value();
	}

	//add the namespace to the current scope
	scope_cursor_.add_to_current_scope(std::make_shared<namespace_>(namespace_name));

	//add the declarations of the namespace definition in the namespace semantic node
	scope_cursor_.enter_last_added_scope(); //we have to enter even if there's no declaration
	const optional_node<declaration_seq>& a_declaration_seq = get_declaration_seq(syntax_node);
	if(a_declaration_seq)
	{
		analyze_list(*a_declaration_seq);
	}
	scope_cursor_.leave_scope();
}

void
semantic_analyzer::analyze(const nested_identifier_or_template_id&)
{
}

void
semantic_analyzer::analyze(const nested_name_specifier&)
{
}

void
semantic_analyzer::analyze(const nested_name_specifier_last_part&)
{
}

void
semantic_analyzer::analyze(const operator_function_id&)
{
}

void
semantic_analyzer::analyze(const parameter_declaration&)
{
}

void
semantic_analyzer::analyze(const parameter_declaration_clause&)
{
}

void
semantic_analyzer::analyze(const ptr_operator&)
{
}

void
semantic_analyzer::analyze(const qualified_identifier&)
{
}

void
semantic_analyzer::analyze(const qualified_nested_id&)
{
}

void
semantic_analyzer::analyze(const qualified_operator_function_id&)
{
}

void
semantic_analyzer::analyze(const qualified_template_id&)
{
}

void
semantic_analyzer::analyze(const return_statement&)
{
}

void
semantic_analyzer::analyze(const simple_declaration& simple_declaration_node)
{
	std::vector<std::string> names;
	std::string class_name;
	bool is_a_class_declaration = false;
	bool is_a_class_forward_declaration = false;
	bool is_a_function_declaration = false;

	const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node = get_decl_specifier_seq(simple_declaration_node);
	const optional_node<init_declarator_list>& opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);

	if(opt_decl_specifier_seq_node)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		for(auto i = decl_specifier_seq_node.begin(); i != decl_specifier_seq_node.end(); ++i)
		{
			const decl_specifier& a_decl_specifier = i->main_node();

			if(auto a_type_specifier_ptr = get<type_specifier>(&a_decl_specifier))
			{
				if(auto opt_class_specifier_node = get<class_specifier>(a_type_specifier_ptr))
				{
					is_a_class_declaration = true;
					analyze(*opt_class_specifier_node);
				}
				else if(auto an_elaborated_type_specifier_ptr = get<elaborated_type_specifier>(a_type_specifier_ptr))
				{
					//const class_template_elaborated_specifier* = get<>;
					//const enum_elaborated_specifier* ;
					//const typename_template_elaborated_specifier* ;
					//const typename_elaborated_specifier* ;

					if
					(
						auto opt_class_elaborated_specifier_node = get<class_elaborated_specifier>
						(
							an_elaborated_type_specifier_ptr
						)
					)
					{
						is_a_class_forward_declaration = true;
						const identifier_or_template_id& identifier_or_template_id_node = get_identifier_or_template_id(*opt_class_elaborated_specifier_node);
						if(auto identifier_node = get<identifier>(&identifier_or_template_id_node))
						{
							class_name = identifier_node->value();
						}
					}
				}
			}
		}
	}

	if(opt_init_declarator_list_node)
	{
		const init_declarator_list& an_init_declarator_list = *opt_init_declarator_list_node;
		for(auto i = an_init_declarator_list.begin(); i != an_init_declarator_list.end(); ++i)
		{
			const declarator& declarator_node = get_declarator(i->main_node());
			const direct_declarator& direct_declarator_node = get_direct_declarator(declarator_node);

			//get the simple_declaration_node name
			const direct_declarator_first_part& first_part_node = get_first_part(direct_declarator_node);
			const boost::optional<const declarator_id&> opt_declarator_id_node = get<declarator_id>(&first_part_node);
			if(opt_declarator_id_node)
			{
				const declarator_id& declarator_id_node = *opt_declarator_id_node;
				if(boost::optional<const id_expression&> id_expression_node = get<id_expression>(&declarator_id_node))
				{
					if(boost::optional<const unqualified_id&> unqualified_id_node = get<unqualified_id>(id_expression_node))
					{
						if(boost::optional<const identifier&> identifier_node = get<identifier>(unqualified_id_node))
						{
							names.push_back(identifier_node->value());
						}
					}
				}
			}

			if(!is_a_function_declaration)
				is_a_function_declaration = is_function_declaration(declarator_node);
		}
	}

	if(is_a_class_declaration)
	{
		//analysis is already done
	}
	else if(is_a_class_forward_declaration)
	{
		if(!class_name.empty())
			scope_cursor_.add_to_current_scope(std::make_shared<class_>(class_name));
	}
	else if(is_a_function_declaration)
	{
		assert(opt_decl_specifier_seq_node);
		assert(opt_init_declarator_list_node);
		auto init_declarator_list_node = *opt_init_declarator_list_node;
		assert(init_declarator_list_node.size() == 1);

		auto decl_specifier_seq_node = *opt_decl_specifier_seq_node;
		auto declarator_node = get_declarator(init_declarator_list_node.front().main_node());
		scope_cursor_.add_to_current_scope(create_function(decl_specifier_seq_node, declarator_node));
	}
	else if(!is_a_function_declaration && !is_a_class_forward_declaration) //variable declaration
	{
		assert(opt_decl_specifier_seq_node);
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		auto opt_init_declarator_list_node = get_init_declarator_list(simple_declaration_node);
		assert(opt_init_declarator_list_node);
		auto init_declarator_list_node = *opt_init_declarator_list_node;

		std::vector<std::shared_ptr<variable>> variables = create_variables(decl_specifier_seq_node, init_declarator_list_node);
		//for each variable
		for
		(
			auto i = variables.begin();
			i != variables.end();
			++i
		)
		{
			scope_cursor_.add_to_current_scope(*i);
		}
	}
}

void
semantic_analyzer::analyze(const simple_template_type_specifier&)
{
}

void
semantic_analyzer::analyze(const switch_statement&)
{
}

void
semantic_analyzer::analyze(const template_declaration&)
{
}

void
semantic_analyzer::analyze(const template_id&)
{
}

void
semantic_analyzer::analyze(const try_block& syntax_node)
{
	analyze(get_compound_statement(syntax_node));
	analyze(get_handler_seq(syntax_node));
}

void
semantic_analyzer::analyze(const type_id_sizeof_expression&)
{
}

void
semantic_analyzer::analyze(const unary_sizeof_expression&)
{
}

void
semantic_analyzer::analyze(const using_declaration&)
{
}

void
semantic_analyzer::analyze(const using_directive&)
{
}

void
semantic_analyzer::analyze(const while_statement&)
{
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
semantic_analyzer::fill_class(class_& c, const class_specifier& class_specifier_node)
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
			class_::access access = class_::access::PRIVATE; //if nothing is specified, access is private
			if(auto opt_access_specifier_node = get_access_specifier(base_specifier_node))
			{
				access = get_access(*opt_access_specifier_node);
			}

			//get base class
			auto nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);
			std::shared_ptr<class_> base = find_class(nested_identifier_or_template_id_node);

			c.add(std::make_shared<class_::base_class>(base, access, is_virtual));
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
				if(auto opt_member_declaration_function_definition_node = get<member_declaration_function_definition>(opt_member_declaration_node))
				{
					auto function_definition_node = get_function_definition(*opt_member_declaration_function_definition_node);
					//analyze(function_definition_node);
				}
				else if(auto opt_member_declaration_member_declarator_list_node = get<member_declaration_member_declarator_list>(opt_member_declaration_node))
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
										if(c.name() == get_function_name(declarator_node)) //constructor/destructor?
										{
											if(!is_destructor_declaration(declarator_node)) //constructor
											{
												c.add
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
												c.set_destructor
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
										else
										{
											c.add
											(
												std::make_shared<class_::member<function>>
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
									else
									{
										c.add(std::make_shared<class_::member<variable>>(create_variable(decl_specifier_seq_node, declarator_node), current_access));
									}
								}
								else
								{
									if(!is_destructor_declaration(declarator_node))
									{
										c.add
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
									else
									{
										c.set_destructor
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
				else if(auto opt_member_declaration_unqualified_id_node = get<member_declaration_unqualified_id>(opt_member_declaration_node))
				{
				}
				else if(auto opt_using_declaration_node = get<using_declaration>(opt_member_declaration_node))
				{
				}
				else if(auto opt_template_declaration_node = get<template_declaration>(opt_member_declaration_node))
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
	//get the name of the function
	const std::string& name = get_function_name(declarator_node);

	//get the function's return type
	std::shared_ptr<const type> return_type = create_type(decl_specifier_seq_node, declarator_node);

	//get the function's parameter list
	std::list<function::parameter> parameters = create_parameters(declarator_node);

	return std::make_shared<function>
	(
		name,
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
	bool const_qualified = false; //useful for "const int" (where prefered form would have been "int const")
	bool volatile_qualified = false; //ditto

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
					if(auto found_class = std::dynamic_pointer_cast<class_>(found_name))
					{
						return_type = found_class;
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
	}

	if(!return_type)
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::bool_, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::char_, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::double_, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::float_, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::int_, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::long_double, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::long_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::long_long_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::short_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::unsigned_char, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::unsigned_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::unsigned_long_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::unsigned_long_long_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::unsigned_short_int, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::void_, scalpel::utility::null_deleter());
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
			return_type = std::shared_ptr<const built_in_type>(&built_in_type::wchar_t_, scalpel::utility::null_deleter());
		}
		else
		{
			throw std::runtime_error("Semantic analysis error: incorrect type");
		}
	}

	if(return_type)
	{
		if(const_qualified)
		{
			return_type = std::make_shared<const_>(return_type);
		}
		else if(volatile_qualified)
		{
			return_type = std::make_shared<volatile_>(return_type);
		}
	}

	if(auto opt_ptr_operator_seq_node = get_ptr_operator_seq(declarator_node))
	{
		auto ptr_operator_seq_node = *opt_ptr_operator_seq_node;
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
			if(auto unqualified_id_node = get<unqualified_id>(id_expression_node))
			{
				if(auto identifier_node = get<identifier>(unqualified_id_node))
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

