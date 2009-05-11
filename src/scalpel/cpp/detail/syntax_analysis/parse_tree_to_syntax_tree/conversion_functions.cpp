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
#include "../../../syntax_tree.hpp"
#include "../grammar.hpp"
#include "basic_functions.hpp"
#include "special_conversion_functions.hpp"
#include "node_finder_and_converter.hpp"
#include "space_conversion_functions.hpp"

using namespace scalpel::cpp::syntax_nodes;

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

abstract_declarator
convert_abstract_declarator(const tree_node_t& node)
{
	assert(node.value.id() == id_t::ABSTRACT_DECLARATOR);

	return convert_alternative
	<
		abstract_declarator,
		id_t::PTR_OPERATOR_SEQ,
		id_t::DIRECT_ABSTRACT_DECLARATOR
	>(node);
}

array_delete_expression
convert_array_delete_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::ARRAY_DELETE_EXPRESSION);

	tree_node_iterator_t double_colon_it = find_node(node, "::");
	tree_node_iterator_t delete_keyword_it = find_node(node, "delete");
	tree_node_iterator_t opening_bracket_it = find_node(node, "[");
	tree_node_iterator_t closing_bracket_it = find_node(node, "]");

	return array_delete_expression
	(
		double_colon_it != node.children.end(),
		convert_next_space(node, double_colon_it),
		convert_next_space(node, delete_keyword_it),
		convert_next_space(node, opening_bracket_it),
		convert_next_space(node, closing_bracket_it),
		find_and_convert_node<cast_expression, id_t::CAST_EXPRESSION>(node)
	);
}

array_operator
convert_array_operator(const tree_node_t& node)
{
	assert(node.value.id() == id_t::ARRAY_OPERATOR);

	return convert_alternative
	<
		array_operator,
		id_t::NEW_ARRAY_OPERATOR,
		id_t::DELETE_ARRAY_OPERATOR
	>(node);
}

arrow_id_expression
convert_arrow_id_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::ARROW_ID_EXPRESSION);

	tree_node_iterator_t arrow_it = node.children.begin();
	tree_node_iterator_t template_keyword_it = find_node(node, "template");

	return arrow_id_expression
	(
		convert_next_space(node, arrow_it),
		template_keyword_it != node.children.end(),
		convert_next_space(node, template_keyword_it),
		find_and_convert_node<id_expression, id_t::ID_EXPRESSION>(node)
	);
}

arrow_pseudo_destructor_name
convert_arrow_pseudo_destructor_name(const tree_node_t& node)
{
	assert(node.value.id() == id_t::ARROW_PSEUDO_DESTRUCTOR_NAME);

	return arrow_pseudo_destructor_name();
}

assignment_expression::first_part
convert_assignment_expression_first_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ASSIGNMENT_EXPRESSION_FIRST_PART);

	return assignment_expression::first_part
	(
		find_and_convert_node<logical_or_expression, id_t::LOGICAL_OR_EXPRESSION>(node),
		find_and_convert_node<boost::optional<space>, id_t::SPACE>(node),
		find_and_convert_node<assignment_operator, id_t::ASSIGNMENT_OPERATOR>(node)
	);
}

assignment_expression
convert_assignment_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ASSIGNMENT_EXPRESSION);

	tree_node_iterator_t first_part_seq_it = find_node<id_t::ASSIGNMENT_EXPRESSION_FIRST_PART_SEQ>(node);
	tree_node_iterator_t conditional_expression_it = find_node<id_t::CONDITIONAL_EXPRESSION>(node);
	tree_node_iterator_t throw_expression_it = find_node<id_t::THROW_EXPRESSION>(node);

	if(conditional_expression_it != node.children.end())
	{
		return assignment_expression
		(
			convert_optional<assignment_expression::first_part_seq>(node, first_part_seq_it),
			convert_next_space(node, first_part_seq_it),
			convert_node<conditional_expression>(*conditional_expression_it)
		);
	}
	else if(throw_expression_it != node.children.end())
	{
		return assignment_expression
		(
			convert_optional<assignment_expression::first_part_seq>(node, first_part_seq_it),
			convert_next_space(node, first_part_seq_it),
			convert_node<throw_expression>(*throw_expression_it)
		);
	}
	else
	{
		assert(false);
	}
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

base_clause
convert_base_clause(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BASE_CLAUSE);

	tree_node_iterator_t i = find_node<id_t::BASE_SPECIFIER_LIST>(node);
	boost::optional<base_specifier_list> base_specifier_list_node;
	boost::optional<space> space_node;
	if(i != node.children.end())
	{
		base_specifier_list_node = convert_node<base_specifier_list>(*i);
		space_node = convert_previous_space(node, i);
	}

    //unlike what grammar defines, base specifier may be missing
    return base_clause
    (
		space_node,
		base_specifier_list_node ? *base_specifier_list_node : base_specifier_list()
    );
}

base_specifier
convert_base_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BASE_SPECIFIER);

	tree_node_iterator_t virtual_keyword_it = find_node(node, "virtual");
	tree_node_iterator_t access_specifier_node_it = find_child_node(node, id_t::ACCESS_SPECIFIER);

	return base_specifier
	(
		virtual_keyword_it != node.children.end(),
		check_node_existence(node, "virtual", 0),
		convert_next_space(node, virtual_keyword_it),
		convert_optional<access_specifier>(node, access_specifier_node_it),
		convert_next_space(node, access_specifier_node_it),
		find_and_convert_node<boost::optional<nested_identifier_or_template_id>, id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID>(node)
	);
}

block_declaration
convert_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BLOCK_DECLARATION);

	return convert_alternative
	<
		block_declaration,
		//id_t::ASM_DEFINITION,
		id_t::SIMPLE_DECLARATION,
		//id_t::NAMESPACE_ALIAS_DEFINITION,
		id_t::USING_DECLARATION,
		id_t::USING_DIRECTIVE
	>(node);
}

boolean_literal
convert_boolean_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BOOLEAN_LITERAL);

	return boolean_literal
	(
		get_only_child_value(node) == "true"
	);
}

bracketed_declarator
convert_bracketed_declarator(const tree_node_t& node)
{
	assert(node.value.id() == id_t::BRACKETED_DECLARATOR);

	tree_node_iterator_t opening_bracket_it = node.children.begin();
	tree_node_iterator_t declarator_it = find_node<id_t::DECLARATOR>(node);

	return bracketed_declarator
	(
		convert_next_space(node, opening_bracket_it),
		convert_node<declarator>(*declarator_it),
		convert_next_space(node, declarator_it)
	);
}

bracketed_expression_list
convert_bracketed_expression_list(const tree_node_t& node)
{
	assert(node.value.id() == id_t::BRACKETED_EXPRESSION_LIST);

	tree_node_iterator_t opening_bracket_it = node.children.begin();
	tree_node_iterator_t expression_list_it = find_node<id_t::EXPRESSION_LIST>(node);

	return bracketed_expression_list
	(
		convert_next_space(node, opening_bracket_it),
		convert_optional<expression_list>(node, expression_list_it),
		convert_next_space(node, expression_list_it)
	);
}

bracketed_initializer
convert_bracketed_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BRACKETED_INITIALIZER);

	tree_node_iterator_t opening_bracket_it = node.children.begin();
	tree_node_iterator_t expression_list_it = find_node<id_t::EXPRESSION_LIST>(node);

	return bracketed_initializer
	(
		convert_next_space(node, opening_bracket_it),
		convert_node<expression_list>(*expression_list_it),
		convert_next_space(node, expression_list_it)
	);
}

break_statement
convert_break_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BREAK_STATEMENT);

	return break_statement
	(
		find_and_convert_node<boost::optional<space>, id_t::SPACE>(node)
	);
}

case_statement
convert_case_statement(const tree_node_t& node)
{
	assert(node.value.id() == id_t::CASE_STATEMENT);

	tree_node_iterator_t case_keyword_it = node.children.begin();
	tree_node_iterator_t conditional_expression_it = find_node<id_t::CONDITIONAL_EXPRESSION>(node);
	tree_node_iterator_t colon_it = find_node(node, ":");

	return case_statement
	(
		convert_next_space(node, case_keyword_it),
		convert_node<conditional_expression>(*conditional_expression_it),
		convert_next_space(node, conditional_expression_it),
		convert_next_space(node, colon_it),
		find_and_convert_node<statement, id_t::STATEMENT>(node)
	);
}

cast_expression
convert_cast_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CAST_EXPRESSION);

	return cast_expression
	(
		find_and_convert_node<unary_expression, id_t::UNARY_EXPRESSION>(node)
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

class_elaborated_specifier
convert_class_elaborated_specifier(const tree_node_t& node)
{
	assert(node.value.id() == id_t::CLASS_ELABORATED_SPECIFIER);

	tree_node_iterator_t class_key_it = node.children.begin();
	tree_node_iterator_t double_colon_it = find_node(node, "::");
	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t identifier_it = find_node<id_t::IDENTIFIER>(node);

	return class_elaborated_specifier
	(
		convert_node<class_key>(*class_key_it),
		convert_next_space(node, class_key_it),
		double_colon_it != node.children.end(),
		convert_next_space(node, double_colon_it),
		convert_optional<nested_name_specifier>(node, nested_name_specifier_it),
		convert_next_space(node, nested_name_specifier_it),
		convert_node<identifier>(*identifier_it)
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

class_specifier
convert_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CLASS_SPECIFIER);

	boost::optional<member_specification> member_specification_node;

	tree_node_iterator_t class_head_it = node.children.begin();

	tree_node_iterator_t opening_brace_it = class_head_it;
	++opening_brace_it;
	if(opening_brace_it->value.id() == id_t::SPACE)
		++opening_brace_it;

	tree_node_iterator_t member_specification_it = find_node<id_t::MEMBER_SPECIFICATION>(node);
	if(member_specification_it != node.children.end())
		member_specification_node = convert_node<member_specification>(*member_specification_it);

    return class_specifier
    (
        find_and_convert_node<class_head, id_t::CLASS_HEAD>(node),
		convert_next_space(node, class_head_it),
		convert_next_space(node, opening_brace_it),
		member_specification_node,
		convert_next_space(node, member_specification_it)
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

classic_labeled_statement
convert_classic_labeled_statement(const tree_node_t& node)
{
	assert(node.value.id() == id_t::CLASSIC_LABELED_STATEMENT);

	return classic_labeled_statement();
}

compound_statement
convert_compound_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::COMPOUND_STATEMENT);

	tree_node_iterator_t opening_brace_it = node.children.begin();
	tree_node_iterator_t statement_seq_it = find_node<id_t::STATEMENT_SEQ>(node);

	return compound_statement
	(
		convert_next_space(node, opening_brace_it),
		convert_optional<statement_seq>(node, statement_seq_it),
		convert_next_space(node, statement_seq_it)
	);
}

condition
convert_condition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CONDITION);

	return convert_alternative
	<
		condition,
		id_t::EXPRESSION,
		id_t::ASSIGNMENT_EXPRESSION_CONDITION
	>(node);
}

conditional_expression
convert_conditional_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CONDITIONAL_EXPRESSION);

	return conditional_expression
	(
		find_and_convert_node<logical_or_expression, id_t::LOGICAL_OR_EXPRESSION>(node)
	);
}

