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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_OTHER_ENTITY_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_OTHER_ENTITY_CONSTRUCTION_IPP

#include "class_construction.hpp"
#include "function_construction.hpp"
#include "type_construction.hpp"
#include "semantic_entity_analysis/get_namespace.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/declarator.hpp"

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class Namespace>
std::unique_ptr<semantic_entities::namespace_alias>
create_namespace_alias
(
	const syntax_nodes::namespace_alias_definition& namespace_alias_definition_node,
	Namespace& current_namespace
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

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

	utility::ptr_variant<namespace_, namespace_alias>::type found_entity =
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
			&current_namespace
		)
	;

	//get the namespace entity
	namespace_& found_namespace = semantic_entity_analysis::get_namespace(found_entity);

	//create the namespace alias semantic entity
	return std::unique_ptr<namespace_alias>
	(
		new namespace_alias
		(
			get_identifier(namespace_alias_definition_node).value(),
			found_namespace
		)
	);
}

template<class Namespace>
semantic_entities::namespace_&
find_using_directive_namespace
(
	const syntax_nodes::using_directive& using_directive_node,
	Namespace& current_namespace
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	//find the namespace or namespace alias designated by the using directive
	utility::ptr_variant<namespace_, namespace_alias>::type found_entity =
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
			&current_namespace
		)
	;

	//get and return the namespace entity
	return semantic_entity_analysis::get_namespace(found_entity);
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

