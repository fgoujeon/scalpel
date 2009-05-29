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

#include "conversion_functions.hpp"

#include <iostream>
#include <scalpel/util/extern_strings.hpp>
#include "../../../syntax_tree.hpp"
#include "../grammar.hpp"
#include "basic_functions.hpp"
#include "special_conversion_functions.hpp"
#include "node_finder_and_converter.hpp"
#include "space_conversion_functions.hpp"
#include "sequence_node_converter.hpp"
#include "alternative_node_converter.hpp"

using namespace scalpel::cpp::syntax_nodes;

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

arrow_pseudo_destructor_name
convert_arrow_pseudo_destructor_name(const tree_node_t& node)
{
	assert(node.value.id() == id_t::ARROW_PSEUDO_DESTRUCTOR_NAME);

	return arrow_pseudo_destructor_name();
}

assignment_expression_condition
convert_assignment_expression_condition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ASSIGNMENT_EXPRESSION_CONDITION);

	tree_node_iterator_t type_specifier_seq_it = find_node<id_t::TYPE_SPECIFIER_SEQ>(node);
	tree_node_iterator_t declarator_it = find_node<id_t::DECLARATOR>(node);
	tree_node_iterator_t assignment_expression_it = find_node<id_t::ASSIGNMENT_EXPRESSION>(node);

	return assignment_expression_condition
	(
		convert_node<type_specifier_seq>(*type_specifier_seq_it),
		convert_next_space(node, type_specifier_seq_it),
		convert_node<declarator>(*declarator_it),
		convert_next_space(node, declarator_it),
		convert_previous_space(node, assignment_expression_it),
		convert_node<assignment_expression>(*assignment_expression_it)
	);
}

character_literal
convert_character_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CHARACTER_LITERAL);

	bool wide = false;

	tree_node_iterator_t i = node.children.begin();
	if(get_value(*i) == "L")
	{
		wide = true;
		++i;
	}

	++i; //iterate to string value

	return character_literal
	(
		wide,
		get_value(*i)
	);
}

class_head
convert_class_head(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CLASS_HEAD);

	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t template_id_it = find_node<id_t::TEMPLATE_ID>(node);
	tree_node_iterator_t identifier_it = find_node<id_t::IDENTIFIER>(node);
	tree_node_iterator_t base_clause_it = find_node<id_t::BASE_CLAUSE>(node);

    return class_head
    (
		find_and_convert_node<class_key, id_t::CLASS_KEY>(node),
		convert_previous_space(node, nested_name_specifier_it),
		convert_optional<nested_name_specifier>(node, nested_name_specifier_it),
		convert_previous_space(node, template_id_it),
		convert_optional<template_id>(node, template_id_it),
		convert_previous_space(node, identifier_it),
		convert_optional<identifier>(node, identifier_it),
		convert_previous_space(node, base_clause_it),
		convert_optional<base_clause>(node, base_clause_it)
	);
}

class_template_elaborated_specifier
convert_class_template_elaborated_specifier(const tree_node_t& node)
{
	assert(node.value.id() == id_t::CLASS_TEMPLATE_ELABORATED_SPECIFIER);

	tree_node_iterator_t class_key_it = node.children.begin();
	tree_node_iterator_t double_colon_it = find_node(node, "::");
	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t template_id_it = find_node<id_t::TEMPLATE_ID>(node);

	return class_template_elaborated_specifier
	(
		convert_node<class_key>(*class_key_it),
		convert_next_space(node, class_key_it),
		double_colon_it != node.children.end(),
		convert_next_space(node, double_colon_it),
		convert_optional<nested_name_specifier>(node, nested_name_specifier_it),
		convert_next_space(node, nested_name_specifier_it),
		convert_node<template_id>(*template_id_it)
	);
}

delete_array_operator
convert_delete_array_operator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DELETE_ARRAY_OPERATOR);

	return delete_array_operator();
}

direct_abstract_declarator
convert_direct_abstract_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_ABSTRACT_DECLARATOR);

	return direct_abstract_declarator();
}

dot_pseudo_destructor_name
convert_dot_pseudo_destructor_name(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DOT_PSEUDO_DESTRUCTOR_NAME);

	return dot_pseudo_destructor_name();
}

empty_initializer_list_initializer_clause
convert_empty_initializer_list_initializer_clause(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EMPTY_INITIALIZER_LIST_INITIALIZER_CLAUSE);

	return empty_initializer_list_initializer_clause();
}

enum_elaborated_specifier
convert_enum_elaborated_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ENUM_ELABORATED_SPECIFIER);

	return enum_elaborated_specifier();
}

