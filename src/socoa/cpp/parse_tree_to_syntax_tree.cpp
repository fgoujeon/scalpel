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

#include "parse_tree_to_syntax_tree.h"

#include <iostream>
#include <sstream>

#define CONVERT_NODE(type, id)                          \
convert_node<type>                                      \
(                                                       \
    node,                                               \
    grammar::parser_id::id,                             \
    &convert_##type                                     \
)

#define ASSERTED_CONVERT_NODE(type, id)                 \
convert_node<type>                                      \
(                                                       \
    node,                                               \
    grammar::parser_id::id,                             \
    &convert_##type,                                    \
    true                                                \
)

#define CONVERT_SEQUENCE_NODE(type, id)                 \
convert_node<type##_seq>                                \
(                                                       \
    node,                                               \
    grammar::parser_id::id,                             \
    &convert_sequence                                   \
    <                                                   \
        type,                                           \
        &convert_##type,                                \
        util::extern_strings::space                     \
    >                                                   \
)

#define CONVERT_LIST_NODE(type, id)						\
convert_node<type##_list>                               \
(                                                       \
    node,                                               \
    grammar::parser_id::id,                             \
    &convert_sequence                                   \
    <                                                   \
        type,                                           \
        &convert_##type,                                \
        util::extern_strings::comma                     \
    >                                                   \
)

#define CONVERT_STRING_ENUMERATION_NODE(type, id)		\
convert_node<type>										\
(														\
	node,												\
	grammar::parser_id::id,								\
	&convert_string_enumeration<type>,					\
	true												\
)

using namespace boost::spirit;
using namespace socoa::cpp::syntax_tree;
using namespace socoa::util;

namespace socoa { namespace cpp
{

namespace parse_tree_to_syntax_tree
{

syntax_tree_t
convert_tree(const tree_node_t& node)
{
    assert(node.children.size() == 1);
    const tree_node_t& declaration_sequence_node = *node.children.begin();
    assert(declaration_sequence_node.value.id() == grammar::TRANSLATION_UNIT);

	boost::optional<syntax_tree_t> syntax_tree /*= convert_only_child_node
    (
        declaration_sequence_node,
        convert_function_traits<util::sequence<declaration>>::id_function_map_t
        {
            {
                grammar::DECLARATION_SEQ,
                &convert_sequence
                <
                    declaration,
                    &convert_declaration,
                    util::extern_strings::space
                >
            }
        },
        false //the tree may be empty
    );
	assert(syntax_tree)*/;
	return *syntax_tree;
}

identifier
convert_identifier(const tree_node_t& node)
{
    assert
    (
        node.value.id() == grammar::IDENTIFIER ||
        node.value.id() == grammar::TYPE_NAME
    );

    return identifier(get_only_child_value(node));
}

id_expression
convert_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == grammar::ID_EXPRESSION);

    /*return convert_only_child_node<id_expression>
    (
        node,
        convert_function_traits<id_expression>::id_function_map_t
        {
            {grammar::UNQUALIFIED_ID, &convert_unqualified_id},
            {grammar::QUALIFIED_ID, &convert_qualified_id}
        }
    );*/
}

unqualified_id
convert_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::UNQUALIFIED_ID);

    /*return convert_only_child_node<unqualified_id>
    (
        node,
        convert_function_traits<unqualified_id>::id_function_map_t
        {
//            {grammar::OPERATOR_FUNCTION_ID, &convert_identifier},
//            {grammar::CONVERSION_FUNCTION_ID, &convert_nested_name_specifier_template_id_part},
//            {grammar::DESTRUCTOR_NAME, &convert_nested_name_specifier_template_id_part},
            {grammar::TEMPLATE_ID, &convert_template_id},
            {grammar::IDENTIFIER, &convert_identifier}
        },
        false
    );*/
}

qualified_id
convert_qualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_ID);

    /*return convert_only_child_node<qualified_id>
    (
        node,
        convert_function_traits<qualified_id>::id_function_map_t
        {
            {grammar::QUALIFIED_NESTED_ID, &convert_qualified_nested_id},
            {grammar::QUALIFIED_OPERATOR_FUNCTION_ID, &convert_qualified_operator_function_id},
            {grammar::QUALIFIED_TEMPLATE_ID, &convert_qualified_template_id},
            {grammar::QUALIFIED_IDENTIFIER, &convert_qualified_identifier}
        }
    );*/
}

