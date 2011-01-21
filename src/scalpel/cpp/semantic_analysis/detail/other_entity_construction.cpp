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

#include "other_entity_construction.hpp"
#include "class_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "semantic_entity_analysis/get_namespace.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/declarator.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

using namespace syntax_nodes;
using namespace semantic_entities;

declarator_entity_shared_ptr_variant
create_entity
(
	const syntax_nodes::declarator& declarator_node,
	const declarative_region_ptr_variant& current_declarative_region,
	boost::optional<semantic_entities::type_variant> opt_type,
	const bool has_typedef_specifier,
	const bool has_static_specifier,
	const bool has_inline_specifier,
	const bool has_virtual_specifier,
	const bool has_explicit_specifier,
	const bool has_pure_specifier,
	const bool is_class_member
)
{
	switch(syntax_node_analysis::get_declarator_type(declarator_node))
	{
		case syntax_node_analysis::declarator_type::SIMPLE_FUNCTION_DECLARATOR:
		{
			if(opt_type)
			{
				if(has_typedef_specifier)
				{
					opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region);

					return std::make_shared<semantic_entities::typedef_>
					(
						syntax_node_analysis::get_identifier(declarator_node).value(),
						*opt_type
					);
				}
				else
				{
					if(syntax_node_analysis::has_bracketed_type_qualifiers(declarator_node))
					{
						opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region);

						return std::make_shared<semantic_entities::variable>
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							*opt_type,
							has_static_specifier
						);
					}
					else
					{
						opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region, true);

						if(is_class_member)
						{
							return std::make_shared<semantic_entities::simple_member_function>
							(
								syntax_node_analysis::get_identifier(declarator_node).value(),
								*opt_type,
								create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
								syntax_node_analysis::has_ellipsis(declarator_node),
								has_inline_specifier,
								has_static_specifier,
								syntax_node_analysis::has_const_function_qualifier(declarator_node),
								syntax_node_analysis::has_volatile_function_qualifier(declarator_node),
								has_virtual_specifier,
								has_pure_specifier
							);
						}
						else
						{
							return std::make_shared<semantic_entities::simple_function>
							(
								syntax_node_analysis::get_identifier(declarator_node).value(),
								*opt_type,
								create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
								syntax_node_analysis::has_ellipsis(declarator_node),
								has_inline_specifier,
								has_static_specifier
							);
						}
					}
				}
			}
			else
			{
				if(!is_class_member)
					throw std::runtime_error("create_entity error: a constructor must be a class member");

				return std::make_shared<semantic_entities::constructor>
				(
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					syntax_node_analysis::has_ellipsis(declarator_node),
					has_inline_specifier,
					has_explicit_specifier
				);
			}
		}
		case syntax_node_analysis::declarator_type::DESTRUCTOR_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 2");

			if(!is_class_member)
				throw std::runtime_error("create_entity error: a destructor must be a class member");

			return std::make_shared<semantic_entities::destructor>
			(
				has_inline_specifier,
				has_virtual_specifier,
				has_pure_specifier
			);
		}
		case syntax_node_analysis::declarator_type::OPERATOR_FUNCTION_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 3");

			opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region, true);

			if(is_class_member)
			{
				return std::make_shared<operator_member_function>
				(
					get_operator_function_operator(declarator_node),
					*opt_type,
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					syntax_node_analysis::has_const_function_qualifier(declarator_node),
					syntax_node_analysis::has_volatile_function_qualifier(declarator_node),
					has_virtual_specifier,
					has_pure_specifier
				);
			}
			else
			{
				return std::make_shared<operator_function>
				(
					get_operator_function_operator(declarator_node),
					*opt_type,
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_static_specifier
				);
			}
		}
		case syntax_node_analysis::declarator_type::CONVERSION_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 3b");

			if(!is_class_member)
				throw std::runtime_error("create_entity error: a conversion function must be a class member");

			return std::make_shared<semantic_entities::conversion_function>
			(
				get_conversion_function_type(declarator_node, current_declarative_region),
				has_inline_specifier,
				syntax_node_analysis::has_const_function_qualifier(declarator_node),
				syntax_node_analysis::has_volatile_function_qualifier(declarator_node),
				has_virtual_specifier,
				has_pure_specifier
			);
		}
		case syntax_node_analysis::declarator_type::VARIABLE_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 4");

			opt_type = qualify_type(*opt_type, declarator_node, current_declarative_region);

			if(has_typedef_specifier)
			{
				return std::make_shared<semantic_entities::typedef_>
				(
					syntax_node_analysis::get_identifier(declarator_node).value(),
					*opt_type
				);
			}
			else
			{
				if(const function_type* opt_function_type = utility::get<function_type>(&*opt_type))
				{
					//the declaration looks like:
					//  typedef void fun_t(int);
					//  fun_t f;

					const function_type& ftype = *opt_function_type;
					const std::vector<type_variant>& parameter_types = ftype.parameter_types();

					function_parameter_list parameter_list;
					for(auto i = parameter_types.begin(); i != parameter_types.end(); ++i)
					{
						const type_variant& parameter_type = *i;
						parameter_list.push_back
						(
							std::make_shared<function_parameter>(parameter_type)
						);
					}

					if(is_class_member)
					{
						return std::make_shared<semantic_entities::simple_member_function>
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							ftype.return_type(),
							std::move(parameter_list),
							ftype.variadic(),
							has_inline_specifier,
							has_static_specifier,
							ftype.const_qualified(),
							ftype.volatile_qualified(),
							has_virtual_specifier,
							has_pure_specifier
						);
					}
					else
					{
						return std::make_shared<semantic_entities::simple_function>
						(
							syntax_node_analysis::get_identifier(declarator_node).value(),
							ftype.return_type(),
							std::move(parameter_list),
							ftype.variadic(),
							has_inline_specifier,
							has_static_specifier
						);
					}
				}
				else
				{
					return std::make_shared<semantic_entities::variable>
					(
						syntax_node_analysis::get_identifier(declarator_node).value(),
						*opt_type,
						has_static_specifier
					);
				}
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

	//find the namespace or namespace alias designated by the namespace alias
	std::string entity_name;
	if(boost::optional<const identifier&> opt_identifier_node = get<identifier>(&get_identifier_or_template_id(nested_identifier_or_template_id_node)))
		entity_name = opt_identifier_node->value();
	else
		assert(false);

	utility::shared_ptr_variant<namespace_, namespace_alias>::type found_entity =
		name_lookup::find
		<
			semantic_entity_analysis::identification_policies::by_name,
			false,
			false,
			namespace_,
			namespace_alias
		>
		(
			has_leading_double_colon(nested_identifier_or_template_id_node),
			get_nested_name_specifier(nested_identifier_or_template_id_node),
			entity_name,
			current_namespace.get()
		)
	;

	//get the namespace entity
	std::shared_ptr<namespace_> found_namespace = semantic_entity_analysis::get_namespace(found_entity);

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
	//find the namespace or namespace alias designated by the using directive
	utility::shared_ptr_variant<namespace_, namespace_alias>::type found_entity =
		name_lookup::find
		<
			semantic_entity_analysis::identification_policies::by_name,
			false,
			false,
			namespace_,
			namespace_alias
		>
		(
			has_leading_double_colon(using_directive_node),
			get_nested_name_specifier(using_directive_node),
			get_identifier(using_directive_node).value(),
			current_namespace.get()
		)
	;

	//get and return the namespace entity
	return semantic_entity_analysis::get_namespace(found_entity);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