enum_specifier
convert_enum_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ENUM_SPECIFIER);

	return enum_specifier();
}

floating_literal
convert_floating_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FLOATING_LITERAL);

	return floating_literal(get_only_child_value(node));
}

function_definition
convert_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FUNCTION_DEFINITION);

	tree_node_iterator_t decl_specifier_seq_it = find_node
	<
		id_t::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1,
		id_t::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2,
		id_t::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3
	>(node);
	tree_node_iterator_t declarator_it = find_node<id_t::DECLARATOR>(node);
	tree_node_iterator_t ctor_initializer_it = find_node<id_t::CTOR_INITIALIZER>(node);
	tree_node_iterator_t compound_statement_it = find_node<id_t::COMPOUND_STATEMENT>(node);
	tree_node_iterator_t function_try_block_it = find_node<id_t::FUNCTION_TRY_BLOCK>(node);

    return function_definition
    (
		convert_optional<decl_specifier_seq>(node, decl_specifier_seq_it),
		convert_next_space(node, decl_specifier_seq_it),
		convert_node<declarator>(*declarator_it),
		convert_next_space(node, declarator_it),
		convert_optional<ctor_initializer>(node, ctor_initializer_it),
		convert_next_space(node, ctor_initializer_it),
		convert_optional<compound_statement>(node, compound_statement_it),
		convert_optional<function_try_block>(node, function_try_block_it)
    );
}

function_try_block
convert_function_try_block(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FUNCTION_TRY_BLOCK);

	tree_node_iterator_t try_keyword_it = node.children.begin();
	tree_node_iterator_t ctor_initializer_it = find_node<id_t::CTOR_INITIALIZER>(node);
	tree_node_iterator_t compound_statement_it = find_node<id_t::COMPOUND_STATEMENT>(node);
	tree_node_iterator_t handler_seq_it = find_node<id_t::HANDLER_SEQ>(node);

	handler_seq handler_seq_node;
	if(handler_seq_it != node.children.end())
		handler_seq_node = convert_node<handler_seq>(*handler_seq_it);

	return function_try_block
	(
		convert_next_space(node, try_keyword_it),
		convert_optional<ctor_initializer>(node, ctor_initializer_it),
		convert_next_space(node, ctor_initializer_it),
		convert_node<compound_statement>(*compound_statement_it),
		convert_next_space(node, compound_statement_it),
		handler_seq_node
	);
}

identifier
convert_identifier(const tree_node_t& node)
{
    assert
    (
        node.value.id() == id_t::IDENTIFIER ||
        node.value.id() == id_t::TYPE_NAME
    );

    return identifier(get_only_child_value(node));
}

initializer_list_initializer_clause
convert_initializer_list_initializer_clause(const tree_node_t& node)
{
    assert(node.value.id() == id_t::INITIALIZER_LIST_INITIALIZER_CLAUSE);

	return initializer_list_initializer_clause
	(
	);
}

integer_literal
convert_integer_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::INTEGER_LITERAL);

	return integer_literal
	(
		get_value(get_only_child_node(node))
	);
}

member_declaration_function_definition
convert_member_declaration_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION_FUNCTION_DEFINITION);

    return member_declaration_function_definition
    (
        find_and_convert_node<function_definition, id_t::FUNCTION_DEFINITION>(node)
    );
}

member_declaration_member_declarator_list
convert_member_declaration_member_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST);

	tree_node_iterator_t decl_specifier_seq_it = find_node<id_t::MEMBER_DECLARATION_DECL_SPECIFIER_SEQ>(node);
	tree_node_iterator_t member_declarator_list_it = find_node<id_t::MEMBER_DECLARATOR_LIST>(node);

    return member_declaration_member_declarator_list
    (
        convert_optional<decl_specifier_seq>(node, decl_specifier_seq_it),
		convert_next_space(node, decl_specifier_seq_it),
        convert_optional<member_declarator_list>(node, member_declarator_list_it),
		convert_next_space(node, member_declarator_list_it)
    );
}

member_declaration_unqualified_id
convert_member_declaration_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION_UNQUALIFIED_ID);

	tree_node_iterator_t leading_double_colon_it = find_node(node, "::");
	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t template_keyword_it = find_node(node, "template");
	tree_node_iterator_t unqualified_id_it = find_node<id_t::UNQUALIFIED_ID>(node);

    return member_declaration_unqualified_id
    (
		leading_double_colon_it != node.children.end(),
		convert_next_space(node, leading_double_colon_it),
		convert_node<nested_name_specifier>(*nested_name_specifier_it),
		convert_next_space(node, nested_name_specifier_it),
		template_keyword_it != node.children.end(),
		convert_next_space(node, template_keyword_it),
		convert_node<unqualified_id>(*unqualified_id_it),
		convert_next_space(node, unqualified_id_it)
    );
}

