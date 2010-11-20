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

#ifndef SCALPEL_CPP_SEMANTIC_ANALYSIS_IPP
#define SCALPEL_CPP_SEMANTIC_ANALYSIS_IPP

#include "detail/semantic_analysis/basic_functions.hpp"
#include "detail/semantic_analysis/name_lookup.hpp"
#include <scalpel/utility/variant.hpp>
#include <sstream>

namespace scalpel { namespace cpp
{

namespace semantic_analysis
{

template<class DeclarativeRegionT>
void
analyze
(
	const syntax_nodes::function_definition& function_definition_node,
	std::shared_ptr<DeclarativeRegionT> current_declarative_region
)
{
	using namespace syntax_nodes;
	using namespace semantic_entities;
	namespace detail = detail::semantic_analysis;

	const boost::optional<const simple_function_definition&> opt_simple_function_definition =
		get<simple_function_definition>(&function_definition_node)
	;
	const boost::optional<const try_block_function_definition&> opt_try_block_function_definition =
		get<try_block_function_definition>(&function_definition_node)
	;
	assert(opt_simple_function_definition || opt_try_block_function_definition);

	const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
		opt_simple_function_definition ?
		get_decl_specifier_seq(*opt_simple_function_definition) :
		get_decl_specifier_seq(*opt_try_block_function_definition)
	;
	const declarator& declarator_node =
		opt_simple_function_definition ?
		get_declarator(*opt_simple_function_definition) :
		get_declarator(*opt_try_block_function_definition)
	;

	//If the function definition has a nested-name-specifier
	//(like in "void n::f(){/*...*/}"), the function must be already declared.
	//Check whether it's the case.
	bool declaration_must_exist = false;
	boost::optional<nested_identifier_or_template_id> opt_nested_identifier_or_template_id_node;
	{
		auto direct_declarator_node = get_direct_declarator(declarator_node);
		auto first_part_node = get_first_part(direct_declarator_node);
		auto opt_declarator_id_node = get<declarator_id>(&first_part_node);
		if(opt_declarator_id_node)
		{
			auto declarator_id_node = *opt_declarator_id_node;
			if(opt_nested_identifier_or_template_id_node = get<nested_identifier_or_template_id>(&declarator_id_node))
			{
				auto nested_identifier_or_template_id_node = *opt_nested_identifier_or_template_id_node;
				if(get_nested_name_specifier(nested_identifier_or_template_id_node))
				{
					declaration_must_exist = true;
				}
			}
		}
	}



	//
	//Analyze the decl-specifier-seq node.
	//

	boost::optional<type_shared_ptr_variant> opt_undecorated_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_explicit_specifier = false;

	if(opt_decl_specifier_seq_node)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = detail::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = detail::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = detail::has_inline_specifier(decl_specifier_seq_node);
		has_explicit_specifier = detail::has_explicit_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(detail::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case detail::decl_specifier_seq_type::CLASS_DECLARATION:
			{
				const syntax_nodes::class_specifier& class_specifier_node = detail::get_class_specifier(decl_specifier_seq_node);

				std::shared_ptr<class_> new_class = create_class(class_specifier_node);
				current_declarative_region->add_member(new_class);
				fill_class(new_class, class_specifier_node);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case detail::decl_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node = detail::get_class_elaborated_specifier(decl_specifier_seq_node);

				std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
				current_declarative_region->add_member(new_class);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case detail::decl_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_undecorated_type = create_type(decl_specifier_seq_node, current_declarative_region);
				break;
			}
			case detail::decl_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//decorate type
		if(opt_undecorated_type)
			opt_undecorated_type = decorate_type(*opt_undecorated_type, decl_specifier_seq_node);
	}



	//
	//Analyze and process the declarator node.
	//

	declarator_entity_shared_ptr_variant declarator_entity = create_entity
	(
		declarator_node,
		current_declarative_region,
		opt_undecorated_type,
		has_typedef_specifier,
		has_static_specifier,
		has_inline_specifier,
		has_explicit_specifier
	);

	if(auto opt_constructor_entity = get<std::shared_ptr<class_::constructor>>(&declarator_entity))
	{
	}
	else if(auto opt_destructor_entity = get<std::shared_ptr<class_::destructor>>(&declarator_entity))
	{
	}
	else if(auto opt_operator_function_entity = get<std::shared_ptr<operator_function>>(&declarator_entity))
	{
	}
	else if(auto opt_conversion_function_entity = get<std::shared_ptr<class_::conversion_function>>(&declarator_entity))
	{
	}
	else if(auto opt_simple_function_entity = get<std::shared_ptr<simple_function>>(&declarator_entity))
	{
		std::shared_ptr<simple_function> new_function = *opt_simple_function_entity;

		//this function pointer will point to either new_function or
		//(if any) to the already existing (undefined) function
		std::shared_ptr<simple_function> function_to_be_defined;


		//find the functions of the same name
		std::set<std::shared_ptr<simple_function>> found_functions;
		if(opt_nested_identifier_or_template_id_node)
		{
			found_functions =
				detail::name_lookup::find<simple_function, true, true>
				(
					*opt_nested_identifier_or_template_id_node,
					current_declarative_region
				)
			;
		}
		else
		{
			found_functions =
				detail::name_lookup::find<simple_function, true, true>
				(
					identifier(new_function->name()),
					current_declarative_region
				)
			;
		}

		//filter the found functions with signature
		for
		(
			auto i = found_functions.begin();
			i != found_functions.end();
			++i
		)
		{
			std::shared_ptr<simple_function> found_function = *i;
			if(found_function->has_same_signature(*new_function))
			{
				function_to_be_defined = found_function;
				break;
			}
		}

		//
		if(declaration_must_exist && !function_to_be_defined)
		{
			std::ostringstream oss;
			oss << new_function->name() << " is not declared";
			throw std::runtime_error(oss.str().c_str());
		}

		if(!function_to_be_defined)
		{
			//declare the function and add it to the current declarative region
			function_to_be_defined = new_function;
			current_declarative_region->add_member(new_function);
		}

		//check whether the function is undefined as expected
		if(function_to_be_defined->defined())
		{
			std::ostringstream oss;
			oss << "Redefinition of " << function_to_be_defined->name();
			throw std::runtime_error(oss.str().c_str());
		}

		//TODO define the function
		function_to_be_defined->body(std::make_shared<semantic_entities::statement_block>());
	}
	else
		assert(false);
}

} //namespace semantic_analysis

}} //namespace scalpel::cpp

#endif