const_cast_expression
convert_const_cast_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::CONST_CAST_EXPRESSION);

	return const_cast_expression();
}

continue_statement
convert_continue_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CONTINUE_STATEMENT);

	return continue_statement
	(
		find_and_convert_node<boost::optional<space>, id_t::SPACE>(node)
	);
}

conversion_function_id
convert_conversion_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CONVERSION_FUNCTION_ID);

	tree_node_iterator_t operator_keyword_it = node.children.begin();
	tree_node_iterator_t type_specifier_seq_it = find_node<id_t::TYPE_SPECIFIER_SEQ>(node);
	tree_node_iterator_t ptr_operator_seq_it = find_node<id_t::PTR_OPERATOR_SEQ>(node);

	return conversion_function_id
	(
		convert_next_space(node, operator_keyword_it),
		convert_node<type_specifier_seq>(*type_specifier_seq_it),
		convert_previous_space(node, ptr_operator_seq_it),
		convert_optional<ptr_operator_seq>(node, ptr_operator_seq_it)
	);
}

ctor_initializer
convert_ctor_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CTOR_INITIALIZER);

	tree_node_iterator_t mem_initializer_list_it = find_node<id_t::MEM_INITIALIZER_LIST>(node);

    return ctor_initializer
    (
		convert_previous_space(node, mem_initializer_list_it),
		convert_node<mem_initializer_list>(*mem_initializer_list_it)
    );
}

cv_qualifier
convert_cv_qualifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CV_QUALIFIER);

    const tree_node_t& child_node = *node.children.begin();
    const boost::spirit::parser_id child_id = child_node.value.id();
    if(child_id == id_t::RESTRICT_KEYWORD)
	{
		const std::string child_value = get_only_child_value(child_node);
        return cv_qualifier(child_value);
	}
    else
	{
		const std::string value = get_only_child_value(node);
		return cv_qualifier(value);
	}
}

decl_specifier
convert_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECL_SPECIFIER);

	return convert_alternative
	<
		decl_specifier,
		id_t::STORAGE_CLASS_SPECIFIER,
		id_t::TYPE_SPECIFIER,
		id_t::FUNCTION_SPECIFIER
	>(node);
}

declaration
convert_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECLARATION);

	return convert_alternative
	<
		declaration,
		id_t::BLOCK_DECLARATION,
		id_t::FUNCTION_DEFINITION,
		id_t::TEMPLATE_DECLARATION,
//            id_t::EXPLICIT_INSTANTIATION,
//            id_t::EXPLICIT_SPECIALIZATION,
//            id_t::LINKAGE_SPECIFICATION,
		id_t::NAMESPACE_DEFINITION
	>(node);
}

declarator
convert_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECLARATOR);

	tree_node_iterator_t ptr_operator_seq_it = find_node<id_t::PTR_OPERATOR_SEQ>(node);

    return declarator
    (
		convert_optional<ptr_operator_seq>(node, ptr_operator_seq_it),
		convert_next_space(node, ptr_operator_seq_it),
		find_and_convert_node<direct_declarator, id_t::DIRECT_DECLARATOR>(node)
	);
}

declarator_id
convert_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECLARATOR_ID);

	return convert_alternative
	<
		declarator_id,
		id_t::ID_EXPRESSION,
		id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID
	>(node);
}

default_statement
convert_default_statement(const tree_node_t& node)
{
	assert(node.value.id() == id_t::DEFAULT_STATEMENT);

	tree_node_iterator_t default_keyword_it = node.children.begin();
	tree_node_iterator_t colon_it = find_node(node, ":");

	return default_statement
	(
		convert_next_space(node, default_keyword_it),
		convert_next_space(node, colon_it),
		find_and_convert_node<statement, id_t::STATEMENT>(node)
	);
}

delete_array_operator
convert_delete_array_operator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DELETE_ARRAY_OPERATOR);

	return delete_array_operator();
}

delete_expression
convert_delete_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DELETE_EXPRESSION);

	return convert_alternative
	<
		delete_expression,
		id_t::SIMPLE_DELETE_EXPRESSION,
		id_t::ARRAY_DELETE_EXPRESSION
	>(node);
}

destructor_name
convert_destructor_name(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DESTRUCTOR_NAME);

	tree_node_iterator_t identifier_or_template_id_it = find_node<id_t::IDENTIFIER_OR_TEMPLATE_ID>(node);

	return destructor_name
	(
		convert_previous_space(node, identifier_or_template_id_it),
		convert_node<identifier_or_template_id>(*identifier_or_template_id_it)
	);
}

direct_abstract_declarator
convert_direct_abstract_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_ABSTRACT_DECLARATOR);

	return direct_abstract_declarator();
}

direct_declarator::array_part
convert_direct_declarator_array_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR_ARRAY_PART);

    return direct_declarator::array_part();
}

direct_declarator::first_part
convert_direct_declarator_first_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR_FIRST_PART);

	return convert_alternative
	<
		direct_declarator::first_part,
		id_t::BRACKETED_DECLARATOR,
		id_t::DECLARATOR_ID
	>(node);
}

