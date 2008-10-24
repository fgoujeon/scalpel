/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

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

#include "syntax_analyzer.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include "grammar.h"

#define EVALUATE_NODE(type, id)                         \
evaluate_node                                           \
(                                                       \
    node,                                               \
    grammar::id,                                        \
    &syntax_analyzer::evaluate_##type                   \
)

#define ASSERTED_EVALUATE_NODE(type, id)                \
evaluate_node                                           \
(                                                       \
    node,                                               \
    grammar::id,                                        \
    &syntax_analyzer::evaluate_##type,                  \
    true                                                \
)

#define EVALUATE_SEQUENCE_NODE(type, id)                \
evaluate_node                                           \
(                                                       \
    node,                                               \
    grammar::id,                                        \
    &syntax_analyzer::evaluate_sequence                 \
    <                                                   \
        type,                                           \
        &syntax_analyzer::evaluate_##type,              \
        util::extern_strings::space                                     \
    >                                                   \
)

#define EVALUATE_SEPARATED_SEQUENCE_NODE(type, id, separator)       \
evaluate_node                                                       \
(                                                                   \
    node,                                                           \
    grammar::id,                                                    \
    &syntax_analyzer::evaluate_sequence                             \
    <                                                               \
        type,                                                       \
        &syntax_analyzer::evaluate_##type,                          \
        separator                                                   \
    >                                                               \
)

using namespace boost::spirit;
using namespace socoa::cpp::program_syntax_tree;
using namespace socoa::util;

namespace socoa { namespace cpp
{

syntax_analyzer::syntax_analyzer():
    grammar_(grammar_configuration_)
{
    grammar_configuration_.skip_function_bodies = true;
}

std::shared_ptr<util::sequence<declaration>>
syntax_analyzer::operator()(const std::string& input)
{
    //reset grammar
    grammar_.reset();

    //parse the input with the C++ grammar
    tree_parse_info<> info = pt_parse(input.c_str(), grammar_.use_parser<grammar::START_FILE>(), space_p);

    //throw an exception if parsing fails
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    //declare a new sequence<declaration> object and populate it
    const tree_node_t& root_node = *info.trees.begin();
    const tree_node_t& translation_unit_node = *root_node.children.begin();

    return evaluate_translation_unit(translation_unit_node);
}

std::shared_ptr<util::sequence<declaration>>
syntax_analyzer::evaluate_translation_unit(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TRANSLATION_UNIT);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<util::sequence<declaration>>::id_function_map_t
        {
            {
                grammar::DECLARATION_SEQ,
                &syntax_analyzer::evaluate_sequence
                <
                    declaration,
                    &syntax_analyzer::evaluate_declaration,
                    util::extern_strings::space
                >
            }
        }
    );
}

std::shared_ptr<identifier>
syntax_analyzer::evaluate_identifier(const tree_node_t& node)
{
    assert
    (
        node.value.id() == grammar::IDENTIFIER ||
        node.value.id() == grammar::TYPE_NAME
    );

    return std::make_shared<identifier>(get_only_child_value(node));
}

std::shared_ptr<id_expression>
syntax_analyzer::evaluate_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == grammar::ID_EXPRESSION);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<id_expression>::id_function_map_t
        {
            {grammar::UNQUALIFIED_ID, &syntax_analyzer::evaluate_unqualified_id},
            {grammar::QUALIFIED_ID, &syntax_analyzer::evaluate_qualified_id}
        }
    );
}

std::shared_ptr<unqualified_id>
syntax_analyzer::evaluate_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::UNQUALIFIED_ID);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<unqualified_id>::id_function_map_t
        {
//            {grammar::OPERATOR_FUNCTION_ID, &syntax_analyzer::evaluate_identifier},
//            {grammar::CONVERSION_FUNCTION_ID, &syntax_analyzer::evaluate_nested_name_specifier_template_id_part},
//            {grammar::DESTRUCTOR_NAME, &syntax_analyzer::evaluate_nested_name_specifier_template_id_part},
            {grammar::TEMPLATE_ID, &syntax_analyzer::evaluate_template_id},
            {grammar::IDENTIFIER, &syntax_analyzer::evaluate_identifier}
        },
        false
    );
}

