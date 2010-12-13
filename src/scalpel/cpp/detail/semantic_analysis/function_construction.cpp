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

#include "function_construction.hpp"
#include "class_construction.hpp"
#include "type_construction.hpp"
#include "other_entity_construction.hpp"
#include "semantic_graph_analysis.hpp"

namespace scalpel { namespace cpp { namespace detail { namespace semantic_analysis
{

using namespace syntax_nodes;
using namespace semantic_entities;

function_shared_ptr_variant
create_function
(
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	//
	//Analyze the decl-specifier-seq node.
	//

	boost::optional<type_shared_ptr_variant> opt_undecorated_type;
	bool has_typedef_specifier = false;
	bool has_static_specifier = false;
	bool has_inline_specifier = false;
	bool has_explicit_specifier = false;

	if
	(
		const optional_node<decl_specifier_seq>& opt_decl_specifier_seq_node =
			syntax_node_analysis::get_decl_specifier_seq(function_definition_node)
	)
	{
		const decl_specifier_seq& decl_specifier_seq_node = *opt_decl_specifier_seq_node;

		has_typedef_specifier = syntax_node_analysis::has_typedef_specifier(decl_specifier_seq_node);
		has_static_specifier = syntax_node_analysis::has_static_specifier(decl_specifier_seq_node);
		has_inline_specifier = syntax_node_analysis::has_inline_specifier(decl_specifier_seq_node);
		has_explicit_specifier = syntax_node_analysis::has_explicit_specifier(decl_specifier_seq_node);

		//create and/or get undecorated type
		switch(syntax_node_analysis::get_decl_specifier_seq_type(decl_specifier_seq_node))
		{
			case syntax_node_analysis::type_specifier_seq_type::CLASS_DECLARATION:
			{
				throw std::runtime_error("error: new types may not be defined in a return type");
				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::CLASS_FORWARD_DECLARATION:
			{
				assert(false); //not managed yet

				const syntax_nodes::class_elaborated_specifier& class_elaborated_specifier_node =
					syntax_node_analysis::get_class_elaborated_specifier(decl_specifier_seq_node)
				;

				std::shared_ptr<class_> new_class = create_class(class_elaborated_specifier_node);
				//current_declarative_region->add_member(new_class);

				opt_undecorated_type = std::shared_ptr<const class_>(new_class);

				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::SIMPLE_TYPE:
			{
				opt_undecorated_type = create_type(decl_specifier_seq_node, current_declarative_region);
				break;
			}
			case syntax_node_analysis::type_specifier_seq_type::NO_TYPE:
			{
				break;
			}
		}

		//decorate type
		if(opt_undecorated_type)
			opt_undecorated_type = decorate_type(*opt_undecorated_type, decl_specifier_seq_node);
	}



	//
	//Analyze the declarator node.
	//

	declarator_entity_shared_ptr_variant declarator_entity = create_entity
	(
		syntax_node_analysis::get_declarator(function_definition_node),
		current_declarative_region,
		opt_undecorated_type,
		has_typedef_specifier,
		has_static_specifier,
		has_inline_specifier,
		has_explicit_specifier
	);

	if(auto opt_constructor_entity = get<constructor>(&declarator_entity))
		return *opt_constructor_entity;
	else if(auto opt_destructor_entity = get<destructor>(&declarator_entity))
		return *opt_destructor_entity;
	else if(auto opt_operator_function_entity = get<operator_function>(&declarator_entity))
		return *opt_operator_function_entity;
	else if(auto opt_conversion_function_entity = get<conversion_function>(&declarator_entity))
		return *opt_conversion_function_entity;
	else if(auto opt_simple_function_entity = get<simple_function>(&declarator_entity))
		return *opt_simple_function_entity;
	else
		assert(false);
}

void
define_function
(
	const function_shared_ptr_variant& function_entity,
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	if(auto opt_constructor_entity = get<constructor>(&function_entity))
		(*opt_constructor_entity)->body(std::make_shared<semantic_entities::statement_block>());
	else if(auto opt_destructor_entity = get<destructor>(&function_entity))
		(*opt_destructor_entity)->body(std::make_shared<semantic_entities::statement_block>());
	else if(auto opt_operator_function_entity = get<operator_function>(&function_entity))
		(*opt_operator_function_entity)->body(std::make_shared<semantic_entities::statement_block>());
	else if(auto opt_conversion_function_entity = get<conversion_function>(&function_entity))
		(*opt_conversion_function_entity)->body(std::make_shared<semantic_entities::statement_block>());
	else if(auto opt_simple_function_entity = get<simple_function>(&function_entity))
		(*opt_simple_function_entity)->body(std::make_shared<semantic_entities::statement_block>());
	else
		assert(false);
}

boost::optional<function_shared_ptr_variant>
find_function
(
	const function_shared_ptr_variant function_signature,
	const syntax_nodes::function_definition& function_definition_node,
	const semantic_entities::declarative_region_shared_ptr_variant current_declarative_region
)
{
	if(auto opt_constructor_entity = get<constructor>(&function_signature))
	{
		assert(false); //not managed yet
	}
	else if(auto opt_destructor_entity = get<destructor>(&function_signature))
	{
		assert(false); //not managed yet
	}
	else if(auto opt_operator_function_signature = get<operator_function>(&function_signature))
	{
		assert(false); //not managed yet
	}
	else if(auto opt_conversion_function_signature = get<conversion_function>(&function_signature))
	{
		assert(false); //not managed yet
	}
	else if(auto opt_simple_function_signature = get<simple_function>(&function_signature))
	{
		std::shared_ptr<simple_function> function_declaration =
			find_function
			<
				semantic_graph_analysis::identifier_getting_policies::get_name,
				simple_function
			>
			(
				*opt_simple_function_signature,
				function_definition_node,
				current_declarative_region
			)
		;
		if(function_declaration)
			return function_shared_ptr_variant(function_declaration);
	}
	else
		assert(false);

	return boost::optional<function_shared_ptr_variant>();
}

std::shared_ptr<semantic_entities::operator_function>
create_operator_function
(
	const syntax_nodes::declarator& declarator_node,
	const semantic_entities::type_shared_ptr_variant type,
	const bool is_inline,
	const bool is_static,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	//
	//get the overloaded operator
	//
	semantic_entities::overloadable_operator op = semantic_entities::overloadable_operator::AMPERSAND;

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
			op = semantic_entities::overloadable_operator::NEW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::delete_>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DELETE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow_asterisk>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::ARROW_ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::PLUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::MINUS_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::ASTERISK_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::SLASH_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::PERCENT_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::CIRCUMFLEX_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::AMPERSAND_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::PIPE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_RIGHT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::EXCLAMATION_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket_equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET_EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_ampersand>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_pipe>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_plus>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::double_minus>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::DOUBLE_MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::arrow>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::ARROW;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::round_brackets>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::ROUND_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::square_brackets>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::SQUARE_BRACKETS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::comma>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::COMMA;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::plus>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::PLUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::minus>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::MINUS;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::asterisk>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::ASTERISK;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::slash>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::SLASH;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::percent>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::PERCENT;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::circumflex>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::CIRCUMFLEX;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::ampersand>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::AMPERSAND;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::pipe>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::PIPE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::tilde>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::TILDE;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::exclamation>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::EXCLAMATION;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::equal>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::EQUAL;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::left_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::LEFT_ANGLE_BRACKET;
		else if(syntax_nodes::get<syntax_nodes::predefined_text_node<syntax_nodes::str::right_angle_bracket>>(&simple_operator_node))
			op = semantic_entities::overloadable_operator::RIGHT_ANGLE_BRACKET;
		else
			assert(false);
	}
	else if(auto opt_array_operator_node = syntax_nodes::get<syntax_nodes::array_operator>(&operator_node))
	{
		auto array_operator_node = *opt_array_operator_node;

		if(syntax_nodes::get<syntax_nodes::new_array_operator>(&array_operator_node))
			op = semantic_entities::overloadable_operator::NEW_ARRAY;
		else if(syntax_nodes::get<syntax_nodes::delete_array_operator>(&array_operator_node))
			op = semantic_entities::overloadable_operator::DELETE_ARRAY;
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
		create_parameters(syntax_node_analysis::get_parameter_declaration_list(declarator_node), current_declarative_region),
		is_inline,
		is_static
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

semantic_entities::function_parameter_list
create_parameters
(
	boost::optional<const syntax_nodes::parameter_declaration_list&> opt_parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	if(opt_parameter_declaration_list_node)
		return create_parameters(*opt_parameter_declaration_list_node, current_declarative_region);
	else
		return semantic_entities::function_parameter_list();
}

semantic_entities::function_parameter_list
create_parameters
(
	const syntax_nodes::parameter_declaration_list& parameter_declaration_list_node,
	const declarative_region_shared_ptr_variant current_declarative_region
)
{
	function_parameter_list parameters;

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
				std::make_shared<function_parameter>
				(
					decorate_type(type, declarator_node),
					syntax_node_analysis::get_identifier(declarator_node).value()
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
				std::make_shared<function_parameter>
				(
					type,
					""
				)
			);
		}
		else
		{
			parameters.push_back
			(
				std::make_shared<function_parameter>
				(
					type,
					""
				)
			);
		}
	}

	return parameters;
}

}}}} //namespace scalpel::cpp::detail::semantic_analysis

