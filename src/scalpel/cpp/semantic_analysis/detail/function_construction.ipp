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
		current_declarative_region,
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

template<class DeclarativeRegion>
semantic_entities::type_variant
get_conversion_function_type
(
	const syntax_nodes::declarator& declarator_node,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const unqualified_id& unqualified_id_node = syntax_node_analysis::get_unqualified_id(declarator_node);
	boost::optional<const conversion_function_id&> opt_conversion_function_id_node = syntax_nodes::get<conversion_function_id>(&unqualified_id_node);
	assert(opt_conversion_function_id_node);
	return get_conversion_function_type(*opt_conversion_function_id_node, current_declarative_region);
}

template<class DeclarativeRegion>
semantic_entities::type_variant
get_conversion_function_type
(
	const syntax_nodes::conversion_function_id& conversion_function_id_node,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	const type_specifier_seq& type_specifier_seq_node = get_type_specifier_seq(conversion_function_id_node);



	//
	//Analyze the type-specifier-seq node
	//

	type_info info =
		create_type
		(
			type_specifier_seq_node,
			true,
			current_declarative_region
		)
	;

	//if the type is a new user defined type (class, union, enum, etc.)...
	if(info.opt_new_type)
	{
		assert(false); //TODO
	}

	//define the type, if appropriate
	if(info.opt_defined_type)
	{
		throw std::runtime_error("types may not be defined in parameter types");
	}

	assert(info.opt_complete_type);
	semantic_entities::type_variant type = *info.opt_complete_type;



	//
	//Add pointers and references
	//

	if(const optional_node<ptr_operator_seq>& opt_ptr_operator_seq_node = get_ptr_operator_seq(conversion_function_id_node))
	{
		const ptr_operator_seq& ptr_operator_seq_node = *opt_ptr_operator_seq_node;
		type = qualify_type(type, ptr_operator_seq_node, &current_declarative_region);
	}

	return type;
}

template<class DeclarativeRegion>
semantic_entities::function_parameter_list
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	DeclarativeRegion& current_declarative_region
)
{
	if(opt_parameter_declaration_list_node)
		return create_parameters(*opt_parameter_declaration_list_node, current_declarative_region);
	else
		return semantic_entities::function_parameter_list();
}

template<class DeclarativeRegion>
semantic_entities::function_parameter_list
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	function_parameter_list parameters;

	for
	(
		auto j = parameter_declaration_list_node.begin();
		j != parameter_declaration_list_node.end();
		++j
	)
	{
		const parameter_declaration& parameter_declaration_node = *j;
		const decl_specifier_seq& decl_specifier_seq_node = get_decl_specifier_seq(parameter_declaration_node);



		//
		//Analyze the decl-specifier-seq node, which defines the parameter type
		//

		type_info info =
			create_type
			(
				decl_specifier_seq_node,
				true,
				current_declarative_region
			)
		;

		//if the type is a new user defined type (class, union, enum, etc.)...
		if(info.opt_new_type)
		{
			assert(false); //TODO
		}

		//define the type, if appropriate
		if(info.opt_defined_type)
		{
			throw std::runtime_error("types may not be defined in parameter types");
		}

		assert(info.opt_complete_type);
		const semantic_entities::type_variant type = *info.opt_complete_type;



		//
		//Create the parameter
		//

		if(auto opt_declarator_node = get_declarator(parameter_declaration_node))
		{
			const declarator& declarator_node = *opt_declarator_node;

			std::unique_ptr<function_parameter> new_parameter
			(
				new function_parameter
				(
					qualify_type(type, declarator_node, current_declarative_region),
					syntax_node_analysis::get_identifier(declarator_node).value()
				)
			);
			parameters.push_back(std::move(new_parameter));
		}
		else if(auto opt_abstract_declarator_node = get_abstract_declarator(parameter_declaration_node))
		{
			const abstract_declarator& abstract_declarator_node = *opt_abstract_declarator_node;

			std::unique_ptr<function_parameter> new_parameter
			(
				new function_parameter
				(
					qualify_type(type, abstract_declarator_node, current_declarative_region)
				)
			);
			parameters.push_back(std::move(new_parameter));
		}
		else
		{
			//void f(void) == void f()
			bool empty_parameter_list = false;
			if(const fundamental_type* const opt_fundamental_type = get<fundamental_type>(&type))
			{
				empty_parameter_list =
					*opt_fundamental_type == fundamental_type::VOID &&
					parameter_declaration_list_node.size() == 1
				;
			}

			if(!empty_parameter_list)
			{
				std::unique_ptr<function_parameter> new_parameter
				(
					new function_parameter
					(
						type
					)
				);
				parameters.push_back(std::move(new_parameter));
			}
		}
	}

	return parameters;
}

template<class DeclarativeRegion>
std::vector<semantic_entities::type_variant>
create_parameter_types
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	if(opt_parameter_declaration_list_node)
		return create_parameter_types(*opt_parameter_declaration_list_node, current_declarative_region);
	else
		return std::vector<semantic_entities::type_variant>();
}

template<class DeclarativeRegion>
std::vector<semantic_entities::type_variant>
create_parameter_types
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	DeclarativeRegion& current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;

	semantic_entities::function_parameter_list parameters =
		create_parameters(parameter_declaration_list_node, current_declarative_region)
	;

	std::vector<semantic_entities::type_variant> parameter_types;
	for(auto i = parameters.begin(); i != parameters.end(); ++i)
	{
		const function_parameter& p = *i;
		parameter_types.push_back(p.type());
	}

	return parameter_types;
}

}}}} //namespace scalpel::cpp::semantic_analysis::detail

#endif

