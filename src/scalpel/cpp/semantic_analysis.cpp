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
using namespace detail::semantic_analysis;

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
				analyze(*opt_simple_declaration_node, namespace_entity);
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
	assert(class_name != "");
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
	std::shared_ptr<class_> c,
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
				access = get_access(*opt_access_specifier_node);
			}

			//get base class
			auto nested_identifier_or_template_id_node = get_nested_identifier_or_template_id(base_specifier_node);
			std::shared_ptr<class_> base_class =
				name_lookup::find<class_, false, false>(nested_identifier_or_template_id_node, c)
			;

			c->add_base_class(base_class, access, is_virtual);
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
											c->add_member
											(
												create_operator_function(decl_specifier_seq_node, declarator_node, c),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												has_virtual_specifier(decl_specifier_seq_node),
												has_pure_specifier(member_declarator_declarator_node)
											);
										}
										else if(is_conversion_function_declaration(declarator_node)) //conversion function
										{
											c->add_member
											(
												std::make_shared<class_::conversion_function>
												(
													get_conversion_function_type(declarator_node, c),
													has_inline_specifier(decl_specifier_seq_node)
												),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												has_virtual_specifier(decl_specifier_seq_node),
												has_pure_specifier(member_declarator_declarator_node)
											);
										}
										else if(c->name() == get_identifier(declarator_node).value()) //constructor or destructor
										{
											if(!is_destructor_declaration(declarator_node)) //constructor
											{
												c->add_member
												(
													std::make_shared<class_::constructor>
													(
														std::move(create_parameters(declarator_node, c)),
														has_inline_specifier(decl_specifier_seq_node),
														has_explicit_specifier(decl_specifier_seq_node)
													),
													current_access
												);
											}
											else //destructor
											{
												c->set_destructor
												(
													std::make_shared<class_::destructor>
													(
														has_inline_specifier(decl_specifier_seq_node)
													),
													current_access,
													has_virtual_specifier(decl_specifier_seq_node),
													has_pure_specifier(member_declarator_declarator_node)
												);
											}
										}
										else //simple function
										{
											c->add_member
											(
												create_simple_function(decl_specifier_seq_node, declarator_node, c),
												current_access,
												is_qualified<str::const_>(declarator_node),
												is_qualified<str::volatile_>(declarator_node),
												has_virtual_specifier(decl_specifier_seq_node),
												has_pure_specifier(member_declarator_declarator_node)
											);
										}
									}
									else //variable
									{
										c->add_member
										(
											create_variable(decl_specifier_seq_node, declarator_node, c),
											current_access,
											has_mutable_specifier(decl_specifier_seq_node)
										);
									}
								}
								else
								{
									if(is_conversion_function_declaration(declarator_node)) //conversion function
									{
										c->add_member
										(
											std::make_shared<class_::conversion_function>
											(
												get_conversion_function_type(declarator_node, c),
												false
											),
											current_access,
											is_qualified<str::const_>(declarator_node),
											is_qualified<str::volatile_>(declarator_node),
											false,
											false
										);
									}
									else if(c->name() == get_identifier(declarator_node).value()) //constructor or destructor
									{
										if(!is_destructor_declaration(declarator_node)) //constructor
										{
											c->add_member
											(
												std::make_shared<class_::constructor>
												(
													std::move(create_parameters(declarator_node, c)),
													false,
													false
												),
												current_access
											);
										}
										else //destructor
										{
											c->set_destructor
											(
												std::make_shared<class_::destructor>(false),
												current_access,
												false,
												false
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

									std::shared_ptr<class_> new_nested_class = create_class(class_specifier_node);
									c->add_member
									(
										new_nested_class,
										current_access
									);
									fill_class(new_nested_class, class_specifier_node);
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

semantic_entities::type_shared_ptr_variant
decorate_type
(
	semantic_entities::type_shared_ptr_variant type,
	const bool is_const,
	const bool is_volatile
)
{
	if(is_const)
		type = std::make_shared<const const_>(type);
	if(is_volatile)
		type = std::make_shared<const volatile_>(type);

	return type;
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
		detail::semantic_analysis::name_lookup::find<namespace_>
		(
			nested_identifier_or_template_id_node,
			current_namespace
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
	return detail::semantic_analysis::name_lookup::find<namespace_>
	(
		nested_identifier_or_template_id_node,
		current_namespace
	);
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp

