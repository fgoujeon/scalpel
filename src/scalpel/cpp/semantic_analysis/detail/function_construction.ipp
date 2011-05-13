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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_FUNCTION_CONSTRUCTION_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_DETAIL_FUNCTION_CONSTRUCTION_IPP

#include "other_entity_construction.hpp"
#include "type_construction.hpp"
#include "name_lookup.hpp"
#include "semantic_entity_analysis/identification_policies.hpp"
#include "syntax_node_analysis/function_definition.hpp"
#include "syntax_node_analysis/declarator.hpp"
#include "syntax_node_analysis/decl_specifier_seq.hpp"
#include <scalpel/cpp/semantic_entities/type_traits/is_class.hpp>
#include <scalpel/cpp/semantic_entities/type_traits/is_union.hpp>
#include <set>
#include <iostream>

namespace scalpel { namespace cpp { namespace semantic_analysis { namespace detail
{

template<class DeclarativeRegion>
function_ptr_variant
create_function
(
	const syntax_nodes::function_definition& function_definition_node,
	DeclarativeRegion& current_declarative_region,
	const bool is_class_member,
	const bool is_defined_in_class,
	const semantic_entities::member_access access
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;



	//
	//Analyze the decl-specifier-seq node, which defines the return type.
	//

	const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
		syntax_node_analysis::get_decl_specifier_seq(function_definition_node)
	;

	//create and/or get the type defined by the decl-specifier-seq node
	type_info info;
	if(opt_decl_specifier_seq_node)
	{
		info =
			create_type
			(
				*opt_decl_specifier_seq_node,
				true,
				current_declarative_region
			)
		;
	}

	//if the type is a new user defined type (class, union, enum, etc.)...
	if(info.opt_new_type)
	{
		assert(false); //not managed yet
	}

	//type definition -> error
	if(info.opt_defined_type)
	{
		throw std::runtime_error("error: new types may not be defined in a return type");
	}



	//
	//Analyze the declarator node.
	//

	declarator_entity_ptr_variant declarator_entity = create_entity
	(
		syntax_node_analysis::get_declarator(function_definition_node),
		&current_declarative_region,
		info.opt_complete_type,
		info.has_typedef_specifier,
		false,
		info.has_static_specifier,
		is_defined_in_class || info.has_inline_specifier,
		info.has_virtual_specifier,
		info.has_explicit_specifier,
		false,
		is_class_member,
		access
	);

	if(auto opt_constructor_entity = get<constructor*>(&declarator_entity))
		return *opt_constructor_entity;
	else if(auto opt_destructor_entity = get<destructor*>(&declarator_entity))
		return *opt_destructor_entity;
	else if(auto opt_operator_member_function_entity = get<operator_member_function*>(&declarator_entity))
		return *opt_operator_member_function_entity;
	else if(auto opt_conversion_function_entity = get<conversion_function*>(&declarator_entity))
		return *opt_conversion_function_entity;
	else if(auto opt_simple_member_function_entity = get<simple_member_function*>(&declarator_entity))
		return *opt_simple_member_function_entity;
	else if(auto opt_operator_function_entity = get<operator_function*>(&declarator_entity))
		return *opt_operator_function_entity;
	else if(auto opt_simple_function_entity = get<simple_function*>(&declarator_entity))
		return *opt_simple_function_entity;
	else
		assert(false);
}

template<class FunctionT>
FunctionT*
find_function
(
	const FunctionT& function_signature,
	semantic_entities::function_enclosing_declarative_region_ptr_variant& function_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	typedef typename semantic_entity_analysis::get_identification_policy<FunctionT>::policy_t identification_policy_t;

	//find the functions with the same identifier
	std::set<FunctionT*> found_functions =
		name_lookup::find_local
		<
			identification_policy_t,
			function_enclosing_declarative_region_ptr_variant,
			true,
			true,
			FunctionT
		>
		(
			identification_policy_t::get_identifier(function_signature),
			function_declarative_region
		)
	;

	//filter the found functions with the signature
	for
	(
		auto i = found_functions.begin();
		i != found_functions.end();
		++i
	)
	{
		FunctionT* found_function = *i;
		if(have_same_signature(*found_function, function_signature))
		{
			return found_function;
		}
	}

	//if nothing is found
	return 0;
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