member_declarator_bit_field_member
convert_member_declarator_bit_field_member(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATOR_BIT_FIELD_MEMBER);

	tree_node_iterator_t identifier_it = find_node<id_t::IDENTIFIER>(node);
	tree_node_iterator_t colon_it = find_node(node, ":");

    return member_declarator_bit_field_member
    (
		convert_optional<identifier>(node, identifier_it),
		convert_next_space(node, identifier_it),
		convert_next_space(node, colon_it),
        find_and_convert_node<conditional_expression, id_t::CONDITIONAL_EXPRESSION>(node)
    );
}

member_declarator_declarator
convert_member_declarator_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATOR_DECLARATOR);

    return member_declarator_declarator
    (
        find_and_convert_node<declarator, id_t::DECLARATOR>(node),
        check_node_existence(node, id_t::PURE_SPECIFIER, 1)
    );
}

member_specification_access_specifier
convert_member_specification_access_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_SPECIFICATION_ACCESS_SPECIFIER);

	tree_node_iterator_t access_specifier_it = find_node<id_t::ACCESS_SPECIFIER>(node);

    return member_specification_access_specifier
    (
        convert_node<access_specifier>(*access_specifier_it),
		convert_next_space(node, access_specifier_it)
    );
}

nested_identifier_or_template_id
convert_nested_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID);

    return nested_identifier_or_template_id
    (
        check_node_existence(node, "::", 0),
        find_and_convert_node<optional_node<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
        find_and_convert_node<identifier_or_template_id, id_t::IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

nested_name_specifier::last_part
convert_nested_name_specifier_last_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NESTED_NAME_SPECIFIER_LAST_PART);

    return nested_name_specifier::last_part
    (
		check_node_existence(node, "template", 0),
		find_and_convert_node<identifier_or_template_id, id_t::IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

nested_name_specifier
convert_nested_name_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NESTED_NAME_SPECIFIER);

	tree_node_iterator_t identifier_or_template_id_it = find_node<id_t::IDENTIFIER_OR_TEMPLATE_ID>(node);
	tree_node_iterator_t last_part_seq_it = find_node<id_t::NESTED_NAME_SPECIFIER_LAST_PART_SEQ>(node);

    return nested_name_specifier
    (
        convert_node<identifier_or_template_id>(*identifier_or_template_id_it),
		convert_next_space(node, identifier_or_template_id_it),
		convert_previous_space(node, last_part_seq_it),
        convert_optional<nested_name_specifier::last_part_seq>(node, last_part_seq_it)
    );
}

new_array_operator
convert_new_array_operator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_ARRAY_OPERATOR);

	return new_array_operator();
}

new_placement
convert_new_placement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_PLACEMENT);

	return new_placement();
}

new_type_id_new_expression
convert_new_type_id_new_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_TYPE_ID_NEW_EXPRESSION);

	tree_node_iterator_t leading_double_colon_it = find_node(node, "::");
	tree_node_iterator_t new_keyword_it = find_node(node, "new");
	tree_node_iterator_t new_placement_it = find_node<id_t::NEW_PLACEMENT>(node);
	tree_node_iterator_t new_type_id_it = find_node<id_t::NEW_TYPE_ID>(node);
	tree_node_iterator_t new_initializer_it = find_node<id_t::NEW_INITIALIZER>(node);

	return new_type_id_new_expression
	(
		leading_double_colon_it != node.children.end(),
		convert_next_space(node, leading_double_colon_it),
		convert_next_space(node, new_keyword_it),
		convert_optional<new_placement>(node, new_placement_it),
		convert_next_space(node, new_placement_it),
		convert_node<new_type_id>(*new_type_id_it),
		convert_previous_space(node, new_initializer_it),
		convert_optional<new_initializer>(node, new_initializer_it)
	);
}

parameter_declaration
convert_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::PARAMETER_DECLARATION);

	tree_node_iterator_t declarator_it = find_node<id_t::DECLARATOR>(node);

    return parameter_declaration
    (
		find_and_convert_node
		<
			decl_specifier_seq,
			id_t::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ1,
			id_t::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ2,
			id_t::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ3,
			id_t::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ4,
			id_t::DECL_SPECIFIER_SEQ
		>(node),
		convert_previous_space(node, declarator_it),
		convert_optional<declarator>(node, declarator_it),
		false
    );
}