direct_declarator::function_part
convert_direct_declarator_function_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR_FUNCTION_PART);

	tree_node_iterator_t opening_bracket_it = node.children.begin();
	tree_node_iterator_t parameter_declaration_clause_it = find_node<id_t::PARAMETER_DECLARATION_CLAUSE>(node);
	tree_node_iterator_t cv_qualifier_seq_it = find_node<id_t::CV_QUALIFIER_SEQ>(node);
	tree_node_iterator_t exception_specification_it = find_node<id_t::EXCEPTION_SPECIFICATION>(node);

    return direct_declarator::function_part
    (
		convert_next_space(node, opening_bracket_it),
		convert_optional<parameter_declaration_clause>(node, parameter_declaration_clause_it),
		convert_next_space(node, parameter_declaration_clause_it),
		convert_previous_space(node, cv_qualifier_seq_it),
		convert_optional<cv_qualifier_seq>(node, cv_qualifier_seq_it),
		convert_previous_space(node, exception_specification_it),
		convert_optional<exception_specification>(node, exception_specification_it)
    );
}

direct_declarator::last_part
convert_direct_declarator_last_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR_LAST_PART);

	return convert_alternative
	<
		direct_declarator::last_part,
		id_t::DIRECT_DECLARATOR_FUNCTION_PART,
		id_t::DIRECT_DECLARATOR_ARRAY_PART
	>(node);
}

direct_declarator
convert_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR);

	tree_node_iterator_t last_part_seq_it = find_node<id_t::DIRECT_DECLARATOR_LAST_PART_SEQ>(node);

    return direct_declarator
    (
		find_and_convert_node<direct_declarator::first_part, id_t::DIRECT_DECLARATOR_FIRST_PART>(node),
		convert_previous_space(node, last_part_seq_it),
		convert_optional<sequence_node<direct_declarator::last_part>>(node, last_part_seq_it)
    );
}

do_while_statement
convert_do_while_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DO_WHILE_STATEMENT);

	return do_while_statement();
}

dot_id_expression
convert_dot_id_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::DOT_ID_EXPRESSION);

	tree_node_iterator_t dot_it = node.children.begin();
	tree_node_iterator_t template_keyword_it = find_node(node, "template");

	return dot_id_expression
	(
		convert_next_space(node, dot_it),
		template_keyword_it != node.children.end(),
		convert_next_space(node, template_keyword_it),
		find_and_convert_node<id_expression, id_t::ID_EXPRESSION>(node)
	);
}

dot_pseudo_destructor_name
convert_dot_pseudo_destructor_name(const tree_node_t& node)
{
	assert(node.value.id() == id_t::DOT_PSEUDO_DESTRUCTOR_NAME);

	return dot_pseudo_destructor_name();
}

dynamic_cast_expression
convert_dynamic_cast_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::DYNAMIC_CAST_EXPRESSION);

	return dynamic_cast_expression();
}

elaborated_type_specifier
convert_elaborated_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ELABORATED_TYPE_SPECIFIER);

	return convert_alternative
	<
		elaborated_type_specifier,
		id_t::CLASS_TEMPLATE_ELABORATED_SPECIFIER,
		id_t::CLASS_ELABORATED_SPECIFIER,
		id_t::ENUM_ELABORATED_SPECIFIER,
		id_t::TYPENAME_TEMPLATE_ELABORATED_SPECIFIER,
		id_t::TYPENAME_ELABORATED_SPECIFIER
	>(node);
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

equal_initializer
convert_equal_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EQUAL_INITIALIZER);

	tree_node_iterator_t i = find_node<id_t::INITIALIZER_CLAUSE>(node);

	return equal_initializer
	(
		convert_previous_space(node, i),
		convert_node<initializer_clause>(*i)
	);
}

exception_abstract_declarator
convert_exception_abstract_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EXCEPTION_ABSTRACT_DECLARATOR);

	tree_node_iterator_t type_specifier_seq_it = node.children.begin();
	tree_node_iterator_t abstract_declarator_it = node.children.end();
	--abstract_declarator_it;

	return exception_abstract_declarator
	(
		convert_node<type_specifier_seq>(*type_specifier_seq_it),
		convert_next_space(node, type_specifier_seq_it),
		convert_node<abstract_declarator>(*abstract_declarator_it)
	);
}

exception_declaration
convert_exception_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EXCEPTION_DECLARATION);

	return convert_alternative
	<
		exception_declaration,
		id_t::EXCEPTION_DECLARATOR,
		id_t::EXCEPTION_ABSTRACT_DECLARATOR,
		id_t::TYPE_SPECIFIER_SEQ,
		id_t::ELLIPSIS
	>(node);
}

exception_declarator
convert_exception_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EXCEPTION_DECLARATOR);

	tree_node_iterator_t type_specifier_seq_it = node.children.begin();
	tree_node_iterator_t declarator_it = node.children.end();
	--declarator_it;

	return exception_declarator
	(
		convert_node<type_specifier_seq>(*type_specifier_seq_it),
		convert_next_space(node, type_specifier_seq_it),
		convert_node<declarator>(*declarator_it)
	);
}

exception_specification
convert_exception_specification(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EXCEPTION_SPECIFICATION);

	tree_node_iterator_t throw_keyword_it = node.children.begin();
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t type_id_list_it = find_node<id_t::TYPE_ID_LIST>(node);

	return exception_specification
	(
		convert_next_space(node, throw_keyword_it),
		convert_next_space(node, opening_bracket_it),
		convert_optional<type_id_list>(node, type_id_list_it),
		convert_next_space(node, type_id_list_it)
	);
}

expression_statement
convert_expression_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::EXPRESSION_STATEMENT);

	tree_node_iterator_t expression_it = find_node<id_t::EXPRESSION>(node);

	return expression_statement
	(
		convert_optional<expression>(node, expression_it),
		convert_next_space(node, expression_it)
	);
}

floating_literal
convert_floating_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FLOATING_LITERAL);

	return floating_literal(get_only_child_value(node));
}

for_init_statement
convert_for_init_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FOR_INIT_STATEMENT);

	return convert_alternative
	<
		for_init_statement,
		id_t::EXPRESSION_STATEMENT,
		id_t::SIMPLE_DECLARATION
	>(node);
}

for_statement
convert_for_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FOR_STATEMENT);

	tree_node_iterator_t for_keyword_it = node.children.begin();
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t for_init_statement_it = find_node<id_t::FOR_INIT_STATEMENT>(node);
	tree_node_iterator_t condition_it = find_node<id_t::CONDITION>(node);
	tree_node_iterator_t semicolon_it = find_node(node, ";");
	tree_node_iterator_t expression_it = find_node<id_t::EXPRESSION>(node);
	tree_node_iterator_t closing_bracket_it = find_node(node, ")");

	return for_statement
	(
		convert_next_space(node, for_keyword_it),
		convert_next_space(node, opening_bracket_it),
		convert_optional<for_init_statement>(node, for_init_statement_it),
		convert_next_space(node, for_init_statement_it),
		convert_optional<condition>(node, condition_it),
		convert_next_space(node, condition_it),
		convert_next_space(node, semicolon_it),
		convert_optional<expression>(node, expression_it),
		convert_next_space(node, expression_it),
		convert_next_space(node, closing_bracket_it),
		find_and_convert_node<statement, id_t::STATEMENT>(node)
	);
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

goto_statement
convert_goto_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::GOTO_STATEMENT);

	tree_node_iterator_t goto_keyword_it = node.children.begin();
	tree_node_iterator_t identifier_it = find_node<id_t::IDENTIFIER>(node);

	return goto_statement
	(
		convert_next_space(node, goto_keyword_it),
		convert_node<identifier>(*identifier_it),
		convert_next_space(node, identifier_it)
	);
}

handler
convert_handler(const tree_node_t& node)
{
    assert(node.value.id() == id_t::HANDLER);

	tree_node_iterator_t catch_keyword_it = node.children.begin();
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t exception_declaration_it = find_node<id_t::EXCEPTION_DECLARATION>(node);
	tree_node_iterator_t closing_bracket_it = find_node(node, ")");
	tree_node_iterator_t compound_statement_it = find_node<id_t::COMPOUND_STATEMENT>(node);

	return handler
	(
		convert_next_space(node, catch_keyword_it),
		convert_next_space(node, opening_bracket_it),
		convert_node<exception_declaration>(*exception_declaration_it),
		convert_next_space(node, exception_declaration_it),
		convert_next_space(node, closing_bracket_it),
		convert_node<compound_statement>(*compound_statement_it)
	);
}

id_expression
convert_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ID_EXPRESSION);

	return convert_alternative
	<
		id_expression,
		id_t::UNQUALIFIED_ID,
	   	id_t::QUALIFIED_ID
	>(node);
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

identifier_or_template_id
convert_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::IDENTIFIER_OR_TEMPLATE_ID);

	return convert_alternative
	<
		identifier_or_template_id,
		id_t::IDENTIFIER,
		id_t::TEMPLATE_ID
	>(node);
}

if_statement
convert_if_statement(const tree_node_t& node)
{
	assert(node.value.id() == id_t::IF_STATEMENT);

	tree_node_iterator_t if_keyword_it = node.children.begin();
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t condition_it = find_node<id_t::CONDITION>(node);
	tree_node_iterator_t closing_bracket_it = find_node(node, ")");
	tree_node_iterator_t else_keyword_it = find_node(node, "else");
	tree_node_iterator_t else_statement_it = node.children.end();

	if(else_keyword_it != node.children.end())
		--else_statement_it;

	return if_statement
	(
		convert_next_space(node, if_keyword_it),
		convert_next_space(node, opening_bracket_it),
		convert_node<condition>(*condition_it),
		convert_next_space(node, condition_it),
		convert_next_space(node, closing_bracket_it),
		find_and_convert_node<statement, id_t::STATEMENT>(node),
		convert_previous_space(node, else_keyword_it),
		convert_optional<statement>(node, else_statement_it),
		convert_next_space(node, else_keyword_it)
	);
}

init_declarator
convert_init_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::INIT_DECLARATOR);

	tree_node_iterator_t initializer_it = find_node<id_t::INITIALIZER>(node);

    return init_declarator
    (
		find_and_convert_node<declarator, id_t::DECLARATOR>(node),
		convert_previous_space(node, initializer_it),
		convert_optional<initializer>(node, initializer_it)
    );
}

initializer
convert_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::INITIALIZER);

	return convert_alternative
	<
		initializer,
		id_t::EQUAL_INITIALIZER,
		id_t::BRACKETED_INITIALIZER
	>(node);
}

initializer_clause
convert_initializer_clause(const tree_node_t& node)
{
    assert(node.value.id() == id_t::INITIALIZER_CLAUSE);

	return convert_alternative
	<
		initializer_clause,
		id_t::ASSIGNMENT_EXPRESSION,
		id_t::INITIALIZER_LIST_INITIALIZER_CLAUSE,
		id_t::EMPTY_INITIALIZER_LIST_INITIALIZER_CLAUSE
	>(node);
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

iteration_statement
convert_iteration_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ITERATION_STATEMENT);

	return convert_alternative
	<
		iteration_statement,
		id_t::WHILE_STATEMENT,
		id_t::DO_WHILE_STATEMENT,
		id_t::FOR_STATEMENT
	>(node);
}

jump_statement
convert_jump_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::JUMP_STATEMENT);

	return convert_alternative
	<
		jump_statement,
		id_t::BREAK_STATEMENT,
		id_t::CONTINUE_STATEMENT,
		id_t::RETURN_STATEMENT,
		id_t::GOTO_STATEMENT
	>(node);
}

labeled_statement
convert_labeled_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::LABELED_STATEMENT);

	return convert_alternative
	<
		labeled_statement,
		id_t::CASE_STATEMENT,
		id_t::DEFAULT_STATEMENT,
		id_t::CLASSIC_LABELED_STATEMENT
	>(node);
}

literal
convert_literal(const tree_node_t& node)
{
    assert(node.value.id() == id_t::LITERAL);

	return convert_alternative
	<
		literal,
		id_t::BOOLEAN_LITERAL,
		id_t::CHARACTER_LITERAL,
		id_t::INTEGER_LITERAL,
		id_t::FLOATING_LITERAL,
		id_t::STRING_LITERAL
	>(node);
}

mem_initializer
convert_mem_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEM_INITIALIZER);

	tree_node_iterator_t mem_initializer_id_it = node.children.begin();
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t expression_list_it = find_node<id_t::EXPRESSION_LIST>(node);

    return mem_initializer
    (
		convert_node<mem_initializer_id>(*mem_initializer_id_it),
		convert_next_space(node, mem_initializer_id_it),
		convert_next_space(node, opening_bracket_it),
		convert_optional<expression_list>(node, expression_list_it),
		convert_next_space(node, expression_list_it)
    );
}

mem_initializer_id
convert_mem_initializer_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEM_INITIALIZER_ID);

	return convert_alternative
	<
		mem_initializer_id,
		id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID,
		id_t::IDENTIFIER
	>(node);
}

member_declaration
convert_member_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION);

	return convert_alternative
	<
		member_declaration,
		id_t::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
		id_t::MEMBER_DECLARATION_UNQUALIFIED_ID,
		id_t::MEMBER_DECLARATION_FUNCTION_DEFINITION,
		id_t::USING_DECLARATION,
		id_t::TEMPLATE_DECLARATION
	>(node);
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

member_declarator
convert_member_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATOR);

	return convert_alternative
	<
		member_declarator,
		id_t::MEMBER_DECLARATOR_DECLARATOR,
		id_t::MEMBER_DECLARATOR_BIT_FIELD_MEMBER
	>(node);
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

member_specification_part
convert_member_specification_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_SPECIFICATION_PART);

    return convert_alternative
	<
		member_specification_part,
		id_t::MEMBER_DECLARATION,
		id_t::MEMBER_SPECIFICATION_ACCESS_SPECIFIER
	>(node);
}

namespace_definition
convert_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NAMESPACE_DEFINITION);

	tree_node_iterator_t namespace_keyword_it = node.children.begin();
	tree_node_iterator_t identifier_it = find_node<id_t::IDENTIFIER>(node);
	tree_node_iterator_t opening_brace_it = find_node(node, "{");
	tree_node_iterator_t declaration_seq_it = find_node<id_t::DECLARATION_SEQ>(node);

    return namespace_definition
    (
		convert_next_space(node, namespace_keyword_it),
        convert_optional<identifier>(node, identifier_it),
		convert_next_space(node, identifier_it),
		convert_next_space(node, opening_brace_it),
        convert_optional<declaration_seq>(node, declaration_seq_it),
		convert_next_space(node, declaration_seq_it)
    );
}

nested_identifier_or_template_id
convert_nested_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID);

    return nested_identifier_or_template_id
    (
        check_node_existence(node, "::", 0),
        find_and_convert_node<boost::optional<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
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

new_declarator
convert_new_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_DECLARATOR);

	return new_declarator();
}

new_expression
convert_new_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_EXPRESSION);

	return convert_alternative
	<
		new_expression,
		id_t::NEW_TYPE_ID_NEW_EXPRESSION,
		id_t::TYPE_ID_NEW_EXPRESSION
	>(node);
}

new_placement
convert_new_placement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_PLACEMENT);

	return new_placement();
}

new_initializer
convert_new_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_INITIALIZER);

	tree_node_iterator_t opening_bracket_it = node.children.begin();
	tree_node_iterator_t expression_list_it = find_node<id_t::EXPRESSION_LIST>(node);

	return new_initializer
	(
		convert_next_space(node, opening_bracket_it),
		convert_optional<expression_list>(node, expression_list_it),
		convert_next_space(node, expression_list_it)
	);
}

new_type_id
convert_new_type_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NEW_TYPE_ID);

	tree_node_iterator_t type_specifier_seq_it = node.children.begin();
	tree_node_iterator_t new_declarator_it = find_node<id_t::NEW_DECLARATOR>(node);

	return new_type_id
	(
		convert_node<type_specifier_seq>(*type_specifier_seq_it),
		convert_previous_space(node, new_declarator_it),
		convert_optional<new_declarator>(node, new_declarator_it)
	);
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

operator_
convert_operator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::OPERATOR);

	return convert_alternative
	<
		operator_,
		id_t::ARRAY_OPERATOR,
		id_t::SIMPLE_OPERATOR
	>(node);
}

