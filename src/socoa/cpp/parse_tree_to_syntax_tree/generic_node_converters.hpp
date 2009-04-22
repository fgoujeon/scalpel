/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTERS_HPP
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_NODE_CONVERTERS_HPP

#include <string>
#include "../grammar.hpp"
#include "conversion_functions.hpp"
#include "special_conversion_functions_fwd.hpp"

#define SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_ID_SPECIALIZATION(id, return_type, convert_function)\
template<class T>																				\
struct node_converter_from_id<T, grammar::parser_id::id>								\
{																								\
	static																						\
	syntax_nodes::return_type																	\
	convert(const tree_node_t& node)															\
	{																							\
		return convert_##convert_function(node);												\
	}																							\
};

#define SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION(return_type, convert_function)\
template<>																						\
struct node_converter_from_type<syntax_nodes::return_type>										\
{																								\
	static																						\
	syntax_nodes::return_type																	\
	convert(const tree_node_t& node)															\
	{																							\
		return convert_##convert_function(node);												\
	}																							\
};

#define SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION(id, return_type, convert_function)\
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_ID_SPECIALIZATION(id, return_type, convert_function)\
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION(return_type, convert_function)

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
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

//specialization for sequences
template<class T>
struct node_converter_from_type
{
	static
	T
	convert(const tree_node_t& node)
	{
		return convert_sequence<T>(node);
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
//SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION(id::ASM_DEFINITION,
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	ASSIGNMENT_EXPRESSION,
	assignment_expression,
	assignment_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	ASSIGNMENT_EXPRESSION_FIRST_PART,
	assignment_expression::first_part,
	assignment_expression_first_part
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	BASE_CLAUSE,
	base_clause,
	base_clause
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	base_specifier,
	base_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	BLOCK_DECLARATION,
	block_declaration,
	block_declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	BOOLEAN_LITERAL,
	boolean_literal,
	boolean_literal
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	BREAK_STATEMENT,
	break_statement,
	break_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	BUILT_IN_TYPE_SPECIFIER,
	built_in_type_specifier,
	string_enumeration<syntax_nodes::built_in_type_specifier>
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CAST_EXPRESSION,
	cast_expression,
	cast_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CHARACTER_LITERAL,
	character_literal,
	character_literal
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CLASS_HEAD,
	class_head,
	class_head
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CLASS_SPECIFIER,
	class_specifier,
	class_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	COMPOUND_STATEMENT,
	compound_statement,
	compound_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CONDITIONAL_EXPRESSION,
	conditional_expression,
	conditional_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CONTINUE_STATEMENT,
	continue_statement,
	continue_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CONVERSION_FUNCTION_ID,
	conversion_function_id,
	conversion_function_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CTOR_INITIALIZER,
	ctor_initializer,
	ctor_initializer
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	CV_QUALIFIER,
	cv_qualifier,
	cv_qualifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	decl_specifier,
	decl_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DECLARATION,
	declaration,
	declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DECLARATOR,
	declarator,
	declarator
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DECLARATOR_ID,
	declarator_id,
	declarator_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DELETE_EXPRESSION,
	delete_expression,
	delete_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DESTRUCTOR_NAME,
	destructor_name,
	destructor_name
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR,
	direct_declarator,
	direct_declarator
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_ARRAY_PART,
	direct_declarator::array_part,
	direct_declarator_array_part
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_FUNCTION_PART,
	direct_declarator::function_part,
	direct_declarator_function_part
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DIRECT_DECLARATOR_NEXT_PART,
	direct_declarator::next_part,
	direct_declarator_next_part
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	DO_WHILE_STATEMENT,
	do_while_statement,
	do_while_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	ELABORATED_TYPE_SPECIFIER,
	elaborated_type_specifier,
	elaborated_type_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	EXPRESSION_STATEMENT,
	expression_statement,
	expression_statement
)
//            id::EXPLICIT_INSTANTIATION,
//            id::EXPLICIT_SPECIALIZATION,
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	FLOATING_LITERAL,
	floating_literal,
	floating_literal
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	FOR_STATEMENT,
	for_statement,
	for_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	FUNCTION_DEFINITION,
	function_definition,
	function_definition
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	FUNCTION_SPECIFIER,
	function_specifier,
	string_enumeration<syntax_nodes::function_specifier>
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	GOTO_STATEMENT,
	goto_statement,
	goto_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	ID_EXPRESSION,
	id_expression,
	id_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	IDENTIFIER,
	identifier,
	identifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	IDENTIFIER_OR_TEMPLATE_ID,
	identifier_or_template_id,
	identifier_or_template_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	init_declarator,
	init_declarator
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	INTEGER_LITERAL,
	integer_literal,
	integer_literal
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	ITERATION_STATEMENT,
	iteration_statement,
	iteration_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	JUMP_STATEMENT,
	jump_statement,
	jump_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	LABELED_STATEMENT,
	labeled_statement,
	labeled_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	LITERAL,
	literal,
	literal
)
//            id::LINKAGE_SPECIFICATION,
	//id::NAMESPACE_ALIAS_DEFINITION,
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	mem_initializer,
	mem_initializer
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEM_INITIALIZER_ID,
	mem_initializer_id,
	mem_initializer_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION,
	member_declaration,
	member_declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION_FUNCTION_DEFINITION,
	member_declaration_function_definition,
	member_declaration_function_definition
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
	member_declaration_member_declarator_list,
	member_declaration_member_declarator_list
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATION_UNQUALIFIED_ID,
	member_declaration_unqualified_id,
	member_declaration_unqualified_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	member_declarator,
	member_declarator
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATOR_BIT_FIELD_MEMBER,
	member_declarator_bit_field_member,
	member_declarator_bit_field_member
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_DECLARATOR_DECLARATOR,
	member_declarator_declarator,
	member_declarator_declarator
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_SPECIFICATION_PART,
	member_specification_part,
	member_specification_part
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	MEMBER_SPECIFICATION_ACCESS_SPECIFIER,
	member_specification_access_specifier,
	member_specification_access_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	NAMESPACE_DEFINITION,
	namespace_definition,
	namespace_definition
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	NESTED_IDENTIFIER_OR_TEMPLATE_ID,
	nested_identifier_or_template_id,
	nested_identifier_or_template_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	NESTED_NAME_SPECIFIER,
	nested_name_specifier,
	nested_name_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	NESTED_NAME_SPECIFIER_NEXT_PART,
	nested_name_specifier::next_part,
	nested_name_specifier_next_part
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	NEW_EXPRESSION,
	new_expression,
	new_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	OPERATOR_FUNCTION_ID,
	operator_function_id,
	operator_function_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	parameter_declaration,
	parameter_declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	PARAMETER_DECLARATION_CLAUSE,
	parameter_declaration_clause,
	parameter_declaration_clause
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	POSTFIX_EXPRESSION,
	postfix_expression,
	postfix_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	PRIMARY_EXPRESSION,
	primary_expression,
	primary_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	PTR_OPERATOR,
	ptr_operator,
	ptr_operator
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_ID,
	qualified_id,
	qualified_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_NESTED_ID,
	qualified_nested_id,
	qualified_nested_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_OPERATOR_FUNCTION_ID,
	qualified_operator_function_id,
	qualified_operator_function_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_TEMPLATE_ID,
	qualified_template_id,
	qualified_template_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	QUALIFIED_IDENTIFIER,
	qualified_identifier,
	qualified_identifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	RETURN_STATEMENT,
	return_statement,
	return_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	SELECTION_STATEMENT,
	selection_statement,
	selection_statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_DECLARATION,
	simple_declaration,
	simple_declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_TYPE_SPECIFIER,
	simple_type_specifier,
	simple_type_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	SIMPLE_TEMPLATE_TYPE_SPECIFIER,
	simple_template_type_specifier,
	simple_template_type_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	SPACE,
	space,
	space
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	STATEMENT,
	statement,
	statement
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	STORAGE_CLASS_SPECIFIER,
	storage_class_specifier,
	string_enumeration<syntax_nodes::storage_class_specifier>
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	STRING_LITERAL,
	string_literal,
	string_literal
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION
(
	template_argument,
	template_argument
)
/*SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
	assignment_expression,
	assignment_expression
)*/
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_DECLARATION,
	template_declaration,
	template_declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TEMPLATE_ID,
	template_id,
	template_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TRANSLATION_UNIT,
	translation_unit,
	translation_unit
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TRY_BLOCK,
	try_block,
	try_block
)
/*SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_ID,
	type_id,
	type_id
)*/
SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_ID_SPECIALIZATION
(
	TYPE_NAME,
	identifier,
	identifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	TYPE_SPECIFIER,
	type_specifier,
	type_specifier
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	UNARY_EXPRESSION,
	unary_expression,
	unary_expression
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	UNQUALIFIED_ID,
	unqualified_id,
	unqualified_id
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	USING_DECLARATION,
	using_declaration,
	using_declaration
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	USING_DIRECTIVE,
	using_directive,
	using_directive
)
SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
(
	WHILE_STATEMENT,
	while_statement,
	while_statement
)

template<class SyntaxNodeT>
inline
SyntaxNodeT
convert_node(const tree_node_t& node)
{
	return node_converter_from_type<SyntaxNodeT>::convert(node);
}

}}} //namespace socoa::cpp::parse_tree_to_syntax_tree

#undef SOCOA_CPP_GENERATE_NODE_CONVERTER_SPECIALIZATION
#undef SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_ID_SPECIALIZATION
#undef SOCOA_CPP_GENERATE_NODE_CONVERTER_FROM_TYPE_SPECIALIZATION

#endif