qualified_nested_id
convert_qualified_nested_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_NESTED_ID);

    return qualified_nested_id
    (
		check_node_existence(node, "::", 0),
		*ASSERTED_CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
		check_node_existence(node, "template", 1) || check_node_existence(node, "template", 2),
		*ASSERTED_CONVERT_NODE(unqualified_id, UNQUALIFIED_ID)
    );
}

qualified_operator_function_id
convert_qualified_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_OPERATOR_FUNCTION_ID);

    return qualified_operator_function_id
    (
        //ASSERTED_CONVERT_NODE(operator_function_id, OPERATOR_FUNCTION_ID)
    );
}

qualified_template_id
convert_qualified_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_TEMPLATE_ID);

    return qualified_template_id
    (
        *ASSERTED_CONVERT_NODE(template_id, TEMPLATE_ID)
    );
}

qualified_identifier
convert_qualified_identifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_IDENTIFIER);

    return qualified_identifier
    (
        *ASSERTED_CONVERT_NODE(identifier, IDENTIFIER)
    );
}

nested_name_specifier
convert_nested_name_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER);

    return nested_name_specifier
    (
        ASSERTED_CONVERT_NODE(identifier_or_template_id, IDENTIFIER_OR_TEMPLATE_ID),
        convert_nodes
        (
            node,
            convert_function_traits<nested_name_specifier_part>::id_function_map_t
            {
                {grammar::IDENTIFIER, &convert_identifier},
                {grammar::NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART, &convert_nested_name_specifier_template_id_part}
            }
        )
    );
}

nested_name_specifier_template_id_part
convert_nested_name_specifier_template_id_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART);

    return nested_name_specifier_template_id_part
    (
		check_node_existence(node, "template", 0),
		std::move(*ASSERTED_CONVERT_NODE(template_id, TEMPLATE_ID))
    );
}

declaration
convert_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATION);

    /*return *convert_only_child_node<declaration>
    (
        node,
        convert_function_traits<declaration>::id_function_map_t
        {
            {grammar::BLOCK_DECLARATION, &convert_block_declaration},
            {grammar::FUNCTION_DEFINITION, &convert_function_definition},
            {grammar::TEMPLATE_DECLARATION, &convert_template_declaration},
//            {grammar::EXPLICIT_INSTANTIATION, &},
//            {grammar::EXPLICIT_SPECIALIZATION, &},
//            {grammar::LINKAGE_SPECIFICATION, &},
            {grammar::NAMESPACE_DEFINITION, &convert_namespace_definition}
        },
        false
    );*/
}

block_declaration
convert_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BLOCK_DECLARATION);

    /*return *convert_only_child_node<block_declaration>
    (
        node,
        convert_function_traits<block_declaration>::id_function_map_t
        {
            //{grammar::ASM_DEFINITION, &convert_block_declaration},
            {grammar::SIMPLE_DECLARATION, &convert_simple_declaration},
            //{grammar::NAMESPACE_ALIAS_DEFINITION, &convert_template_declaration},
            {grammar::USING_DECLARATION, &convert_using_declaration},
            {grammar::USING_DIRECTIVE, &convert_using_directive}
        },
        false
    );*/
}

simple_declaration
convert_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_DECLARATION);

    return simple_declaration
    (
		CONVERT_SEQUENCE_NODE(decl_specifier, SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ),
		CONVERT_LIST_NODE(init_declarator, INIT_DECLARATOR_LIST)
    );
}

decl_specifier
convert_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECL_SPECIFIER);

    /*return *convert_only_child_node<decl_specifier>
    (
        node,
        convert_function_traits<decl_specifier>::id_function_map_t
        {
            //{grammar::STORAGE_CLASS_SPECIFIER, &convert_block_declaration));
            {grammar::TYPE_SPECIFIER, &convert_type_specifier}
            //{grammar::FUNCTION_SPECIFIER, &convert_template_declaration));
        },
        false
    );*/
}

type_specifier
convert_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TYPE_SPECIFIER);

    /*return *convert_only_child_node<type_specifier>
    (
        node,
        convert_function_traits<type_specifier>::id_function_map_t
        {
            {grammar::SIMPLE_TYPE_SPECIFIER, &convert_simple_type_specifier},
            {grammar::CLASS_SPECIFIER, &convert_class_specifier},
            //{grammar::ENUM_SPECIFIER, &convert_template_declaration},
            //{grammar::ELABORATED_TYPE_SPECIFIER, &},
            {grammar::CV_QUALIFIER, &convert_cv_qualifier},
            //{grammar::TYPEOF_EXPRESSION, &},,
        },
        false
    );*/
}

simple_type_specifier
convert_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TYPE_SPECIFIER);

    /*return convert_only_child_node<simple_type_specifier>
    (
        node,
        convert_function_traits<simple_type_specifier>::id_function_map_t
        {
            {grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID, &convert_nested_identifier_or_template_id},
            {grammar::SIMPLE_TEMPLATE_TYPE_SPECIFIER, &convert_simple_template_type_specifier},
			{grammar::BUILT_IN_TYPE_SPECIFIER, &convert_string_enumeration<built_in_type_specifier>}
        }
    );*/
}

simple_template_type_specifier
convert_simple_template_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TEMPLATE_TYPE_SPECIFIER);

    return simple_template_type_specifier
	(
		check_node_existence(node, "::", 0),
		*ASSERTED_CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
		*ASSERTED_CONVERT_NODE(template_id, TEMPLATE_ID)
	);
}

identifier_or_template_id
convert_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::IDENTIFIER_OR_TEMPLATE_ID);

    /*return convert_only_child_node<identifier_or_template_id>
    (
        node,
        convert_function_traits<identifier_or_template_id>::id_function_map_t
        {
            {grammar::IDENTIFIER, &convert_identifier},
            {grammar::TEMPLATE_ID, &convert_template_id}
        }
    );*/
}

namespace_definition
convert_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NAMESPACE_DEFINITION);

    return namespace_definition
    (
        CONVERT_NODE(identifier, IDENTIFIER),
        CONVERT_SEQUENCE_NODE(declaration, DECLARATION_SEQ)
    );
}

using_declaration
convert_using_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::USING_DECLARATION);

    return using_declaration
    (
        check_node_existence(node, "typename", 1),
        check_node_existence(node, "::"),
        CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        ASSERTED_CONVERT_NODE(unqualified_id, UNQUALIFIED_ID)
    );
}

using_directive
convert_using_directive(const tree_node_t& node)
{
    assert(node.value.id() == grammar::USING_DIRECTIVE);

    return using_directive
    (
        check_node_existence(node, "::", 2),
        CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        *ASSERTED_CONVERT_NODE(identifier, IDENTIFIER)
    );
}

init_declarator
convert_init_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::INIT_DECLARATOR);

    return init_declarator
    (
		*ASSERTED_CONVERT_NODE(declarator, DECLARATOR)
    );
}

declarator
convert_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR);

    return declarator
    (
		convert_nodes<ptr_operator>
		(
			node,
			grammar::PTR_OPERATOR,
			&convert_ptr_operator
		),
		*ASSERTED_CONVERT_NODE(direct_declarator, DIRECT_DECLARATOR)
    );
}

direct_declarator
convert_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR);

    return direct_declarator
    (
		CONVERT_NODE(declarator_id, DECLARATOR_ID),
		CONVERT_NODE(declarator, DECLARATOR),
		convert_nodes
		(
			node,
			convert_function_traits<direct_declarator_part>::id_function_map_t
			{
				{grammar::DIRECT_DECLARATOR_FUNCTION_PART, &convert_direct_declarator_function_part},
				//{grammar::DIRECT_DECLARATOR_ARRAY_PART, &convert_direct_declarator_array_part},
			}
		)
    );
}

direct_declarator_function_part
convert_direct_declarator_function_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_FUNCTION_PART);

	boost::optional<parameter_declaration_clause> new_parameter_declaration_clause = CONVERT_NODE(parameter_declaration_clause, PARAMETER_DECLARATION_CLAUSE);

    ///@todo why must I do this?
    //grammar defines that this node MUST exist, but in practice it's not always the case
    if(!new_parameter_declaration_clause)
    {
        typedef util::sequence<parameter_declaration, util::extern_strings::comma> parameter_declaration_seq;

        //create an empty parameter declaration clause, if node didn't have been found
        new_parameter_declaration_clause = parameter_declaration_clause
        (
			parameter_declaration_seq(),
			false,
			false
        );
    }

    return direct_declarator_function_part
    (
        *new_parameter_declaration_clause,
        CONVERT_SEQUENCE_NODE(cv_qualifier, CV_QUALIFIER_SEQ)
    );
}

direct_declarator_array_part
convert_direct_declarator_array_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_ARRAY_PART);

    return direct_declarator_array_part();
}

ptr_operator
convert_ptr_operator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PTR_OPERATOR);

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
		CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
		CONVERT_SEQUENCE_NODE(cv_qualifier, CV_QUALIFIER_SEQ)
    );
}

cv_qualifier
convert_cv_qualifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CV_QUALIFIER);

    const std::string value = get_only_child_value(node);
    assert(node.children.size() == 1);
    const tree_node_t child_node = *node.children.begin();
    const parser_id child_id = child_node.value.id();

    //the value is either const, volatile or restrict
    if(value == "const")
        return cv_qualifier(cv_qualifier::CONST);
    else if(value == "volatile")
        return cv_qualifier(cv_qualifier::VOLATILE);
    else if(child_id == grammar::RESTRICT_KEYWORD)
        return cv_qualifier(cv_qualifier::RESTRICT);
    else
    {
        assert(false);
        return cv_qualifier(cv_qualifier::CONST);
    }
}

declarator_id
convert_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR_ID);

    /*return convert_only_child_node<declarator_id>
    (
        node,
        convert_function_traits<declarator_id>::id_function_map_t
        {
            {grammar::ID_EXPRESSION, &convert_id_expression},
            {grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID, &convert_nested_identifier_or_template_id}
        }
    );*/
}

parameter_declaration_clause
convert_parameter_declaration_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION_CLAUSE);

    bool trailing_comma = check_node_existence(node, ",", 1);
    bool ellipsis = check_node_existence(node, "...");

    if(trailing_comma) assert(ellipsis);

    return parameter_declaration_clause
    (
        parameter_declaration_clause
        {
            CONVERT_LIST_NODE(parameter_declaration, PARAMETER_DECLARATION_LIST),
            trailing_comma,
            ellipsis
        }
    );
}

///@todo factorize it
parameter_declaration
convert_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION);

    util::sequence<decl_specifier> new_decl_specifier_seq;

    //get sequence<decl_specifier> node
    const tree_node_t& decl_specifier_seq_node = *node.children.begin();
    parser_id decl_specifier_seq_node_id = decl_specifier_seq_node.value.id();
    assert
    (
        decl_specifier_seq_node_id == grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ1 ||
        decl_specifier_seq_node_id == grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ2 ||
        decl_specifier_seq_node_id == grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ3 ||
        decl_specifier_seq_node_id == grammar::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ4 ||
        decl_specifier_seq_node_id == grammar::DECL_SPECIFIER_SEQ
    );
    new_decl_specifier_seq = convert_sequence
    <
        decl_specifier,
        &convert_decl_specifier,
        util::extern_strings::space
    >(decl_specifier_seq_node);

    return parameter_declaration
    (
		new_decl_specifier_seq,
		CONVERT_NODE(declarator, DECLARATOR),
		false
    );
}

///@todo factorize it
function_definition
convert_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::FUNCTION_DEFINITION);

    //find decl_specifier_seq node...
    const tree_node_t* decl_specifier_seq_node;
    decl_specifier_seq_node = find_child_node(node, grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1);
    if(!decl_specifier_seq_node)
        decl_specifier_seq_node = find_child_node(node, grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2);
    if(!decl_specifier_seq_node)
        decl_specifier_seq_node = find_child_node(node, grammar::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3);

    //... and evaluate it
    util::sequence<decl_specifier> new_decl_specifier_seq;
    if(decl_specifier_seq_node)
    {
        new_decl_specifier_seq = convert_sequence
        <
            decl_specifier,
            &convert_decl_specifier,
            util::extern_strings::space
        >(*decl_specifier_seq_node);
    }

    //create function definition object
    return function_definition
    (
        new_decl_specifier_seq,
        *ASSERTED_CONVERT_NODE(declarator, DECLARATOR),
        CONVERT_NODE(ctor_initializer, CTOR_INITIALIZER)
    );
}

class_specifier
convert_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_SPECIFIER);

    return class_specifier
    (
        *ASSERTED_CONVERT_NODE(class_head, CLASS_HEAD),
        CONVERT_NODE(member_specification, MEMBER_SPECIFICATION)
    );
}

class_head
convert_class_head(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_HEAD);

    return class_head
    (
		*CONVERT_STRING_ENUMERATION_NODE(class_key, CLASS_KEY),
		CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
		CONVERT_NODE(template_id, TEMPLATE_ID),
		CONVERT_NODE(identifier, IDENTIFIER),
		CONVERT_NODE(base_clause, BASE_CLAUSE)
    );
}

member_specification
convert_member_specification(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION);

    return member_specification
    (
		convert_nodes
		(
			node,
			convert_function_traits<member_specification_part>::id_function_map_t
			{
				{grammar::MEMBER_DECLARATION, &convert_member_declaration},
				{grammar::MEMBER_SPECIFICATION_ACCESS_SPECIFIER, &convert_member_specification_access_specifier}
			}
		)
    );
}

member_specification_access_specifier
convert_member_specification_access_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION_ACCESS_SPECIFIER);

    return member_specification_access_specifier
    (
        *CONVERT_STRING_ENUMERATION_NODE(access_specifier, ACCESS_SPECIFIER)
    );
}

member_declaration
convert_member_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION);

    /*return convert_only_child_node<member_declaration>
    (
        node,
        convert_function_traits<member_declaration>::id_function_map_t
        {
            {grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST, &convert_member_declaration_member_declarator_list},
            {grammar::MEMBER_DECLARATION_UNQUALIFIED_ID, &convert_member_declaration_unqualified_id},
            {grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION, &convert_member_declaration_function_definition},
            {grammar::USING_DECLARATION, &convert_using_declaration},
            {grammar::TEMPLATE_DECLARATION, &convert_template_declaration}
        }
    );*/
}

member_declaration_member_declarator_list
convert_member_declaration_member_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST);

    return member_declaration_member_declarator_list
    (
        CONVERT_SEQUENCE_NODE(decl_specifier, MEMBER_DECLARATION_DECL_SPECIFIER_SEQ),
        CONVERT_LIST_NODE(member_declarator, MEMBER_DECLARATOR_LIST)
    );
}

member_declaration_unqualified_id
convert_member_declaration_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_UNQUALIFIED_ID);

    return member_declaration_unqualified_id
    (
        check_node_existence(node, "::", 0),
        *ASSERTED_CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        check_node_existence(node, "template"),
        *ASSERTED_CONVERT_NODE(unqualified_id, UNQUALIFIED_ID)
    );
}

member_declaration_function_definition
convert_member_declaration_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION);

    return member_declaration_function_definition
    (
        *ASSERTED_CONVERT_NODE(function_definition, FUNCTION_DEFINITION)
    );
}

member_declarator
convert_member_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR);

    /*return convert_only_child_node<member_declarator>
    (
        node,
        convert_function_traits<member_declarator>::id_function_map_t
        {
            {grammar::MEMBER_DECLARATOR_DECLARATOR, &convert_member_declarator_declarator},
            {grammar::MEMBER_DECLARATOR_BIT_FIELD_MEMBER, &convert_member_declarator_bit_field_member}
        }
    );*/
}

member_declarator_declarator
convert_member_declarator_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR_DECLARATOR);

    return member_declarator_declarator
    (
        *ASSERTED_CONVERT_NODE(declarator, DECLARATOR),
        check_node_existence(node, grammar::PURE_SPECIFIER, 1)
    );
}

member_declarator_bit_field_member
convert_member_declarator_bit_field_member(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR_BIT_FIELD_MEMBER);

    return member_declarator_bit_field_member
    (
        CONVERT_NODE(identifier, IDENTIFIER)
    );
}

base_clause
convert_base_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BASE_CLAUSE);

    //unlike what grammar defines, base specifier may be missing
    return base_clause
    (
		*CONVERT_LIST_NODE(base_specifier, BASE_SPECIFIER)
    );
}

base_specifier
convert_base_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BASE_SPECIFIER);

    return base_specifier
    (
		check_node_existence(node, "virtual"),
		convert_string_enumeration<syntax_tree::access_specifier>
		(
			*find_child_node(node, grammar::ACCESS_SPECIFIER)
		),
		CONVERT_NODE(nested_identifier_or_template_id, NESTED_IDENTIFIER_OR_TEMPLATE_ID)
    );
}

ctor_initializer
convert_ctor_initializer(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CTOR_INITIALIZER);

    return ctor_initializer
    (
		*CONVERT_LIST_NODE(mem_initializer, MEM_INITIALIZER_LIST)
    );
}

mem_initializer
convert_mem_initializer(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEM_INITIALIZER);

    return mem_initializer
    (
		*ASSERTED_CONVERT_NODE(mem_initializer_id, MEM_INITIALIZER_ID)
    );
}

mem_initializer_id
convert_mem_initializer_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEM_INITIALIZER_ID);

    /*return convert_only_child_node<mem_initializer_id>
    (
        node,
        convert_function_traits<mem_initializer_id>::id_function_map_t
        {
            {grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID, &convert_nested_identifier_or_template_id},
            {grammar::IDENTIFIER, &convert_identifier}
        }
    );*/
}

template_declaration
convert_template_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_DECLARATION);

    return template_declaration
    (
        check_node_existence(node, "export", 0),
        *ASSERTED_CONVERT_NODE(declaration, DECLARATION)
    );
}

template_id
convert_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ID);

    return template_id
    (
        *ASSERTED_CONVERT_NODE(identifier, TYPE_NAME),
        CONVERT_LIST_NODE(template_argument, TEMPLATE_ARGUMENT_LIST)
    );
}

template_argument
convert_template_argument(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ARGUMENT);

    /*return *convert_only_child_node<template_argument>
    (
        node,
        convert_function_traits<template_argument>::id_function_map_t
        {
            //{grammar::TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION, &convert_assignment_expression},
            //{grammar::TYPE_ID, &convert_type_id},
            {grammar::ID_EXPRESSION, &convert_id_expression}
        },
        false
    );*/
}

nested_identifier_or_template_id
convert_nested_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID);

    return nested_identifier_or_template_id
    (
        check_node_existence(node, "::", 0),
        CONVERT_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        *ASSERTED_CONVERT_NODE(identifier_or_template_id, IDENTIFIER_OR_TEMPLATE_ID)
    );
}


const tree_node_t*
find_child_node(const tree_node_t& parent_node, grammar::parser_id child_id)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        boost::spirit::parser_id id = child_node.value.id();
        if(id == child_id)
        {
            return &child_node;
        }
    }

    return 0;
}

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position)
{
    if(parent_node.children.size() <= position)
        return false;

    return get_value(parent_node.children[position]) == value;
}

bool
check_node_existence(const tree_node_t& parent_node, const std::string& value)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        if(get_value(child_node) == value)
        {
            return true;
        }
    }

    return false;
}

bool
check_node_existence
(
    const tree_node_t& parent_node,
    const grammar::parser_id id,
    unsigned int position
)
{
    if(parent_node.children.size() <= position)
        return false;

    return parent_node.children[position].value.id() == id;
}

bool
check_node_existence
(
    const tree_node_t& parent_node,
    const grammar::parser_id id
)
{
    for
    (
        tree_node_iterator_t i = parent_node.children.begin();
        i != parent_node.children.end();
        ++i
    ) //for each child
    {
        const tree_node_t& child_node = *i;
        const parser_id child_id = child_node.value.id();

        if(child_id == id)
        {
            return true;
        }
    }

    return false;
}

std::string
get_only_child_value(const tree_node_t& node)
{
    assert(node.children.size() == 1);

    //get child node
    const tree_node_t& child_node = *node.children.begin();

    return get_value(child_node);
}

std::string
get_value(const tree_node_t& node)
{
    //get value
    std::ostringstream value_oss;
    for
    (
        tree_node_value_iterator_t i = node.value.begin();
        i != node.value.end();
        ++i
    ) //iterate node value
    {
        value_oss << *i;
    }

    return strip_redundant_spaces(value_oss.str());
}

std::string
strip_redundant_spaces(const std::string& str)
{
    std::string result;

    bool skip = true;
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        const char c = str[i];

        if(c == ' ' || c == '\t' || c == '\n')
        {
            if(!skip)
            {
                result += ' ';
                skip = true;
            }
        }
        else
        {
            result += c;
            skip = false;
        }
    }

    return result;
}

int
get_id(const tree_node_t& node)
{
    boost::spirit::parser_id id = node.value.id();

    for(unsigned int i = 0; i < 400; ++i)
    {
        if(id == i)
        {
            return i;
        }
    }

    return -1;
}

}

}} //namespace socoa::cpp

#undef CONVERT_NODE
#undef ASSERTED_CONVERT_NODE
#undef CONVERT_SEQUENCE_NODE
#undef CONVERT_LIST_NODE