ptr_operator
convert_ptr_operator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::PTR_OPERATOR);

    #ifndef NDEBUG
    bool asterisk = check_node_existence(node, "*");
    bool ampersand = check_node_existence(node, "&", 0);
    assert
    (
        (asterisk && !ampersand) ||
        (!asterisk && ampersand)
    );
    #endif

	tree_node_iterator_t leading_double_colon_it = find_node(node, "::");
	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t cv_qualifier_seq_it = find_node<id_t::CV_QUALIFIER_SEQ>(node);

	return ptr_operator
	(
		check_node_existence(node, "*") ? ptr_operator::ASTERISK : ptr_operator::AMPERSAND,
		leading_double_colon_it != node.children.end(),
		convert_next_space(node, leading_double_colon_it),
		convert_optional<nested_name_specifier>(node, nested_name_specifier_it),
		convert_next_space(node, nested_name_specifier_it),
		convert_previous_space(node, cv_qualifier_seq_it),
		convert_optional<cv_qualifier_seq>(node, cv_qualifier_seq_it)
	);
}

qualified_operator_function_id
convert_qualified_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_OPERATOR_FUNCTION_ID);

    return qualified_operator_function_id
    (
        //find_and_convert_node<operator_function_id, id_t::OPERATOR_FUNCTION_ID>(node)
    );
}

qualified_template_id
convert_qualified_template_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_TEMPLATE_ID);

    return qualified_template_id
    (
        find_and_convert_node<template_id, id_t::TEMPLATE_ID>(node)
    );
}

simple_declaration
convert_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SIMPLE_DECLARATION);

	tree_node_iterator_t decl_specifier_seq_it = find_node<id_t::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ>(node);
	tree_node_iterator_t init_declarator_list_it = find_node<id_t::INIT_DECLARATOR_LIST>(node);

    return simple_declaration
    (
		convert_optional<decl_specifier_seq>(node, decl_specifier_seq_it),
		convert_next_space(node, decl_specifier_seq_it),
		convert_optional<init_declarator_list>(node, init_declarator_list_it),
		convert_next_space(node, init_declarator_list_it)
    );
}

simple_template_type_specifier
convert_simple_template_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SIMPLE_TEMPLATE_TYPE_SPECIFIER);

    return simple_template_type_specifier
	(
		check_node_existence(node, "::", 0),
		find_and_convert_node<nested_name_specifier, id_t::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<template_id, id_t::TEMPLATE_ID>(node)
	);
}

simple_type_specifier_postfix_expression
convert_simple_type_specifier_postfix_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::SIMPLE_TYPE_SPECIFIER_POSTFIX_EXPRESSION);

	return simple_type_specifier_postfix_expression();
}

space
convert_space(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SPACE);

	return space(get_only_child_value(node));
}

string_literal
convert_string_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::STRING_LITERAL);

	bool wide = false;

	tree_node_iterator_t i = node.children.begin();
	if(get_value(*i) == "L")
	{
		wide = true;
		++i;
	}

	++i; //iterate to string value

	return string_literal
	(
		wide,
		get_value(*i)
	);
}

switch_statement
convert_switch_statement(const tree_node_t& node)
{
	assert(node.value.id() == id_t::SWITCH_STATEMENT);

	tree_node_iterator_t switch_keyword_it = node.children.begin();
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t condition_it = find_node<id_t::CONDITION>(node);
	tree_node_iterator_t closing_bracket_it = find_node(node, ")");

	return switch_statement
	(
		convert_next_space(node, switch_keyword_it),
		convert_next_space(node, opening_bracket_it),
		convert_node<condition>(*condition_it),
		convert_next_space(node, condition_it),
		convert_next_space(node, closing_bracket_it),
		find_and_convert_node<statement, id_t::STATEMENT>(node)
	);
}

template_declaration
convert_template_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TEMPLATE_DECLARATION);

    return template_declaration
    (
        check_node_existence(node, "export", 0),
        find_and_convert_node<declaration, id_t::DECLARATION>(node)
    );
}

template_id
convert_template_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TEMPLATE_ID);

	tree_node_iterator_t type_name_it = node.children.begin();
	tree_node_iterator_t opening_angle_bracket_it = find_node(node, "<");
	tree_node_iterator_t template_argument_list_it = find_node<id_t::TEMPLATE_ARGUMENT_LIST>(node);

    return template_id
    (
        convert_node<identifier>(*type_name_it),
		convert_next_space(node, type_name_it),
		convert_next_space(node, opening_angle_bracket_it),
        convert_optional<template_argument_list>(node, template_argument_list_it),
		convert_next_space(node, template_argument_list_it)
    );
}

template_typename_expression
convert_template_typename_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TEMPLATE_TYPENAME_EXPRESSION);

	return template_typename_expression();
}

throw_expression
convert_throw_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::THROW_EXPRESSION);

	tree_node_iterator_t assignment_expression_it = find_node<id_t::ASSIGNMENT_EXPRESSION>(node);

	return throw_expression
	(
		convert_previous_space(node, assignment_expression_it),
		convert_optional<assignment_expression>(node, assignment_expression_it)
	);
}

translation_unit
convert_translation_unit(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TRANSLATION_UNIT);

	optional_node<space> first_space_node;
	optional_node<declaration_seq> declaration_seq_node;
	optional_node<space> post_declaration_seq_node;

	tree_node_iterator_t i = node.children.begin();
	if(i->value.id() == id_t::SPACE)
		first_space_node = convert_node<space>(*i);

	i = find_node<id_t::DECLARATION_SEQ>(node);
	if(i != node.children.end())
	{
		declaration_seq_node = convert_node<declaration_seq>(*i);
		post_declaration_seq_node = convert_next_space(node, i);
	}

	return translation_unit
	(
		first_space_node,
		declaration_seq_node,
		post_declaration_seq_node
	);
}

try_block
convert_try_block(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TRY_BLOCK);

	tree_node_iterator_t try_keyword_it = node.children.begin();
	tree_node_iterator_t compound_statement_it = find_node<id_t::COMPOUND_STATEMENT>(node);
	tree_node_iterator_t handler_seq_it = find_node<id_t::HANDLER_SEQ>(node);

	handler_seq handler_seq_node;
	if(handler_seq_it != node.children.end())
		handler_seq_node = convert_node<handler_seq>(*handler_seq_it);

	return try_block
	(
		convert_next_space(node, try_keyword_it),
		convert_node<compound_statement>(*compound_statement_it),
		convert_next_space(node, compound_statement_it),
		handler_seq_node
	);
}

type_id
convert_type_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TYPE_ID);

	tree_node_iterator_t type_specifier_seq_it = node.children.begin();
	tree_node_iterator_t abstract_declarator_it = find_node<id_t::ABSTRACT_DECLARATOR>(node);

	return type_id
	(
		convert_node<type_specifier_seq>(*type_specifier_seq_it),
		convert_previous_space(node, abstract_declarator_it),
		convert_optional<abstract_declarator>(node, abstract_declarator_it)
	);
}

type_id_sizeof_expression
convert_type_id_sizeof_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TYPE_ID_SIZEOF_EXPRESSION);

	return type_id_sizeof_expression();
}

type_id_typeid_expression
convert_type_id_typeid_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TYPE_ID_TYPEID_EXPRESSION);

	return type_id_typeid_expression();
}

typeid_expression
convert_typeid_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TYPEID_EXPRESSION);

	return typeid_expression();
}

typeof_expression
convert_typeof_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TYPEOF_EXPRESSION);

	return typeof_expression();
}

typename_elaborated_specifier
convert_typename_elaborated_specifier(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TYPENAME_ELABORATED_SPECIFIER);

	return typename_elaborated_specifier();
}

typename_expression
convert_typename_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TYPENAME_EXPRESSION);

	return typename_expression();
}

typename_template_elaborated_specifier
convert_typename_template_elaborated_specifier(const tree_node_t& node)
{
	assert(node.value.id() == id_t::TYPENAME_TEMPLATE_ELABORATED_SPECIFIER);

	return typename_template_elaborated_specifier();
}

unary_operator_unary_expression
convert_unary_operator_unary_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::UNARY_OPERATOR_UNARY_EXPRESSION);

	tree_node_iterator_t unary_operator_it = find_node<id_t::UNARY_OPERATOR>(node);
	tree_node_iterator_t cast_expression_it = find_node<id_t::CAST_EXPRESSION>(node);

	return unary_operator_unary_expression
	(
		convert_node<unary_operator>(*unary_operator_it),
		convert_next_space(node, unary_operator_it),
		convert_node<cast_expression>(*cast_expression_it)
	);
}

unary_sizeof_expression
convert_unary_sizeof_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::UNARY_SIZEOF_EXPRESSION);

	return unary_sizeof_expression();
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis

