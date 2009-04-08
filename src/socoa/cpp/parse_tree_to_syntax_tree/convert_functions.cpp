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

#include "convert_functions.hpp"

#include "../grammar.hpp"
#include "basic_functions.hpp"
#include "generic_convert_functions.hpp"
#include "special_convert_functions.hpp"

using namespace socoa::cpp::syntax_tree;

namespace socoa { namespace cpp { namespace parse_tree_to_syntax_tree
{

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

id_expression
convert_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ID_EXPRESSION);

	return convert_node
	<
		id_expression,
		id_t::UNQUALIFIED_ID,
	   	id_t::QUALIFIED_ID
	>
	(
		get_only_child_node(node)
	);
}

unqualified_id
convert_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::UNQUALIFIED_ID);

	return convert_node
	<
		unqualified_id,
		id_t::OPERATOR_FUNCTION_ID,
		id_t::CONVERSION_FUNCTION_ID,
		id_t::DESTRUCTOR_NAME,
		id_t::TEMPLATE_ID,
		id_t::IDENTIFIER
	>
	(
		get_only_child_node(node)
	);
}

qualified_id
convert_qualified_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_ID);

	return convert_node
	<
		qualified_id,
		id_t::QUALIFIED_NESTED_ID,
		id_t::QUALIFIED_OPERATOR_FUNCTION_ID,
		id_t::QUALIFIED_TEMPLATE_ID,
		id_t::QUALIFIED_IDENTIFIER
	>
	(
		get_only_child_node(node)
	);
}

qualified_nested_id
convert_qualified_nested_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_NESTED_ID);

    return qualified_nested_id
    (
		check_node_existence(node, "::", 0),
		find_and_convert_node<nested_name_specifier, id_t::NESTED_NAME_SPECIFIER>(node),
		check_node_existence(node, "template", 1) || check_node_existence(node, "template", 2),
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

qualified_identifier
convert_qualified_identifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::QUALIFIED_IDENTIFIER);

    return qualified_identifier
    (
        find_and_convert_node<identifier, id_t::IDENTIFIER>(node)
    );
}

nested_name_specifier
convert_nested_name_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NESTED_NAME_SPECIFIER);

    return nested_name_specifier
    (
        find_and_convert_node<identifier_or_template_id, id_t::IDENTIFIER_OR_TEMPLATE_ID>(node),
		convert_nodes
		<
			std::vector<nested_name_specifier::second_part>,
			nested_name_specifier::second_part,
			id_t::NESTED_NAME_SPECIFIER_SECOND_PART
		>(node)
    );
}

nested_name_specifier::second_part
convert_nested_name_specifier_second_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NESTED_NAME_SPECIFIER_SECOND_PART);

    return nested_name_specifier::second_part
    (
		check_node_existence(node, "template", 0),
		find_and_convert_node<identifier_or_template_id, id_t::IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

declaration
convert_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECLARATION);

	return convert_node
	<
		declaration,
		id_t::BLOCK_DECLARATION,
		id_t::FUNCTION_DEFINITION,
		id_t::TEMPLATE_DECLARATION,
//            id_t::EXPLICIT_INSTANTIATION,
//            id_t::EXPLICIT_SPECIALIZATION,
//            id_t::LINKAGE_SPECIFICATION,
		id_t::NAMESPACE_DEFINITION
	>
	(
		get_only_child_node(node)
	);
}

block_declaration
convert_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BLOCK_DECLARATION);

	return convert_node
	<
		block_declaration,
		//id_t::ASM_DEFINITION,
		id_t::SIMPLE_DECLARATION,
		//id_t::NAMESPACE_ALIAS_DEFINITION,
		id_t::USING_DECLARATION,
		id_t::USING_DIRECTIVE
	>
	(
		get_only_child_node(node)
	);
}

simple_declaration
convert_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SIMPLE_DECLARATION);

    return simple_declaration
    (
		find_and_convert_node<boost::optional<decl_specifier_seq>, id_t::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ>(node),
		find_and_convert_node<boost::optional<init_declarator_list>, id_t::INIT_DECLARATOR_LIST>(node)
    );
}

decl_specifier
convert_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECL_SPECIFIER);

	return convert_node
	<
		decl_specifier,
		id_t::STORAGE_CLASS_SPECIFIER,
		id_t::TYPE_SPECIFIER,
		id_t::FUNCTION_SPECIFIER
	>
	(
		get_only_child_node(node)
	);
}

type_specifier
convert_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TYPE_SPECIFIER);

	return convert_node
	<
		type_specifier,
		id_t::SIMPLE_TYPE_SPECIFIER,
		id_t::CLASS_SPECIFIER,
		//id_t::ENUM_SPECIFIER,
		id_t::ELABORATED_TYPE_SPECIFIER,
		id_t::CV_QUALIFIER
		//id_t::TYPEOF_EXPRESSION
	>
	(
		get_only_child_node(node)
	);
}

simple_type_specifier
convert_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::SIMPLE_TYPE_SPECIFIER);

	return convert_node
	<
		simple_type_specifier,
		id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID,
		id_t::SIMPLE_TEMPLATE_TYPE_SPECIFIER,
		id_t::BUILT_IN_TYPE_SPECIFIER
	>
	(
		get_only_child_node(node)
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

identifier_or_template_id
convert_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::IDENTIFIER_OR_TEMPLATE_ID);

	return convert_node
	<
		identifier_or_template_id,
		id_t::IDENTIFIER,
		id_t::TEMPLATE_ID
	>
	(
		get_only_child_node(node)
	);
}

namespace_definition
convert_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::NAMESPACE_DEFINITION);

    return namespace_definition
    (
        find_and_convert_node<boost::optional<identifier>, id_t::IDENTIFIER>(node),
        find_and_convert_node<boost::optional<declaration_seq>, id_t::DECLARATION_SEQ>(node)
    );
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

    return using_directive
    (
        check_node_existence(node, "::", 2),
        find_and_convert_node<boost::optional<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
        find_and_convert_node<identifier, id_t::IDENTIFIER>(node)
    );
}

init_declarator
convert_init_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::INIT_DECLARATOR);

    return init_declarator
    (
		find_and_convert_node<declarator, id_t::DECLARATOR>(node)
    );
}

declarator
convert_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECLARATOR);

    return declarator
    (
		convert_nodes
		<
			std::vector<ptr_operator>,
			ptr_operator,
			id_t::PTR_OPERATOR
		>(node),
		find_and_convert_node<direct_declarator, id_t::DIRECT_DECLARATOR>(node)
    );
}

direct_declarator
convert_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR);

    direct_declarator decl
    (
		find_and_convert_node<boost::optional<declarator_id>, id_t::DECLARATOR_ID>(node),
		find_and_convert_node<boost::optional<declarator>, id_t::DECLARATOR>(node),
		convert_nodes
		<
			std::vector<direct_declarator::other_part>,
			direct_declarator::other_part,
			id_t::DIRECT_DECLARATOR_FUNCTION_PART
			//id_t::DIRECT_DECLARATOR_ARRAY_PART
		>(node)
    );

	return decl;
}

direct_declarator::function_part
convert_direct_declarator_function_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR_FUNCTION_PART);

	boost::optional<parameter_declaration_clause> new_parameter_declaration_clause = find_and_convert_node<boost::optional<parameter_declaration_clause>, id_t::PARAMETER_DECLARATION_CLAUSE>(node);

    ///@todo why must I do this?
    //grammar defines that this node MUST exist, but in practice it's not always the case
    if(!new_parameter_declaration_clause)
    {
        typedef sequence_node<parameter_declaration, util::extern_strings::comma> parameter_declaration_seq;

        //create an empty parameter declaration clause, if node didn't have been found
        new_parameter_declaration_clause = parameter_declaration_clause
        (
			parameter_declaration_seq(),
			false,
			false
        );
    }

    return direct_declarator::function_part
    (
        *new_parameter_declaration_clause,
        find_and_convert_node<boost::optional<cv_qualifier_seq>, id_t::CV_QUALIFIER_SEQ>(node)
    );
}

direct_declarator::array_part
convert_direct_declarator_array_part(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DIRECT_DECLARATOR_ARRAY_PART);

    return direct_declarator::array_part();
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

    return ptr_operator
	(
		check_node_existence(node, "*") ? ptr_operator::ASTERISK : ptr_operator::AMPERSAND,
		check_node_existence(node, "::", 0),
		find_and_convert_node<boost::optional<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<boost::optional<cv_qualifier_seq>, id_t::CV_QUALIFIER_SEQ>(node)
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

declarator_id
convert_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DECLARATOR_ID);

	return convert_node
	<
		declarator_id,
		id_t::ID_EXPRESSION,
		id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID
	>
	(
		get_only_child_node(node)
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

parameter_declaration
convert_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::PARAMETER_DECLARATION);

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
		find_and_convert_node<boost::optional<declarator>, id_t::DECLARATOR>(node),
		false
    );
}

function_definition
convert_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == id_t::FUNCTION_DEFINITION);

    return function_definition
    (
		find_and_convert_node
		<
			boost::optional<decl_specifier_seq>,
			id_t::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1,
			id_t::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2,
			id_t::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3
		>(node),
        find_and_convert_node<declarator, id_t::DECLARATOR>(node),
        find_and_convert_node<boost::optional<ctor_initializer>, id_t::CTOR_INITIALIZER>(node)
    );
}

class_specifier
convert_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CLASS_SPECIFIER);

    return class_specifier
    (
        find_and_convert_node<class_head, id_t::CLASS_HEAD>(node),
        find_and_convert_node<boost::optional<member_specification>, id_t::MEMBER_SPECIFICATION>(node)
    );
}

class_head
convert_class_head(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CLASS_HEAD);

    return class_head
    (
		find_and_convert_node<class_key, id_t::CLASS_KEY>(node),
		find_and_convert_node<boost::optional<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<boost::optional<template_id>, id_t::TEMPLATE_ID>(node),
		find_and_convert_node<boost::optional<identifier>, id_t::IDENTIFIER>(node),
		find_and_convert_node<boost::optional<base_clause>, id_t::BASE_CLAUSE>(node)
    );
}

member_specification
convert_member_specification(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_SPECIFICATION);

    return member_specification
    (
		convert_nodes
		<
			std::vector<member_specification_part>,
			member_specification_part,
			id_t::MEMBER_DECLARATION,
			id_t::MEMBER_SPECIFICATION_ACCESS_SPECIFIER
		>(node)
    );
}

member_specification_access_specifier
convert_member_specification_access_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_SPECIFICATION_ACCESS_SPECIFIER);

    return member_specification_access_specifier
    (
        find_and_convert_node<access_specifier, id_t::ACCESS_SPECIFIER>(node)
    );
}

member_declaration
convert_member_declaration(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION);

	return convert_node
	<
		member_declaration,
		id_t::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST,
		id_t::MEMBER_DECLARATION_UNQUALIFIED_ID,
		id_t::MEMBER_DECLARATION_FUNCTION_DEFINITION,
		id_t::USING_DECLARATION,
		id_t::TEMPLATE_DECLARATION
	>
	(
		get_only_child_node(node)
	);
}

member_declaration_member_declarator_list
convert_member_declaration_member_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST);

    return member_declaration_member_declarator_list
    (
        find_and_convert_node<boost::optional<decl_specifier_seq>, id_t::MEMBER_DECLARATION_DECL_SPECIFIER_SEQ>(node),
        find_and_convert_node<boost::optional<member_declarator_list>, id_t::MEMBER_DECLARATOR_LIST>(node)
    );
}

member_declaration_unqualified_id
convert_member_declaration_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATION_UNQUALIFIED_ID);

    return member_declaration_unqualified_id
    (
        check_node_existence(node, "::", 0),
        find_and_convert_node<nested_name_specifier, id_t::NESTED_NAME_SPECIFIER>(node),
        check_node_existence(node, "template"),
        find_and_convert_node<unqualified_id, id_t::UNQUALIFIED_ID>(node)
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

member_declarator
convert_member_declarator(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATOR);

	return convert_node
	<
		member_declarator,
		id_t::MEMBER_DECLARATOR_DECLARATOR,
		id_t::MEMBER_DECLARATOR_BIT_FIELD_MEMBER
	>
	(
		get_only_child_node(node)
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

member_declarator_bit_field_member
convert_member_declarator_bit_field_member(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEMBER_DECLARATOR_BIT_FIELD_MEMBER);

    return member_declarator_bit_field_member
    (
        find_and_convert_node<boost::optional<identifier>, id_t::IDENTIFIER>(node)
    );
}

base_clause
convert_base_clause(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BASE_CLAUSE);

	boost::optional<base_specifier_list> obs = find_and_convert_node<boost::optional<base_specifier_list>, id_t::BASE_SPECIFIER>(node);
	base_specifier_list bs;
	if(obs)
		bs = *obs;

    //unlike what grammar defines, base specifier may be missing
    return base_clause
    (
		bs
    );
}

base_specifier
convert_base_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::BASE_SPECIFIER);

    return base_specifier
    (
		check_node_existence(node, "virtual"),
		convert_string_enumeration<syntax_tree::access_specifier>
		(
			*find_child_node(node, id_t::ACCESS_SPECIFIER)
		),
		find_and_convert_node<boost::optional<nested_identifier_or_template_id>, id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID>(node)
    );
}

ctor_initializer
convert_ctor_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CTOR_INITIALIZER);

    return ctor_initializer
    (
		find_and_convert_node<mem_initializer_list, id_t::MEM_INITIALIZER_LIST>(node)
    );
}

mem_initializer
convert_mem_initializer(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEM_INITIALIZER);

    return mem_initializer
    (
		find_and_convert_node<mem_initializer_id, id_t::MEM_INITIALIZER_ID>(node)
    );
}

mem_initializer_id
convert_mem_initializer_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::MEM_INITIALIZER_ID);

	return convert_node
	<
		mem_initializer_id,
		id_t::NESTED_IDENTIFIER_OR_TEMPLATE_ID,
		id_t::IDENTIFIER
	>
	(
		get_only_child_node(node)
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

    return template_id
    (
        find_and_convert_node<identifier, id_t::TYPE_NAME>(node),
        find_and_convert_node<template_argument_list, id_t::TEMPLATE_ARGUMENT_LIST>(node)
    );
}

template_argument
convert_template_argument(const tree_node_t& node)
{
    assert(node.value.id() == id_t::TEMPLATE_ARGUMENT);

	return convert_node
	<
		template_argument,
		//id_t::TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION,
		//id_t::TYPE_ID,
		id_t::ID_EXPRESSION
	>
	(
		get_only_child_node(node)
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

elaborated_type_specifier
convert_elaborated_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == id_t::ELABORATED_TYPE_SPECIFIER);

	return elaborated_type_specifier
	(
		find_and_convert_node<boost::optional<class_key>, id_t::CLASS_KEY>(node),
		find_and_convert_node<boost::optional<nested_name_specifier>, id_t::NESTED_NAME_SPECIFIER>(node),
		find_and_convert_node<boost::optional<template_id>, id_t::TEMPLATE_ID>(node),
		find_and_convert_node<boost::optional<identifier>, id_t::IDENTIFIER>(node),
		check_node_existence(node, "::", 1),
		check_node_existence(node, "enum", 0),
		check_node_existence(node, "typename", 0),
		check_node_existence(node, "template")
	);
}

destructor_name
convert_destructor_name(const tree_node_t& node)
{
    assert(node.value.id() == id_t::DESTRUCTOR_NAME);

	return destructor_name(identifier(""));
}

operator_function_id
convert_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::OPERATOR_FUNCTION_ID);

	return operator_function_id();
}

conversion_function_id
convert_conversion_function_id(const tree_node_t& node)
{
    assert(node.value.id() == id_t::CONVERSION_FUNCTION_ID);

	return conversion_function_id();
}

}}} //namespace socoa::cpp