operator_function_id
convert_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::OPERATOR_FUNCTION_ID);

	tree_node_iterator_t operator_keyword_it = node.children.begin();
	tree_node_iterator_t operator_it = find_node<id_t::OPERATOR>(node);

	return operator_function_id
	(
		convert_next_space(node, operator_keyword_it),
		convert_node<operator_>(*operator_it)
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

parameter_declaration_clause
convert_parameter_declaration_clause(const tree_node_t& node)
{
    assert(node.value.id() == id_t::PARAMETER_DECLARATION_CLAUSE);

    bool trailing_comma = check_node_existence(node, ",", 1);
    bool ellipsis = check_node_existence(node, "...");

    if(trailing_comma) assert(ellipsis);

    return parameter_declaration_clause
    (
		find_and_convert_node<parameter_declaration_list, id_t::PARAMETER_DECLARATION_LIST>(node),
		trailing_comma,
		ellipsis
    );
}

postfix_expression::first_part
convert_postfix_expression_first_part(const tree_node_t& node)
{
	assert(node.value.id() == id_t::POSTFIX_EXPRESSION_FIRST_PART);

	return convert_alternative
	<
		postfix_expression::first_part,
		id_t::PRIMARY_EXPRESSION,
		id_t::SIMPLE_TYPE_SPECIFIER_POSTFIX_EXPRESSION,
		id_t::TYPENAME_EXPRESSION,
		id_t::TEMPLATE_TYPENAME_EXPRESSION,
		id_t::DYNAMIC_CAST_EXPRESSION,
		id_t::STATIC_CAST_EXPRESSION,
		id_t::REINTERPRET_CAST_EXPRESSION,
		id_t::CONST_CAST_EXPRESSION,
		id_t::TYPEID_EXPRESSION,
		id_t::TYPE_ID_TYPEID_EXPRESSION
	>(node);
}

postfix_expression::last_part
convert_postfix_expression_last_part(const tree_node_t& node)
{
	assert(node.value.id() == id_t::POSTFIX_EXPRESSION_LAST_PART);

	return convert_alternative
	<
		postfix_expression::last_part,
		id_t::SQUARE_BRACKETED_EXPRESSION,
		id_t::BRACKETED_EXPRESSION_LIST,
		id_t::DOT_ID_EXPRESSION,
		id_t::ARROW_ID_EXPRESSION,
		id_t::DOT_PSEUDO_DESTRUCTOR_NAME,
		id_t::ARROW_PSEUDO_DESTRUCTOR_NAME,
		id_t::DOUBLE_MINUS,
		id_t::DOUBLE_PLUS
	>(node);
}

postfix_expression
convert_postfix_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::POSTFIX_EXPRESSION);

	tree_node_iterator_t first_part_it = node.children.begin();
	tree_node_iterator_t last_part_it = find_node<id_t::POSTFIX_EXPRESSION_LAST_PART_SEQ>(node);

	return postfix_expression
	(
		convert_node<postfix_expression::first_part>(*first_part_it),
		convert_previous_space(node, last_part_it),
		convert_optional<postfix_expression::last_part_seq>(node, last_part_it)
	);
}

primary_expression
convert_primary_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::PRIMARY_EXPRESSION);

	return convert_alternative
	<
		primary_expression,
		id_t::THIS_KEYWORD,
		id_t::LITERAL,
		id_t::ROUND_BRACKETED_EXPRESSION,
		id_t::ID_EXPRESSION
	>(node);
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

qualified_id
convert_qualified_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_ID);

	return convert_alternative
	<
		qualified_id,
		id_t::QUALIFIED_NESTED_ID,
		id_t::QUALIFIED_OPERATOR_FUNCTION_ID,
		id_t::QUALIFIED_TEMPLATE_ID,
		id_t::QUALIFIED_IDENTIFIER
	>(node);
}

qualified_identifier
convert_qualified_identifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_IDENTIFIER);

    return qualified_identifier
    (
        find_and_convert_node<identifier, id_t::IDENTIFIER>(node)
    );
}

qualified_nested_id
convert_qualified_nested_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_NESTED_ID);

	tree_node_iterator_t double_colon_it = find_node(node, "::");
	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t template_keyword_it = find_node(node, "template");

    return qualified_nested_id
    (
		double_colon_it != node.children.end(),
		convert_next_space(node, double_colon_it),
		convert_node<nested_name_specifier>(*nested_name_specifier_it),
		convert_next_space(node, nested_name_specifier_it),
		template_keyword_it != node.children.end(),
		convert_next_space(node, template_keyword_it),
		find_and_convert_node<unqualified_id, id_t::UNQUALIFIED_ID>(node)
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

reinterpret_cast_expression
convert_reinterpret_cast_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::REINTERPRET_CAST_EXPRESSION);

	return reinterpret_cast_expression();
}

return_statement
convert_return_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::RETURN_STATEMENT);

	tree_node_iterator_t return_keyword_it = node.children.begin();
	tree_node_iterator_t expression_it = find_node<id_t::EXPRESSION>(node);

	return return_statement
	(
		convert_next_space(node, return_keyword_it),
		convert_optional<expression>(node, expression_it),
		convert_next_space(node, expression_it)
	);
}

round_bracketed_expression
convert_round_bracketed_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ROUND_BRACKETED_EXPRESSION);

	tree_node_iterator_t opening_bracket_it = node.children.begin();
	tree_node_iterator_t expression_it = find_node<id_t::EXPRESSION>(node);

	return round_bracketed_expression
	(
		convert_next_space(node, opening_bracket_it),
		convert_node<expression>(*expression_it),
		convert_next_space(node, expression_it)
	);
}

selection_statement
convert_selection_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SELECTION_STATEMENT);

	return convert_alternative
	<
		selection_statement,
		id_t::IF_STATEMENT,
		id_t::SWITCH_STATEMENT
	>(node);
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

simple_delete_expression
convert_simple_delete_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SIMPLE_DELETE_EXPRESSION);

	tree_node_iterator_t double_colon_it = find_node(node, "::");
	tree_node_iterator_t delete_keyword_it = find_node(node, "delete");

	return simple_delete_expression
	(
		double_colon_it != node.children.end(),
		convert_next_space(node, double_colon_it),
		convert_next_space(node, delete_keyword_it),
		find_and_convert_node<cast_expression, id_t::CAST_EXPRESSION>(node)
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

simple_type_specifier
convert_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SIMPLE_TYPE_SPECIFIER);

	return convert_alternative
	<
		simple_type_specifier,
		id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID,
		id_t::SIMPLE_TEMPLATE_TYPE_SPECIFIER,
		id_t::BUILT_IN_TYPE_SPECIFIER
	>(node);
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

square_bracketed_expression
convert_square_bracketed_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::SQUARE_BRACKETED_EXPRESSION);

	tree_node_iterator_t i = find_node<id_t::EXPRESSION>(node);

	return square_bracketed_expression
	(
		convert_previous_space(node, i),
		convert_node<expression>(*i),
		convert_next_space(node, i)
	);
}

statement
convert_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::STATEMENT);

	return convert_alternative
	<
		statement,
		id_t::LABELED_STATEMENT,
		id_t::EXPRESSION_STATEMENT,
		id_t::COMPOUND_STATEMENT,
		id_t::SELECTION_STATEMENT,
		id_t::ITERATION_STATEMENT,
		id_t::JUMP_STATEMENT,
		id_t::BLOCK_DECLARATION,
		id_t::TRY_BLOCK
	>(node);
}

static_cast_expression
convert_static_cast_expression(const tree_node_t& node)
{
	assert(node.value.id() == id_t::STATIC_CAST_EXPRESSION);

	return static_cast_expression();
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

template_argument
convert_template_argument(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TEMPLATE_ARGUMENT);

	return convert_alternative
	<
		template_argument,
		//id_t::TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
		id_t::TYPE_ID,
		id_t::ID_EXPRESSION
	>(node);
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

	boost::optional<space> first_space_node;
	boost::optional<declaration_seq> declaration_seq_node;
	boost::optional<space> post_declaration_seq_node;

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

type_id_new_expression
convert_type_id_new_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TYPE_ID_NEW_EXPRESSION);

	tree_node_iterator_t leading_double_colon_it = find_node(node, "::");
	tree_node_iterator_t new_keyword_it = find_node(node, "new");
	tree_node_iterator_t new_placement_it = find_node<id_t::NEW_PLACEMENT>(node);
	tree_node_iterator_t opening_bracket_it = find_node(node, "(");
	tree_node_iterator_t type_id_it = find_node<id_t::TYPE_ID>(node);
	tree_node_iterator_t new_initializer_it = find_node<id_t::NEW_INITIALIZER>(node);

	return type_id_new_expression
	(
		leading_double_colon_it != node.children.end(),
		convert_next_space(node, leading_double_colon_it),
		convert_next_space(node, new_keyword_it),
		convert_optional<new_placement>(node, new_placement_it),
		convert_next_space(node, new_placement_it),
		convert_next_space(node, opening_bracket_it),
		convert_node<type_id>(*type_id_it),
		convert_next_space(node, type_id_it),
		convert_previous_space(node, new_initializer_it),
		convert_optional<new_initializer>(node, new_initializer_it)
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

type_specifier
convert_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TYPE_SPECIFIER);

	return convert_alternative
	<
		type_specifier,
		id_t::SIMPLE_TYPE_SPECIFIER,
		id_t::CLASS_SPECIFIER,
		id_t::ENUM_SPECIFIER,
		id_t::ELABORATED_TYPE_SPECIFIER,
		id_t::CV_QUALIFIER,
		id_t::TYPEOF_EXPRESSION
	>(node);
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

unary_expression
convert_unary_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::UNARY_EXPRESSION);

	return convert_alternative
	<
		unary_expression,
		id_t::UNARY_OPERATOR_UNARY_EXPRESSION,
		id_t::TYPE_ID_SIZEOF_EXPRESSION,
		id_t::UNARY_SIZEOF_EXPRESSION,
		id_t::POSTFIX_EXPRESSION,
		id_t::NEW_EXPRESSION,
		id_t::DELETE_EXPRESSION
	>(node);
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

unqualified_id
convert_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::UNQUALIFIED_ID);

	return convert_alternative
	<
		unqualified_id,
		id_t::OPERATOR_FUNCTION_ID,
		id_t::CONVERSION_FUNCTION_ID,
		id_t::DESTRUCTOR_NAME,
		id_t::TEMPLATE_ID,
		id_t::IDENTIFIER
	>(node);
}

using_declaration
convert_using_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::USING_DECLARATION);

    return using_declaration
    (
        check_node_existence(node, "typename", 1),
        check_node_existence(node, "::"),
        find_and_convert_node<boost::optional<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
        find_and_convert_node<unqualified_id, id_t::UNQUALIFIED_ID>(node)
    );
}

using_directive
convert_using_directive(const tree_node_t& node)
{
    assert(node.value.id() == id_t::USING_DIRECTIVE);

	tree_node_iterator_t using_keyword_it = node.children.begin();
	tree_node_iterator_t namespace_keyword_it = find_node(node, "namespace");
	tree_node_iterator_t leading_double_colon_it = find_node(node, "::");
	tree_node_iterator_t nested_name_specifier_it = find_node<id_t::NESTED_NAME_SPECIFIER>(node);
	tree_node_iterator_t identifier_it = find_node<id_t::IDENTIFIER>(node);

    return using_directive
    (
		convert_next_space(node, using_keyword_it),
		convert_next_space(node, namespace_keyword_it),
		leading_double_colon_it != node.children.end(),
		convert_next_space(node, leading_double_colon_it),
		convert_optional<nested_name_specifier>(node, nested_name_specifier_it),
		convert_next_space(node, nested_name_specifier_it),
		convert_node<identifier>(*identifier_it),
		convert_next_space(node, identifier_it)
    );
}

while_statement
convert_while_statement(const tree_node_t& node)
{
    assert(node.value.id() == id_t::WHILE_STATEMENT);

	return while_statement();
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis

