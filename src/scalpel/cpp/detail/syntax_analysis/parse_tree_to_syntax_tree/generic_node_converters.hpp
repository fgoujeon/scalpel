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

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTERS_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTERS_HPP

#include <string>
#include "../../../syntax_tree.hpp"
#include "../grammar.hpp"
#include "conversion_functions.hpp"
#include "sequence_node_converter_fwd.hpp"
#include "special_conversion_functions_fwd.hpp"

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_ID_SPECIALIZATION(id, return_type, convert_function)\
template<class T>											\
struct node_converter_from_id<T, grammar::parser_id::id>	\
{															\
	static													\
	syntax_nodes::return_type								\
	convert(const tree_node_t& node)						\
	{														\
		return convert_##convert_function(node);			\
	}														\
};

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION(return_type, convert_function)\
template<>													\
struct node_converter_from_type<syntax_nodes::return_type>	\
{															\
	static													\
	syntax_nodes::return_type								\
	convert(const tree_node_t& node)						\
	{														\
		return convert_##convert_function(node);			\
	}														\
};

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_CHECKER_SPECIALIZATION(correct_id, node_type)\
template<>													\
struct id_checker<syntax_nodes::node_type>					\
{															\
	static													\
	bool													\
	check(const boost::spirit::parser_id id)				\
	{														\
		return id == id_t::correct_id;						\
	}														\
};

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION(id, return_type, convert_function)\
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_ID_SPECIALIZATION(id, return_type, convert_function)\
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION(return_type, convert_function)\
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_ID_CHECKER_SPECIALIZATION(id, return_type)

#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_SEQUENCE_NODE_CONVERTER_SPECIALIZATION(id, return_type)\
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_ID_SPECIALIZATION(id, return_type, node<syntax_nodes::return_type>)

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

/**
Calls the convert_* function corresponding to the given grammar's parser id.
*/
template<class T, int ParserId>
struct node_converter_from_id;

/**
Calls the convert_* function corresponding to the given syntax node type.
*/
template<class T>
struct node_converter_from_type;

template<class SyntaxNodeT>
struct id_checker;

template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node);






//specialization for list nodes
template<class T>
struct node_converter_from_type
{
	static
	T
	convert(const tree_node_t& node)
	{
		return convert_list_node<T>(node);
	}
};

//specialization for sequence nodes
template<class... NodesT>
struct node_converter_from_type<syntax_nodes::sequence_node<NodesT...>>
{
	static
	syntax_nodes::sequence_node<NodesT...>
	convert(const tree_node_t& node)
	{
		return convert_sequence_node<syntax_nodes::sequence_node<NodesT...>>(node);
	}
};

//specialization for optional nodes
template<class T>
struct node_converter_from_type<syntax_nodes::optional_node<T>>
{
	static
	T
	convert(const tree_node_t& node)
	{
		return convert_node<T>(node);
	}
};

//specialization for simple text nodes
template<const std::string& Text>
struct node_converter_from_type<syntax_nodes::simple_text_node<Text>>
{
	static
	syntax_nodes::simple_text_node<Text>
	convert(const tree_node_t& node)
	{
		return convert_simple_text<Text>(node);
	}
};

//specialization for string enumerations
template<const std::vector<std::string>& StringList>
struct node_converter_from_type<syntax_nodes::string_enumeration_node<StringList>>
{
	static
	syntax_nodes::string_enumeration_node<StringList>
	convert(const tree_node_t& node)
	{
		return convert_string_enumeration<syntax_nodes::string_enumeration_node<StringList>>(node);
	}
};

//other specializations
//SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION(id::ASM_DEFINITION,
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ASSIGNMENT_EXPRESSION,
	assignment_expression,
	assignment_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ASSIGNMENT_EXPRESSION_CONDITION,
	assignment_expression_condition,
	assignment_expression_condition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ASSIGNMENT_EXPRESSION_FIRST_PART,
	assignment_expression::first_part,
	assignment_expression_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_SEQUENCE_NODE_CONVERTER_SPECIALIZATION
(
	BASE_CLAUSE,
	base_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	base_specifier,
	base_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BLOCK_DECLARATION,
	block_declaration,
	block_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BOOLEAN_LITERAL,
	boolean_literal,
	boolean_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BRACKETED_INITIALIZER,
	bracketed_initializer,
	bracketed_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BREAK_STATEMENT,
	break_statement,
	break_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BUILT_IN_TYPE_SPECIFIER,
	built_in_type_specifier,
	string_enumeration<syntax_nodes::built_in_type_specifier>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CAST_EXPRESSION,
	cast_expression,
	cast_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CHARACTER_LITERAL,
	character_literal,
	character_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CLASS_HEAD,
	class_head,
	class_head
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CLASS_SPECIFIER,
	class_specifier,
	class_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	COMPOUND_STATEMENT,
	compound_statement,
	compound_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CONDITION,
	condition,
	condition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CONDITIONAL_EXPRESSION,
	conditional_expression,
	conditional_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CONTINUE_STATEMENT,
	continue_statement,
	continue_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CONVERSION_FUNCTION_ID,
	conversion_function_id,
	conversion_function_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CTOR_INITIALIZER,
	ctor_initializer,
	ctor_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CV_QUALIFIER,
	cv_qualifier,
	cv_qualifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	decl_specifier,
	decl_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DECLARATION,
	declaration,
	declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DECLARATOR,
	declarator,
	declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DECLARATOR_ID,
	declarator_id,
	declarator_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DELETE_EXPRESSION,
	delete_expression,
	delete_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DESTRUCTOR_NAME,
	destructor_name,
	destructor_name
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR,
	direct_declarator,
	direct_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_ARRAY_PART,
	direct_declarator::array_part,
	direct_declarator_array_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_FUNCTION_PART,
	direct_declarator::function_part,
	direct_declarator_function_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_LAST_PART,
	direct_declarator::last_part,
	direct_declarator_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DO_WHILE_STATEMENT,
	do_while_statement,
	do_while_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ELABORATED_TYPE_SPECIFIER,
	elaborated_type_specifier,
	elaborated_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EMPTY_INITIALIZER_LIST_INITIALIZER_CLAUSE,
	empty_initializer_list_initializer_clause,
	empty_initializer_list_initializer_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EQUAL_INITIALIZER,
	equal_initializer,
	equal_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EXPRESSION,
	expression,
	list_node<syntax_nodes::expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EXPRESSION_STATEMENT,
	expression_statement,
	expression_statement
)
//            id::EXPLICIT_INSTANTIATION,
//            id::EXPLICIT_SPECIALIZATION,
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	FLOATING_LITERAL,
	floating_literal,
	floating_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	FOR_INIT_STATEMENT,
	for_init_statement,
	for_init_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	FOR_STATEMENT,
	for_statement,
	for_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	FUNCTION_DEFINITION,
	function_definition,
	function_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	FUNCTION_SPECIFIER,
	function_specifier,
	string_enumeration<syntax_nodes::function_specifier>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	GOTO_STATEMENT,
	goto_statement,
	goto_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ID_EXPRESSION,
	id_expression,
	id_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	IDENTIFIER,
	identifier,
	identifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	IDENTIFIER_OR_TEMPLATE_ID,
	identifier_or_template_id,
	identifier_or_template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	init_declarator,
	init_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	INITIALIZER,
	initializer,
	initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	INITIALIZER_CLAUSE,
	initializer_clause,
	initializer_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	INITIALIZER_LIST_INITIALIZER_CLAUSE,
	initializer_list_initializer_clause,
	initializer_list_initializer_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	INTEGER_LITERAL,
	integer_literal,
	integer_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ITERATION_STATEMENT,
	iteration_statement,
	iteration_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	JUMP_STATEMENT,
	jump_statement,
	jump_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	LABELED_STATEMENT,
	labeled_statement,
	labeled_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	LITERAL,
	literal,
	literal
)
//            id::LINKAGE_SPECIFICATION,
	//id::NAMESPACE_ALIAS_DEFINITION,
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	mem_initializer,
	mem_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEM_INITIALIZER_ID,
	mem_initializer_id,
	mem_initializer_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION,
	member_declaration,
	member_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION_FUNCTION_DEFINITION,
	member_declaration_function_definition,
	member_declaration_function_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
	member_declaration_member_declarator_list,
	member_declaration_member_declarator_list
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION_UNQUALIFIED_ID,
	member_declaration_unqualified_id,
	member_declaration_unqualified_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	member_declarator,
	member_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATOR_BIT_FIELD_MEMBER,
	member_declarator_bit_field_member,
	member_declarator_bit_field_member
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATOR_DECLARATOR,
	member_declarator_declarator,
	member_declarator_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_SPECIFICATION_PART,
	member_specification_part,
	member_specification_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_SPECIFICATION_ACCESS_SPECIFIER,
	member_specification_access_specifier,
	member_specification_access_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NAMESPACE_DEFINITION,
	namespace_definition,
	namespace_definition
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NESTED_IDENTIFIER_OR_TEMPLATE_ID,
	nested_identifier_or_template_id,
	nested_identifier_or_template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NESTED_NAME_SPECIFIER,
	nested_name_specifier,
	nested_name_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NESTED_NAME_SPECIFIER_LAST_PART,
	nested_name_specifier::last_part,
	nested_name_specifier_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_EXPRESSION,
	new_expression,
	new_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	OPERATOR_FUNCTION_ID,
	operator_function_id,
	operator_function_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	parameter_declaration,
	parameter_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	PARAMETER_DECLARATION_CLAUSE,
	parameter_declaration_clause,
	parameter_declaration_clause
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	POSTFIX_EXPRESSION,
	postfix_expression,
	postfix_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	PRIMARY_EXPRESSION,
	primary_expression,
	primary_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	PTR_OPERATOR,
	ptr_operator,
	ptr_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_ID,
	qualified_id,
	qualified_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_NESTED_ID,
	qualified_nested_id,
	qualified_nested_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_OPERATOR_FUNCTION_ID,
	qualified_operator_function_id,
	qualified_operator_function_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_TEMPLATE_ID,
	qualified_template_id,
	qualified_template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_IDENTIFIER,
	qualified_identifier,
	qualified_identifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	RETURN_STATEMENT,
	return_statement,
	return_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SELECTION_STATEMENT,
	selection_statement,
	selection_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_DECLARATION,
	simple_declaration,
	simple_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_TYPE_SPECIFIER,
	simple_type_specifier,
	simple_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_TEMPLATE_TYPE_SPECIFIER,
	simple_template_type_specifier,
	simple_template_type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SPACE,
	space,
	space
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	STATEMENT,
	statement,
	statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	STORAGE_CLASS_SPECIFIER,
	storage_class_specifier,
	string_enumeration<syntax_nodes::storage_class_specifier>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	STRING_LITERAL,
	string_literal,
	string_literal
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	template_argument,
	template_argument
)
/*SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
	assignment_expression,
	assignment_expression
)*/
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_DECLARATION,
	template_declaration,
	template_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_ID,
	template_id,
	template_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TRANSLATION_UNIT,
	translation_unit,
	translation_unit
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TRY_BLOCK,
	try_block,
	try_block
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_ID,
	type_id,
	type_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_ID_SPECIALIZATION
