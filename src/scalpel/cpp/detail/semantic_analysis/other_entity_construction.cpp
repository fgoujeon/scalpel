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

#include "other_entity_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "syntax_node_analysis.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

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

	switch(syntax_node_analysis::get_declarator_type(declarator_node))
	{
		case syntax_node_analysis::declarator_type::SIMPLE_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				return semantic_entities::simple_function::make_shared
				(
					syntax_node_analysis::get_identifier(declarator_node).value(),
					*opt_type,
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_static_specifier
				);
			else
				return std::make_shared<semantic_entities::class_::constructor>
				(
					create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
					has_inline_specifier,
					has_explicit_specifier
				);
		}
		case syntax_node_analysis::declarator_type::DESTRUCTOR_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 2");

			return std::make_shared<semantic_entities::class_::destructor>
			(
				has_inline_specifier
			);
		}
		case syntax_node_analysis::declarator_type::OPERATOR_FUNCTION_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 3");

			return create_operator_function
			(
				declarator_node,
				*opt_type,
				has_inline_specifier,
				has_static_specifier,
				current_declarative_region
			);
		}
		case syntax_node_analysis::declarator_type::CONVERSION_FUNCTION_DECLARATOR:
		{
			if(opt_type)
				throw std::runtime_error("create_entity error 3b");

			return std::make_shared<semantic_entities::class_::conversion_function>
			(
				get_conversion_function_type(declarator_node, current_declarative_region),
				has_inline_specifier
			);
		}
		case syntax_node_analysis::declarator_type::VARIABLE_DECLARATOR:
		{
			if(!opt_type)
				throw std::runtime_error("create_entity error 4");

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
				return std::make_shared<semantic_entities::variable>
				(
					syntax_node_analysis::get_identifier(declarator_node).value(),
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
			semantic_graph_analysis::name_lookup::find<namespace_or_namespace_alias_shared_ptr_variant>
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
		semantic_graph_analysis::name_lookup::find<namespace_or_namespace_alias_shared_ptr_variant>
		(
			nested_identifier_or_template_id_node,
			current_namespace
		)
	);
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