std::shared_ptr<qualified_id>
syntax_analyzer::evaluate_qualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_ID);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<qualified_id>::id_function_map_t
        {
            {grammar::QUALIFIED_NESTED_ID, &syntax_analyzer::evaluate_qualified_nested_id},
            {grammar::QUALIFIED_OPERATOR_FUNCTION_ID, &syntax_analyzer::evaluate_qualified_operator_function_id},
            {grammar::QUALIFIED_TEMPLATE_ID, &syntax_analyzer::evaluate_qualified_template_id},
            {grammar::QUALIFIED_IDENTIFIER, &syntax_analyzer::evaluate_qualified_identifier}
        }
    );
}

std::shared_ptr<qualified_nested_id>
syntax_analyzer::evaluate_qualified_nested_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_NESTED_ID);

    return std::make_shared<qualified_nested_id>
    (
        check_node_existence(node, "::", 0),
        *ASSERTED_EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        check_node_existence(node, "template", 1) || check_node_existence(node, "template", 2),
        ASSERTED_EVALUATE_NODE(unqualified_id, UNQUALIFIED_ID)
    );
}

std::shared_ptr<qualified_operator_function_id>
syntax_analyzer::evaluate_qualified_operator_function_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_OPERATOR_FUNCTION_ID);

    return std::make_shared<qualified_operator_function_id>
    (
        //ASSERTED_EVALUATE_NODE(operator_function_id, OPERATOR_FUNCTION_ID)
    );
}

std::shared_ptr<qualified_template_id>
syntax_analyzer::evaluate_qualified_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_TEMPLATE_ID);

    return std::make_shared<qualified_template_id>
    (
        *ASSERTED_EVALUATE_NODE(template_id, TEMPLATE_ID)
    );
}

std::shared_ptr<qualified_identifier>
syntax_analyzer::evaluate_qualified_identifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::QUALIFIED_IDENTIFIER);

    return std::make_shared<qualified_identifier>
    (
        *ASSERTED_EVALUATE_NODE(identifier, IDENTIFIER)
    );
}

std::shared_ptr<nested_name_specifier>
syntax_analyzer::evaluate_nested_name_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER);

    nested_name_specifier item
    {
        ASSERTED_EVALUATE_NODE(identifier_or_template_id, IDENTIFIER_OR_TEMPLATE_ID),
        evaluate_nodes
        (
            node,
            evaluate_function_typedefs<nested_name_specifier_part>::id_function_map_t
            {
                {grammar::IDENTIFIER, &syntax_analyzer::evaluate_identifier},
                {grammar::NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART, &syntax_analyzer::evaluate_nested_name_specifier_template_id_part}
            }
        )
    };

    return std::shared_ptr<nested_name_specifier>
    (
        new nested_name_specifier(item)
    );
}

std::shared_ptr<nested_name_specifier_template_id_part>
syntax_analyzer::evaluate_nested_name_specifier_template_id_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART);

    return std::make_shared<nested_name_specifier_template_id_part>
    (
        check_node_existence(node, "template", 0),
        std::move(*ASSERTED_EVALUATE_NODE(template_id, TEMPLATE_ID))
    );
}

std::shared_ptr<declaration>
syntax_analyzer::evaluate_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATION);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<declaration>::id_function_map_t
        {
            {grammar::BLOCK_DECLARATION, &syntax_analyzer::evaluate_block_declaration},
            {grammar::FUNCTION_DEFINITION, &syntax_analyzer::evaluate_function_definition},
            {grammar::TEMPLATE_DECLARATION, &syntax_analyzer::evaluate_template_declaration},
//            {grammar::EXPLICIT_INSTANTIATION, &syntax_analyzer::},
//            {grammar::EXPLICIT_SPECIALIZATION, &syntax_analyzer::},
//            {grammar::LINKAGE_SPECIFICATION, &syntax_analyzer::},
            {grammar::NAMESPACE_DEFINITION, &syntax_analyzer::evaluate_namespace_definition}
        },
        false
    );
}