(
	TYPE_NAME,
	identifier,
	identifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_ID_SIZEOF_EXPRESSION,
	type_id_sizeof_expression,
	type_id_sizeof_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_SPECIFIER,
	type_specifier,
	type_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	UNARY_EXPRESSION,
	unary_expression,
	unary_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	UNARY_OPERATOR_UNARY_EXPRESSION,
	unary_operator_unary_expression,
	unary_operator_unary_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	UNARY_SIZEOF_EXPRESSION,
	unary_sizeof_expression,
	unary_sizeof_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	UNQUALIFIED_ID,
	unqualified_id,
	unqualified_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	USING_DECLARATION,
	using_declaration,
	using_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	USING_DIRECTIVE,
	using_directive,
	using_directive
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	WHILE_STATEMENT,
	while_statement,
	while_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	POSTFIX_EXPRESSION_FIRST_PART,
	postfix_expression::first_part,
	postfix_expression_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_TYPE_SPECIFIER_POSTFIX_EXPRESSION,
	simple_type_specifier_postfix_expression,
	simple_type_specifier_postfix_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPENAME_EXPRESSION,
	typename_expression,
	typename_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_TYPENAME_EXPRESSION,
	template_typename_expression,
	template_typename_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DYNAMIC_CAST_EXPRESSION,
	dynamic_cast_expression,
	cast_expression_template<syntax_nodes::dynamic_cast_expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	STATIC_CAST_EXPRESSION,
	static_cast_expression,
	cast_expression_template<syntax_nodes::static_cast_expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	REINTERPRET_CAST_EXPRESSION,
	reinterpret_cast_expression,
	cast_expression_template<syntax_nodes::reinterpret_cast_expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CONST_CAST_EXPRESSION,
	const_cast_expression,
	cast_expression_template<syntax_nodes::const_cast_expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPEID_EXPRESSION,
	typeid_expression,
	typeid_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_ID_TYPEID_EXPRESSION,
	type_id_typeid_expression,
	type_id_typeid_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	POSTFIX_EXPRESSION_LAST_PART,
	postfix_expression::last_part,
	postfix_expression_last_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SQUARE_BRACKETED_EXPRESSION,
	square_bracketed_node<syntax_nodes::expression>::type,
	square_bracketed_node<syntax_nodes::expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BRACKETED_EXPRESSION_LIST,
	round_bracketed_node<syntax_nodes::optional_node<syntax_nodes::expression_list>>::type,
	round_bracketed_node<syntax_nodes::optional_node<syntax_nodes::expression_list>>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DOT_ID_EXPRESSION,
	dot_id_expression,
	dot_id_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ARROW_ID_EXPRESSION,
	arrow_id_expression,
	arrow_id_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DOT_PSEUDO_DESTRUCTOR_NAME,
	dot_pseudo_destructor_name,
	dot_pseudo_destructor_name
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ARROW_PSEUDO_DESTRUCTOR_NAME,
	arrow_pseudo_destructor_name,
	arrow_pseudo_destructor_name
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	IF_STATEMENT,
	if_statement,
	if_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SWITCH_STATEMENT,
	switch_statement,
	switch_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CASE_STATEMENT,
	case_statement,
	case_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DEFAULT_STATEMENT,
	default_statement,
	default_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CLASSIC_LABELED_STATEMENT,
	classic_labeled_statement,
	classic_labeled_statement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DOUBLE_PLUS,
	simple_text_node<util::extern_strings::double_plus>,
	simple_text<util::extern_strings::double_plus>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DOUBLE_MINUS,
	simple_text_node<util::extern_strings::double_minus>,
	simple_text<util::extern_strings::double_minus>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	THIS_KEYWORD,
	simple_text_node<util::extern_strings::this_>,
	simple_text<util::extern_strings::this_>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ROUND_BRACKETED_EXPRESSION,
	round_bracketed_node<syntax_nodes::expression>::type,
	round_bracketed_node<syntax_nodes::expression>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	HANDLER,
	handler,
	handler
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	THROW_EXPRESSION,
	throw_expression,
	throw_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EXCEPTION_DECLARATION,
	exception_declaration,
	exception_declaration
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EXCEPTION_DECLARATOR,
	exception_declarator,
	exception_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EXCEPTION_ABSTRACT_DECLARATOR,
	exception_abstract_declarator,
	exception_abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ELLIPSIS,
	simple_text_node<util::extern_strings::ellipsis>,
	simple_text<util::extern_strings::ellipsis>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_SPECIFIER_SEQ,
	type_specifier_seq,
	list_node<syntax_nodes::type_specifier_seq>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_ABSTRACT_DECLARATOR,
	direct_abstract_declarator,
	direct_abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	PTR_OPERATOR_SEQ,
	ptr_operator_seq,
	list_node<syntax_nodes::ptr_operator_seq>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ABSTRACT_DECLARATOR,
	abstract_declarator,
	abstract_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	FUNCTION_TRY_BLOCK,
	function_try_block,
	function_try_block
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	OPERATOR,
	operator_,
	operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ARRAY_OPERATOR,
	array_operator,
	array_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_ARRAY_OPERATOR,
	new_array_operator,
	new_array_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DELETE_ARRAY_OPERATOR,
	delete_array_operator,
	delete_array_operator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_OPERATOR,
	simple_operator,
	string_enumeration<syntax_nodes::simple_operator>
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CLASS_TEMPLATE_ELABORATED_SPECIFIER,
	class_template_elaborated_specifier,
	class_template_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	CLASS_ELABORATED_SPECIFIER,
	class_elaborated_specifier,
	class_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ENUM_ELABORATED_SPECIFIER,
	enum_elaborated_specifier,
	enum_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPENAME_TEMPLATE_ELABORATED_SPECIFIER,
	typename_template_elaborated_specifier,
	typename_template_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPENAME_ELABORATED_SPECIFIER,
	typename_elaborated_specifier,
	typename_elaborated_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_ID_NEW_EXPRESSION,
	type_id_new_expression,
	type_id_new_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_TYPE_ID_NEW_EXPRESSION,
	new_type_id_new_expression,
	new_type_id_new_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_PLACEMENT,
	new_placement,
	new_placement
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_INITIALIZER,
	new_initializer,
	new_initializer
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_TYPE_ID,
	new_type_id,
	new_type_id
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	NEW_DECLARATOR,
	new_declarator,
	new_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	TYPEOF_EXPRESSION,
	typeof_expression,
	typeof_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ENUM_SPECIFIER,
	enum_specifier,
	enum_specifier
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_DELETE_EXPRESSION,
	simple_delete_expression,
	simple_delete_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	ARRAY_DELETE_EXPRESSION,
	array_delete_expression,
	array_delete_expression
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	BRACKETED_DECLARATOR,
	bracketed_declarator,
	bracketed_declarator
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_FIRST_PART,
	direct_declarator::first_part,
	direct_declarator_first_part
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	EXCEPTION_SPECIFICATION,
	exception_specification,
	exception_specification
)
SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_NEW_DECLARATOR,
	direct_new_declarator,
	direct_new_declarator
)


template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node)
{
	return node_converter_from_type<SyntaxNodeT>::convert(node);
}

template<class SyntaxNodeT>
bool
check_id(const boost::spirit::parser_id id)
{
	return id_checker<SyntaxNodeT>::check(id);
}

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#undef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_SPECIALIZATION
#undef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_ID_SPECIALIZATION
#undef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION

#endif