std::shared_ptr<declaration>
syntax_analyzer::evaluate_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BLOCK_DECLARATION);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<declaration>::id_function_map_t
        {
            //{grammar::ASM_DEFINITION, &syntax_analyzer::evaluate_block_declaration},
            {grammar::SIMPLE_DECLARATION, &syntax_analyzer::evaluate_simple_declaration},
            //{grammar::NAMESPACE_ALIAS_DEFINITION, &syntax_analyzer::evaluate_template_declaration},
            {grammar::USING_DECLARATION, &syntax_analyzer::evaluate_using_declaration},
            {grammar::USING_DIRECTIVE, &syntax_analyzer::evaluate_using_directive}
        },
        false
    );
}

std::shared_ptr<simple_declaration>
syntax_analyzer::evaluate_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_DECLARATION);

    return std::make_shared<simple_declaration>
    (
        EVALUATE_SEQUENCE_NODE(decl_specifier, SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ),
        EVALUATE_SEPARATED_SEQUENCE_NODE(init_declarator, INIT_DECLARATOR_LIST, util::extern_strings::comma)
    );
}

std::shared_ptr<decl_specifier>
syntax_analyzer::evaluate_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECL_SPECIFIER);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<decl_specifier>::id_function_map_t
        {
            //{grammar::STORAGE_CLASS_SPECIFIER, &syntax_analyzer::evaluate_block_declaration));
            {grammar::TYPE_SPECIFIER, &syntax_analyzer::evaluate_type_specifier}
            //{grammar::FUNCTION_SPECIFIER, &syntax_analyzer::evaluate_template_declaration));
        },
        false
    );
}

std::shared_ptr<type_specifier>
syntax_analyzer::evaluate_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TYPE_SPECIFIER);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<type_specifier>::id_function_map_t
        {
            {grammar::SIMPLE_TYPE_SPECIFIER, &syntax_analyzer::evaluate_simple_type_specifier},
            {grammar::CLASS_SPECIFIER, &syntax_analyzer::evaluate_class_specifier},
            //{grammar::ENUM_SPECIFIER, &syntax_analyzer::evaluate_template_declaration},
            //{grammar::ELABORATED_TYPE_SPECIFIER, &syntax_analyzer::},
            {grammar::CV_QUALIFIER, &syntax_analyzer::evaluate_cv_qualifier},
            //{grammar::TYPEOF_EXPRESSION, &syntax_analyzer::},,
        },
        false
    );
}

std::shared_ptr<simple_type_specifier>
syntax_analyzer::evaluate_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TYPE_SPECIFIER);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<simple_type_specifier>::id_function_map_t
        {
            {grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID, &syntax_analyzer::evaluate_nested_identifier_or_template_id},
            {grammar::SIMPLE_TEMPLATE_TYPE_SPECIFIER, &syntax_analyzer::evaluate_simple_template_type_specifier},
            {grammar::BUILT_IN_TYPE_SPECIFIER, &syntax_analyzer::evaluate_keyword_enumeration<built_in_type_specifier>}
        }
    );
}

std::shared_ptr<simple_template_type_specifier>
syntax_analyzer::evaluate_simple_template_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TEMPLATE_TYPE_SPECIFIER);

    return std::make_shared<simple_template_type_specifier>
    (
        check_node_existence(node, "::", 0),
        ASSERTED_EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        ASSERTED_EVALUATE_NODE(template_id, TEMPLATE_ID)
    );
}

std::shared_ptr<identifier_or_template_id>
syntax_analyzer::evaluate_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::IDENTIFIER_OR_TEMPLATE_ID);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<identifier_or_template_id>::id_function_map_t
        {
            {grammar::IDENTIFIER, &syntax_analyzer::evaluate_identifier},
            {grammar::TEMPLATE_ID, &syntax_analyzer::evaluate_template_id}
        }
    );
}

std::shared_ptr<namespace_definition>
syntax_analyzer::evaluate_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NAMESPACE_DEFINITION);

    return std::make_shared<namespace_definition>
    (
        EVALUATE_NODE(identifier, IDENTIFIER),
        EVALUATE_SEQUENCE_NODE(declaration, DECLARATION_SEQ)
    );
}

std::shared_ptr<using_declaration>
syntax_analyzer::evaluate_using_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::USING_DECLARATION);

    return std::make_shared<using_declaration>
    (
        check_node_existence(node, "typename", 1),
        check_node_existence(node, "::"),
        EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        ASSERTED_EVALUATE_NODE(unqualified_id, UNQUALIFIED_ID)
    );
}

std::shared_ptr<using_directive>
syntax_analyzer::evaluate_using_directive(const tree_node_t& node)
{
    assert(node.value.id() == grammar::USING_DIRECTIVE);

    return std::make_shared<using_directive>
    (
        check_node_existence(node, "::", 2),
        EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        *ASSERTED_EVALUATE_NODE(identifier, IDENTIFIER)
    );
}

std::shared_ptr<init_declarator>
syntax_analyzer::evaluate_init_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::INIT_DECLARATOR);

    return std::make_shared<init_declarator>
    (
        init_declarator
        {
            *ASSERTED_EVALUATE_NODE(declarator, DECLARATOR)
        }
    );
}

std::shared_ptr<declarator>
syntax_analyzer::evaluate_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR);

    return std::make_shared<declarator>
    (
        declarator
        {
            std::move
            (
                evaluate_nodes
                (
                    node,
                    grammar::PTR_OPERATOR,
                    &syntax_analyzer::evaluate_ptr_operator
                )
            ),
            *ASSERTED_EVALUATE_NODE(direct_declarator, DIRECT_DECLARATOR)
        }
    );
}

std::shared_ptr<direct_declarator>
syntax_analyzer::evaluate_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR);

    return std::make_shared<direct_declarator>
    (
        direct_declarator
        {
            EVALUATE_NODE(declarator_id, DECLARATOR_ID),
            EVALUATE_NODE(declarator, DECLARATOR),
            evaluate_nodes
            (
                node,
                evaluate_function_typedefs<direct_declarator_part>::id_function_map_t
                {
                    {grammar::DIRECT_DECLARATOR_FUNCTION_PART, &syntax_analyzer::evaluate_direct_declarator_function_part},
                    //{grammar::DIRECT_DECLARATOR_ARRAY_PART, &syntax_analyzer::evaluate_direct_declarator_array_part},
                }
            )
        }
    );
}

std::shared_ptr<direct_declarator_function_part>
syntax_analyzer::evaluate_direct_declarator_function_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_FUNCTION_PART);

    std::shared_ptr<parameter_declaration_clause> new_parameter_declaration_clause = EVALUATE_NODE(parameter_declaration_clause, PARAMETER_DECLARATION_CLAUSE);

    ///@todo why must I do this?
    //grammar defines that this node MUST exist, but in practice it's not always the case
    if(!new_parameter_declaration_clause)
    {
        typedef util::sequence<parameter_declaration, util::extern_strings::comma> parameter_declaration_seq;

        //create an empty parameter declaration clause, if node didn't have been found
        new_parameter_declaration_clause = std::make_shared<parameter_declaration_clause>
        (
            parameter_declaration_clause
            {
                std::shared_ptr<parameter_declaration_seq>(),
                false,
                false
            }
        );
    }

    return std::make_shared<direct_declarator_function_part>
    (
        *new_parameter_declaration_clause,
        EVALUATE_SEQUENCE_NODE(cv_qualifier, CV_QUALIFIER_SEQ)
    );
}

std::shared_ptr<direct_declarator_array_part>
syntax_analyzer::evaluate_direct_declarator_array_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_ARRAY_PART);

    return std::shared_ptr<direct_declarator_array_part>();
}

std::shared_ptr<ptr_operator>
syntax_analyzer::evaluate_ptr_operator(const tree_node_t& node)
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

    return std::make_shared<ptr_operator>
    (
        ptr_operator
        {
            check_node_existence(node, "*") ? ptr_operator::ASTERISK : ptr_operator::AMPERSAND,
            check_node_existence(node, "::", 0),
            EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
            EVALUATE_SEQUENCE_NODE(cv_qualifier, CV_QUALIFIER_SEQ)
        }
    );
}

std::shared_ptr<cv_qualifier>
syntax_analyzer::evaluate_cv_qualifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CV_QUALIFIER);

    const std::string value = get_only_child_value(node);
    assert(node.children.size() == 1);
    const tree_node_t child_node = *node.children.begin();
    const parser_id child_id = child_node.value.id();

    //the value is either const, volatile or restrict
    if(value == "const")
        return std::make_shared<cv_qualifier>(cv_qualifier::CONST);
    else if(value == "volatile")
        return std::make_shared<cv_qualifier>(cv_qualifier::VOLATILE);
    else if(child_id == grammar::RESTRICT_KEYWORD)
        return std::make_shared<cv_qualifier>(cv_qualifier::RESTRICT);
    else
    {
        assert(false);
        return std::shared_ptr<cv_qualifier>();
    }
}

std::shared_ptr<declarator_id>
syntax_analyzer::evaluate_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR_ID);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<declarator_id>::id_function_map_t
        {
            {grammar::ID_EXPRESSION, &syntax_analyzer::evaluate_id_expression},
            {grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID, &syntax_analyzer::evaluate_nested_identifier_or_template_id}
        }
    );
}

std::shared_ptr<parameter_declaration_clause>
syntax_analyzer::evaluate_parameter_declaration_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION_CLAUSE);

    bool trailing_comma = check_node_existence(node, ",", 1);
    bool ellipsis = check_node_existence(node, "...");

    if(trailing_comma) assert(ellipsis);

    return std::make_shared<parameter_declaration_clause>
    (
        parameter_declaration_clause
        {
            EVALUATE_SEPARATED_SEQUENCE_NODE(parameter_declaration, PARAMETER_DECLARATION_LIST, util::extern_strings::comma),
            trailing_comma,
            ellipsis
        }
    );
}

///@todo factorize it
std::shared_ptr<parameter_declaration>
syntax_analyzer::evaluate_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION);

    std::shared_ptr<util::sequence<decl_specifier>> new_decl_specifier_seq;
    std::shared_ptr<declarator> new_declarator;

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
    new_decl_specifier_seq = evaluate_sequence
    <
        decl_specifier,
        &syntax_analyzer::evaluate_decl_specifier,
        util::extern_strings::space
    >(decl_specifier_seq_node);

    return std::make_shared<parameter_declaration>
    (
        parameter_declaration
        {
            *new_decl_specifier_seq,
            EVALUATE_NODE(declarator, DECLARATOR),
            false
        }
    );
}

///@todo factorize it
std::shared_ptr<function_definition>
syntax_analyzer::evaluate_function_definition(const tree_node_t& node)
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
    std::shared_ptr<util::sequence<decl_specifier>> new_decl_specifier_seq;
    if(decl_specifier_seq_node)
    {
        new_decl_specifier_seq = evaluate_sequence
        <
            decl_specifier,
            &syntax_analyzer::evaluate_decl_specifier,
            util::extern_strings::space
        >(*decl_specifier_seq_node);
    }

    //create function definition object
    return std::make_shared<function_definition>
    (
        new_decl_specifier_seq,
        *ASSERTED_EVALUATE_NODE(declarator, DECLARATOR),
        EVALUATE_NODE(ctor_initializer, CTOR_INITIALIZER)
    );
}

std::shared_ptr<class_specifier>
syntax_analyzer::evaluate_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_SPECIFIER);

    return std::make_shared<class_specifier>
    (
        *ASSERTED_EVALUATE_NODE(class_head, CLASS_HEAD),
        EVALUATE_NODE(member_specification, MEMBER_SPECIFICATION)
    );
}

std::shared_ptr<class_head>
syntax_analyzer::evaluate_class_head(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_HEAD);

    return std::make_shared<class_head>
    (
        class_head
        {
            *ASSERTED_EVALUATE_NODE(keyword_enumeration<class_key>, CLASS_KEY),
            EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
            EVALUATE_NODE(template_id, TEMPLATE_ID),
            EVALUATE_NODE(identifier, IDENTIFIER)
        }
    );
}

std::shared_ptr<member_specification>
syntax_analyzer::evaluate_member_specification(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION);

    return std::make_shared<member_specification>
    (
        member_specification
        {
            evaluate_nodes
            (
                node,
                evaluate_function_typedefs<member_specification_part>::id_function_map_t
                {
                    {grammar::MEMBER_DECLARATION, &syntax_analyzer::evaluate_member_declaration},
                    {grammar::MEMBER_SPECIFICATION_ACCESS_SPECIFIER, &syntax_analyzer::evaluate_member_specification_access_specifier}
                }
            )
        }
    );
}

std::shared_ptr<member_specification_access_specifier>
syntax_analyzer::evaluate_member_specification_access_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION_ACCESS_SPECIFIER);

    return std::make_shared<member_specification_access_specifier>
    (
        *ASSERTED_EVALUATE_NODE(keyword_enumeration<access_specifier>, ACCESS_SPECIFIER)
    );
}

std::shared_ptr<member_declaration>
syntax_analyzer::evaluate_member_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<member_declaration>::id_function_map_t
        {
            {grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST, &syntax_analyzer::evaluate_member_declaration_member_declarator_list},
            {grammar::MEMBER_DECLARATION_UNQUALIFIED_ID, &syntax_analyzer::evaluate_member_declaration_unqualified_id},
            {grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION, &syntax_analyzer::evaluate_member_declaration_function_definition},
            {grammar::USING_DECLARATION, &syntax_analyzer::evaluate_using_declaration},
            {grammar::TEMPLATE_DECLARATION, &syntax_analyzer::evaluate_template_declaration}
        }
    );
}

std::shared_ptr<member_declaration_member_declarator_list>
syntax_analyzer::evaluate_member_declaration_member_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST);

    return std::make_shared<member_declaration_member_declarator_list>
    (
        EVALUATE_SEQUENCE_NODE(decl_specifier, MEMBER_DECLARATION_DECL_SPECIFIER_SEQ),
        EVALUATE_SEPARATED_SEQUENCE_NODE(member_declarator, MEMBER_DECLARATOR_LIST, util::extern_strings::comma)
    );
}

std::shared_ptr<member_declaration_unqualified_id>
syntax_analyzer::evaluate_member_declaration_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_UNQUALIFIED_ID);

    return std::make_shared<member_declaration_unqualified_id>
    (
        check_node_existence(node, "::", 0),
        *ASSERTED_EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        check_node_existence(node, "template"),
        EVALUATE_NODE(unqualified_id, UNQUALIFIED_ID)
    );
}

std::shared_ptr<member_declaration_function_definition>
syntax_analyzer::evaluate_member_declaration_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION);

    return std::make_shared<member_declaration_function_definition>
    (
        *ASSERTED_EVALUATE_NODE(function_definition, FUNCTION_DEFINITION)
    );
}

std::shared_ptr<member_declarator>
syntax_analyzer::evaluate_member_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<member_declarator>::id_function_map_t
        {
            {grammar::MEMBER_DECLARATOR_DECLARATOR, &syntax_analyzer::evaluate_member_declarator_declarator},
            {grammar::MEMBER_DECLARATOR_BIT_FIELD_MEMBER, &syntax_analyzer::evaluate_member_declarator_bit_field_member}
        }
    );
}

std::shared_ptr<member_declarator_declarator>
syntax_analyzer::evaluate_member_declarator_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR_DECLARATOR);

    return std::make_shared<member_declarator_declarator>
    (
        ASSERTED_EVALUATE_NODE(declarator, DECLARATOR),
        check_node_existence(node, grammar::PURE_SPECIFIER, 1)
    );
}

std::shared_ptr<member_declarator_bit_field_member>
syntax_analyzer::evaluate_member_declarator_bit_field_member(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATOR_BIT_FIELD_MEMBER);

    return std::make_shared<member_declarator_bit_field_member>
    (
        EVALUATE_NODE(identifier, IDENTIFIER)
    );
}

std::shared_ptr<ctor_initializer>
syntax_analyzer::evaluate_ctor_initializer(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CTOR_INITIALIZER);

    return std::make_shared<ctor_initializer>
    (
        ctor_initializer
        {
            *EVALUATE_SEPARATED_SEQUENCE_NODE(mem_initializer, MEM_INITIALIZER_LIST, util::extern_strings::comma)
        }
    );
}

std::shared_ptr<mem_initializer>
syntax_analyzer::evaluate_mem_initializer(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEM_INITIALIZER);

    return std::make_shared<mem_initializer>
    (
        mem_initializer
        {
            ASSERTED_EVALUATE_NODE(mem_initializer_id, MEM_INITIALIZER_ID)
        }
    );
}

std::shared_ptr<mem_initializer_id>
syntax_analyzer::evaluate_mem_initializer_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEM_INITIALIZER_ID);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<mem_initializer_id>::id_function_map_t
        {
            {grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID, &syntax_analyzer::evaluate_nested_identifier_or_template_id},
            {grammar::IDENTIFIER, &syntax_analyzer::evaluate_identifier}
        }
    );
}

std::shared_ptr<template_declaration>
syntax_analyzer::evaluate_template_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_DECLARATION);

    return std::make_shared<template_declaration>
    (
        check_node_existence(node, "export", 0),
        ASSERTED_EVALUATE_NODE(declaration, DECLARATION)
    );
}

std::shared_ptr<template_id>
syntax_analyzer::evaluate_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ID);

    return std::make_shared<template_id>
    (
        *ASSERTED_EVALUATE_NODE(identifier, TYPE_NAME),
        EVALUATE_SEPARATED_SEQUENCE_NODE(template_argument, TEMPLATE_ARGUMENT_LIST, util::extern_strings::comma)
    );
}

std::shared_ptr<template_argument>
syntax_analyzer::evaluate_template_argument(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ARGUMENT);

    return evaluate_only_child_node
    (
        node,
        evaluate_function_typedefs<template_argument>::id_function_map_t
        {
            //{grammar::TEMPLATE_ARGUMENT_ASSIGNMENT_EXPRESSION, &syntax_analyzer::evaluate_assignment_expression},
            //{grammar::TYPE_ID, &syntax_analyzer::evaluate_type_id},
            {grammar::ID_EXPRESSION, &syntax_analyzer::evaluate_id_expression}
        },
        false
    );
}

std::shared_ptr<nested_identifier_or_template_id>
syntax_analyzer::evaluate_nested_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_IDENTIFIER_OR_TEMPLATE_ID);

    return std::make_shared<nested_identifier_or_template_id>
    (
        check_node_existence(node, "::", 0),
        EVALUATE_NODE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        ASSERTED_EVALUATE_NODE(identifier_or_template_id, IDENTIFIER_OR_TEMPLATE_ID)
    );
}


const syntax_analyzer::tree_node_t*
syntax_analyzer::find_child_node(const tree_node_t& parent_node, int child_id)
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
syntax_analyzer::check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position)
{
    if(parent_node.children.size() <= position)
        return false;

    return get_value(parent_node.children[position]) == value;
}

bool
syntax_analyzer::check_node_existence(const tree_node_t& parent_node, const std::string& value)
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
syntax_analyzer::check_node_existence(const tree_node_t& parent_node, grammar::parser_id id, unsigned int position)
{
    if(parent_node.children.size() <= position)
        return false;

    return parent_node.children[position].value.id() == id;
}

bool
syntax_analyzer::check_node_existence(const tree_node_t& parent_node, grammar::parser_id id)
{
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
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
syntax_analyzer::get_only_child_value(const tree_node_t& node)
{
    assert(node.children.size() == 1);

    //get child node
    const tree_node_t& child_node = *node.children.begin();

    return get_value(child_node);
}

std::string
syntax_analyzer::get_value(const tree_node_t& node)
{
    //get value
    std::ostringstream value_oss;
    for(tree_node_value_iterator_t i = node.value.begin(); i != node.value.end(); ++i) //iterate node value
    {
        value_oss << *i;
    }

    return strip_redundant_spaces(value_oss.str());
}

std::string
syntax_analyzer::strip_redundant_spaces(const std::string& str)
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
syntax_analyzer::get_id(const tree_node_t& node)
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

}} //namespace socoa::cpp

#undef EVALUATE_NODE
#undef ASSERTED_EVALUATE_NODE
#undef EVALUATE_SEQUENCE_NODE
#undef EVALUATE_SEPARATED_SEQUENCE_NODE
