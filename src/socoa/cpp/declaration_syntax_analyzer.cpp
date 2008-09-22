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

#include "declaration_syntax_analyzer.h"

#include <sstream>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include "grammar.h"
#include "program_syntax_tree.h"

#define EVALUATE(type, id)                              \
evaluate_node                                           \
(                                                       \
    node,                                               \
    grammar::id,                                        \
    &declaration_syntax_analyzer::evaluate_##type       \
)

#define ASSERTED_EVALUATE(type, id)                     \
evaluate_node                                           \
(                                                       \
    node,                                               \
    grammar::id,                                        \
    &declaration_syntax_analyzer::evaluate_##type,      \
    true                                                \
)

using namespace boost::spirit;
using namespace socoa::cpp::program_syntax_tree;

namespace socoa { namespace cpp
{

declaration_syntax_analyzer::declaration_syntax_analyzer():
    m_grammar(*new grammar(m_grammar_configuration))
{
    m_grammar_configuration.skip_function_bodies = true;
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::operator()(const std::string& input)
{
    std::cout << std::endl;

    //parse the input with the C++ grammar
    tree_parse_info<> info = pt_parse(input.c_str(), m_grammar, space_p);

    //throw an exception if parsing failed
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    //declare a new declaration_seq object and populate it
    const tree_node_t& root_node = *info.trees.begin();
    const tree_node_t& translation_unit_node = *root_node.children.begin();

    std::shared_ptr<declaration_seq> new_declaration_seq(evaluate_translation_unit(translation_unit_node));

    std::cout << "--" << std::endl;

    return new_declaration_seq;
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::evaluate_translation_unit(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TRANSLATION_UNIT);

    const tree_node_t& declaration_seq_node = *node.children.begin();
    return evaluate_declaration_seq(declaration_seq_node);
}

std::shared_ptr<identifier>
declaration_syntax_analyzer::evaluate_identifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::IDENTIFIER);

    return std::make_shared<identifier>(get_unique_child_value(node));
}

std::shared_ptr<id_expression>
declaration_syntax_analyzer::evaluate_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == grammar::ID_EXPRESSION);

    evaluate_function_typedefs<id_expression>::id_function_map_t id_eval;
    //id_eval.insert(std::make_pair(grammar::QUALIFIED_ID, &declaration_syntax_analyzer::evaluate_qualified_id));
    id_eval.insert(std::make_pair(grammar::UNQUALIFIED_ID, &declaration_syntax_analyzer::evaluate_unqualified_id));

    return evaluate_only_child_node(node, id_eval, false);
}

std::shared_ptr<unqualified_id>
declaration_syntax_analyzer::evaluate_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::UNQUALIFIED_ID);

    evaluate_function_typedefs<unqualified_id>::id_function_map_t id_eval;
    /*id_eval.insert(std::make_pair(grammar::OPERATOR_FUNCTION_ID, &declaration_syntax_analyzer::evaluate_identifier));
    id_eval.insert(std::make_pair(grammar::CONVERSION_FUNCTION_ID, &declaration_syntax_analyzer::evaluate_nested_name_specifier_template_id_part));
    id_eval.insert(std::make_pair(grammar::DESTRUCTOR_NAME, &declaration_syntax_analyzer::evaluate_nested_name_specifier_template_id_part));
    id_eval.insert(std::make_pair(grammar::TEMPLATE_ID, &declaration_syntax_analyzer::evaluate_nested_name_specifier_template_id_part));*/
    id_eval.insert(std::make_pair(grammar::IDENTIFIER, &declaration_syntax_analyzer::evaluate_identifier));

    return evaluate_only_child_node(node, id_eval);
}

std::shared_ptr<nested_name_specifier>
declaration_syntax_analyzer::evaluate_nested_name_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER);

    evaluate_function_typedefs<nested_name_specifier_part>::id_function_map_t id_eval;
    id_eval.insert(std::make_pair(grammar::IDENTIFIER, &declaration_syntax_analyzer::evaluate_identifier));
    id_eval.insert(std::make_pair(grammar::NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART, &declaration_syntax_analyzer::evaluate_nested_name_specifier_template_id_part));

    return std::make_shared<nested_name_specifier>
    (
        ASSERTED_EVALUATE(identifier_or_template_id, IDENTIFIER_OR_TEMPLATE_ID),
        evaluate_nodes(node, id_eval)
    );
}

std::shared_ptr<nested_name_specifier_template_id_part>
declaration_syntax_analyzer::evaluate_nested_name_specifier_template_id_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NESTED_NAME_SPECIFIER_TEMPLATE_ID_PART);

    return std::make_shared<nested_name_specifier_template_id_part>
    (
        find_value(node, "template", 0),
        std::move(*ASSERTED_EVALUATE(template_id, TEMPLATE_ID))
    );
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::evaluate_declaration_seq(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATION_SEQ);

    std::shared_ptr<declaration_seq> new_declaration_seq(std::make_shared<declaration_seq>());

    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        std::shared_ptr<declaration> decl = evaluate_declaration(child_node);

        if(decl)
        {
            new_declaration_seq->add(decl);
        }
    }

    return new_declaration_seq;
}

std::shared_ptr<declaration>
declaration_syntax_analyzer::evaluate_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATION);

    evaluate_function_typedefs<declaration>::id_function_map_t id_function_map;
    id_function_map.insert(std::make_pair(grammar::BLOCK_DECLARATION, &declaration_syntax_analyzer::evaluate_block_declaration));
    id_function_map.insert(std::make_pair(grammar::FUNCTION_DEFINITION, &declaration_syntax_analyzer::evaluate_function_definition));
    id_function_map.insert(std::make_pair(grammar::TEMPLATE_DECLARATION, &declaration_syntax_analyzer::evaluate_template_declaration));
    /*id_function_map.insert(std::make_pair(grammar::EXPLICIT_INSTANTIATION, &declaration_syntax_analyzer::));
    id_function_map.insert(std::make_pair(grammar::EXPLICIT_SPECIALIZATION, &declaration_syntax_analyzer::));
    id_function_map.insert(std::make_pair(grammar::LINKAGE_SPECIFICATION, &declaration_syntax_analyzer::));*/
    id_function_map.insert(std::make_pair(grammar::NAMESPACE_DEFINITION, &declaration_syntax_analyzer::evaluate_namespace_definition));

    return evaluate_only_child_node(node, id_function_map, false);
}

std::shared_ptr<declaration>
declaration_syntax_analyzer::evaluate_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::BLOCK_DECLARATION);

    evaluate_function_typedefs<declaration>::id_function_map_t id_function_map;
    //id_function_map.insert(std::make_pair(grammar::ASM_DEFINITION, &declaration_syntax_analyzer::evaluate_block_declaration));
    id_function_map.insert(std::make_pair(grammar::SIMPLE_DECLARATION, &declaration_syntax_analyzer::evaluate_simple_declaration));
    /*id_function_map.insert(std::make_pair(grammar::NAMESPACE_ALIAS_DEFINITION, &declaration_syntax_analyzer::evaluate_template_declaration));
    id_function_map.insert(std::make_pair(grammar::USING_DECLARATION, &declaration_syntax_analyzer::));
    id_function_map.insert(std::make_pair(grammar::USING_DIRECTIVE, &declaration_syntax_analyzer::));*/

    return evaluate_only_child_node(node, id_function_map, false);
}

std::shared_ptr<simple_declaration>
declaration_syntax_analyzer::evaluate_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_DECLARATION);

    return std::make_shared<simple_declaration>
    (
        EVALUATE(decl_specifier_seq, SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ),
        EVALUATE(init_declarator_list, INIT_DECLARATOR_LIST)
    );
}

std::shared_ptr<decl_specifier>
declaration_syntax_analyzer::evaluate_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECL_SPECIFIER);

    evaluate_function_typedefs<decl_specifier>::id_function_map_t id_function_map;
    //id_function_map.insert(std::make_pair(grammar::STORAGE_CLASS_SPECIFIER, &declaration_syntax_analyzer::evaluate_block_declaration));
    id_function_map.insert(std::make_pair(grammar::TYPE_SPECIFIER, &declaration_syntax_analyzer::evaluate_type_specifier));
    //id_function_map.insert(std::make_pair(grammar::FUNCTION_SPECIFIER, &declaration_syntax_analyzer::evaluate_template_declaration));

    return evaluate_only_child_node(node, id_function_map, false);
}

std::shared_ptr<decl_specifier_seq>
declaration_syntax_analyzer::evaluate_decl_specifier_seq(const tree_node_t& node)
{
    std::shared_ptr<decl_specifier_seq> new_decl_specifier_seq(std::make_shared<decl_specifier_seq>());

    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        std::shared_ptr<decl_specifier> specifier = evaluate_decl_specifier(child_node);

        if(specifier)
        {
            new_decl_specifier_seq->add(specifier);
        }
    }

    return new_decl_specifier_seq;
}

std::shared_ptr<type_specifier>
declaration_syntax_analyzer::evaluate_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TYPE_SPECIFIER);

    evaluate_function_typedefs<type_specifier>::id_function_map_t id_function_map;
    id_function_map.insert(std::make_pair(grammar::SIMPLE_TYPE_SPECIFIER, &declaration_syntax_analyzer::evaluate_simple_type_specifier));
    id_function_map.insert(std::make_pair(grammar::CLASS_SPECIFIER, &declaration_syntax_analyzer::evaluate_class_specifier));
    //id_function_map.insert(std::make_pair(grammar::ENUM_SPECIFIER, &declaration_syntax_analyzer::evaluate_template_declaration));
    //id_function_map.insert(std::make_pair(grammar::ELABORATED_TYPE_SPECIFIER, &declaration_syntax_analyzer::));
    id_function_map.insert(std::make_pair(grammar::CV_QUALIFIER, &declaration_syntax_analyzer::evaluate_cv_qualifier));
    //id_function_map.insert(std::make_pair(grammar::TYPEOF_EXPRESSION, &declaration_syntax_analyzer::));

    return evaluate_only_child_node(node, id_function_map, false);
}

std::shared_ptr<simple_type_specifier>
declaration_syntax_analyzer::evaluate_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::SIMPLE_TYPE_SPECIFIER);

    if(node.children.size() == 1)
    {
        std::string value = get_unique_child_value(node);
        simple_type_specifier::type value_id;

        if(value == "char")
            value_id = simple_type_specifier::CHAR;
        else if(value == "wchar_t")
            value_id = simple_type_specifier::WCHAR_T;
        else if(value == "bool")
            value_id = simple_type_specifier::BOOL;
        else if(value == "short")
            value_id = simple_type_specifier::SHORT;
        else if(value == "int")
            value_id = simple_type_specifier::INT;
        else if(value == "long")
            value_id = simple_type_specifier::LONG;
        else if(value == "signed")
            value_id = simple_type_specifier::SIGNED;
        else if(value == "unsigned")
            value_id = simple_type_specifier::UNSIGNED;
        else if(value == "float")
            value_id = simple_type_specifier::FLOAT;
        else if(value == "double")
            value_id = simple_type_specifier::DOUBLE;
        else if(value == "void")
            value_id = simple_type_specifier::VOID;
        else
            value_id = simple_type_specifier::OTHER;

        if(value_id != simple_type_specifier::OTHER)
        {
            return std::make_shared<simple_type_specifier>(value_id);
        }
    }

    bool leading_double_colon = find_value(node, "::", 0);

    if(find_value(node, "template", 1) || find_value(node, "template", 2))
    {
        return std::make_shared<simple_type_specifier>
        (
            leading_double_colon,
            ASSERTED_EVALUATE(nested_name_specifier, NESTED_NAME_SPECIFIER),
            ASSERTED_EVALUATE(template_id, TEMPLATE_ID)
        );
    }
    else
    {
        return std::make_shared<simple_type_specifier>
        (
            leading_double_colon,
            EVALUATE(nested_name_specifier, NESTED_NAME_SPECIFIER),
            ASSERTED_EVALUATE(identifier_or_template_id, IDENTIFIER_OR_TEMPLATE_ID)
        );
    }
}

std::shared_ptr<identifier_or_template_id>
declaration_syntax_analyzer::evaluate_identifier_or_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::IDENTIFIER_OR_TEMPLATE_ID);

    evaluate_function_typedefs<identifier_or_template_id>::id_function_map_t id_function_map;
    id_function_map.insert(std::make_pair(grammar::IDENTIFIER, &declaration_syntax_analyzer::evaluate_identifier));
    id_function_map.insert(std::make_pair(grammar::TEMPLATE_ID, &declaration_syntax_analyzer::evaluate_template_id));

    return evaluate_only_child_node(node, id_function_map);
}

std::shared_ptr<namespace_definition>
declaration_syntax_analyzer::evaluate_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar::NAMESPACE_DEFINITION);

    return std::make_shared<namespace_definition>
    (
        EVALUATE(identifier, IDENTIFIER),
        EVALUATE(declaration_seq, DECLARATION_SEQ)
    );
}

std::shared_ptr<init_declarator_list>
declaration_syntax_analyzer::evaluate_init_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar::INIT_DECLARATOR_LIST);

    //create init declarator list
    std::shared_ptr<init_declarator_list> new_init_declarator_list(std::make_shared<init_declarator_list>());

    //fill the list
    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        if(child_node.value.id() == grammar::INIT_DECLARATOR)
        {
            std::shared_ptr<init_declarator> new_init_declarator(evaluate_init_declarator(child_node));

            if(new_init_declarator)
            {
                new_init_declarator_list->add(new_init_declarator);
            }
        }
    }

    return new_init_declarator_list;
}

std::shared_ptr<init_declarator>
declaration_syntax_analyzer::evaluate_init_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::INIT_DECLARATOR);

    return std::make_shared<init_declarator>
    (
        *ASSERTED_EVALUATE(declarator, DECLARATOR)
    );
}

std::shared_ptr<declarator>
declaration_syntax_analyzer::evaluate_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR);

    //get ptr_operator nodes
    std::vector<std::shared_ptr<ptr_operator>> ptr_operators
    (
        evaluate_nodes
        (
            node,
            grammar::PTR_OPERATOR,
            &declaration_syntax_analyzer::evaluate_ptr_operator
        )
    );

    return std::make_shared<declarator>
    (
        std::move(ptr_operators),
        *ASSERTED_EVALUATE(direct_declarator, DIRECT_DECLARATOR)
    );
}

std::shared_ptr<direct_declarator>
declaration_syntax_analyzer::evaluate_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR);

    std::shared_ptr<declarator_id> new_declarator_id(EVALUATE(declarator_id, DECLARATOR_ID));
    std::shared_ptr<declarator> new_declarator(EVALUATE(declarator, DECLARATOR));

    //get other parts
    std::vector<std::shared_ptr<direct_declarator_part>> other_parts;
    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i)
    {
        const tree_node_t& child_node = *i;
        parser_id child_node_id = child_node.value.id();

        if(child_node_id == grammar::DIRECT_DECLARATOR_FUNCTION_PART)
        {
            other_parts.push_back(evaluate_direct_declarator_function_part(child_node));
        }
        else if(child_node_id == grammar::DIRECT_DECLARATOR_ARRAY_PART)
        {
            //other_parts.push_back(evaluate_direct_declarator_array_part(child_node));
        }
    }

    if(new_declarator_id)
    {
        return std::make_shared<direct_declarator>
        (
            new_declarator_id,
            other_parts
        );
    }
    else if(new_declarator)
    {
        return std::make_shared<direct_declarator>
        (
            new_declarator,
            other_parts
        );
    }
    else
    {
        assert(false);
        return std::shared_ptr<direct_declarator>();
    }
}

std::shared_ptr<direct_declarator_function_part>
declaration_syntax_analyzer::evaluate_direct_declarator_function_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_FUNCTION_PART);

    std::shared_ptr<parameter_declaration_clause> new_parameter_declaration_clause = EVALUATE(parameter_declaration_clause, PARAMETER_DECLARATION_CLAUSE);

    //grammar defines that this node MUST exist, but in practice it's not always the case
    if(!new_parameter_declaration_clause)
    {
        //create an empty parameter declaration clause, if node didn't have been found
        new_parameter_declaration_clause = std::make_shared<parameter_declaration_clause>
        (
            std::shared_ptr<parameter_declaration_list>(),
            false,
            false
        );
    }

    return std::make_shared<direct_declarator_function_part>
    (
        *new_parameter_declaration_clause
    );
}

std::shared_ptr<direct_declarator_array_part>
declaration_syntax_analyzer::evaluate_direct_declarator_array_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DIRECT_DECLARATOR_ARRAY_PART);

    return std::shared_ptr<direct_declarator_array_part>();
}

std::shared_ptr<ptr_operator>
declaration_syntax_analyzer::evaluate_ptr_operator(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PTR_OPERATOR);

    bool asterisk = find_value(node, "*");
    bool ampersand = find_value(node, "&", 0);
    assert
    (
        (asterisk && !ampersand) ||
        (!asterisk && ampersand)
    );

    return std::make_shared<ptr_operator>
    (
        asterisk ? ptr_operator::ASTERISK : ptr_operator::AMPERSAND,
        find_value(node, "::", 0),
        EVALUATE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        EVALUATE(cv_qualifier_seq, CV_QUALIFIER_SEQ)
    );
}

std::shared_ptr<cv_qualifier_seq>
declaration_syntax_analyzer::evaluate_cv_qualifier_seq(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CV_QUALIFIER_SEQ);

    return std::make_shared<cv_qualifier_seq>
    (
        evaluate_nodes
        (
            node,
            grammar::CV_QUALIFIER,
            &declaration_syntax_analyzer::evaluate_cv_qualifier
        )
    );
}

std::shared_ptr<cv_qualifier>
declaration_syntax_analyzer::evaluate_cv_qualifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CV_QUALIFIER);

    const std::string value = get_unique_child_value(node);
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
declaration_syntax_analyzer::evaluate_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::DECLARATOR_ID);

    return std::make_shared<declarator_id>
    (
        EVALUATE(id_expression, ID_EXPRESSION)
    );
}

std::shared_ptr<parameter_declaration_clause>
declaration_syntax_analyzer::evaluate_parameter_declaration_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION_CLAUSE);

    bool trailing_comma = find_value(node, ",", 1);
    bool ellipsis = find_value(node, "...");

    if(trailing_comma) assert(ellipsis);

    return std::make_shared<parameter_declaration_clause>
    (
        EVALUATE(parameter_declaration_list, PARAMETER_DECLARATION_LIST),
        trailing_comma,
        ellipsis
    );
}

std::shared_ptr<parameter_declaration_list>
declaration_syntax_analyzer::evaluate_parameter_declaration_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION_LIST);

    std::shared_ptr<parameter_declaration_list> new_parameter_declaration_list(std::make_shared<parameter_declaration_list>());

    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i)
    {
        const tree_node_t& parameter_declaration_node = *i;
        parser_id parameter_declaration_node_id = parameter_declaration_node.value.id();

        if(parameter_declaration_node_id == grammar::PARAMETER_DECLARATION)
        {
            new_parameter_declaration_list->add(evaluate_parameter_declaration(parameter_declaration_node));
        }
    }

    return new_parameter_declaration_list;
}

std::shared_ptr<parameter_declaration>
declaration_syntax_analyzer::evaluate_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::PARAMETER_DECLARATION);

    std::shared_ptr<decl_specifier_seq> new_decl_specifier_seq;
    std::shared_ptr<declarator> new_declarator;

    //get decl_specifier_seq node
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
    new_decl_specifier_seq = evaluate_decl_specifier_seq(decl_specifier_seq_node);

    return std::make_shared<parameter_declaration>
    (
        *new_decl_specifier_seq,
        EVALUATE(declarator, DECLARATOR),
        false
    );
}

std::shared_ptr<function_definition>
declaration_syntax_analyzer::evaluate_function_definition(const tree_node_t& node)
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
    std::shared_ptr<decl_specifier_seq> new_decl_specifier_seq;
    if(decl_specifier_seq_node)
    {
        new_decl_specifier_seq = evaluate_decl_specifier_seq(*decl_specifier_seq_node);
    }

    //create function definition object
    return std::make_shared<function_definition>
    (
        new_decl_specifier_seq,
        *ASSERTED_EVALUATE(declarator, DECLARATOR)
    );
}

std::shared_ptr<class_specifier>
declaration_syntax_analyzer::evaluate_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_SPECIFIER);

    return std::make_shared<class_specifier>
    (
        *ASSERTED_EVALUATE(class_head, CLASS_HEAD),
        EVALUATE(member_specification, MEMBER_SPECIFICATION)
    );
}

std::shared_ptr<class_head>
declaration_syntax_analyzer::evaluate_class_head(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_HEAD);

    return std::make_shared<class_head>
    (
        *ASSERTED_EVALUATE(class_key, CLASS_KEY),
        EVALUATE(nested_name_specifier, NESTED_NAME_SPECIFIER),
        EVALUATE(template_id, TEMPLATE_ID),
        EVALUATE(identifier, IDENTIFIER)
    );
}

std::shared_ptr<class_key>
declaration_syntax_analyzer::evaluate_class_key(const tree_node_t& node)
{
    assert(node.value.id() == grammar::CLASS_KEY);

    std::string key = get_unique_child_value(node);

    if(key == "class")
        return std::make_shared<class_key>(class_key::CLASS);
    else if(key == "struct")
        return std::make_shared<class_key>(class_key::STRUCT);
    else if(key == "union")
        return std::make_shared<class_key>(class_key::UNION);
    else
    {
        assert(false && "invalid class key");
        return std::shared_ptr<class_key>();
    }
}

std::shared_ptr<member_specification>
declaration_syntax_analyzer::evaluate_member_specification(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_SPECIFICATION);

    evaluate_function_typedefs<member_specification_part>::id_function_map_t id_eval;
    id_eval.insert(std::make_pair(grammar::MEMBER_DECLARATION, &declaration_syntax_analyzer::evaluate_member_declaration));
    id_eval.insert(std::make_pair(grammar::ACCESS_SPECIFIER, &declaration_syntax_analyzer::evaluate_access_specifier));

    return std::make_shared<member_specification>
    (
        evaluate_nodes(node, id_eval)
    );
}

std::shared_ptr<member_declaration>
declaration_syntax_analyzer::evaluate_member_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::MEMBER_DECLARATION);

    evaluate_function_typedefs<member_declaration>::id_function_map_t id_eval;
//    id_eval.insert(std::make_pair(grammar::MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST, &declaration_syntax_analyzer::));
//    id_eval.insert(std::make_pair(grammar::MEMBER_DECLARATION_UNQUALIFIED_ID, &declaration_syntax_analyzer::));
//    id_eval.insert(std::make_pair(grammar::MEMBER_DECLARATION_FUNCTION_DEFINITION, &declaration_syntax_analyzer::));
//    id_eval.insert(std::make_pair(grammar::USING_DECLARATION, &declaration_syntax_analyzer::));
    id_eval.insert(std::make_pair(grammar::TEMPLATE_DECLARATION, &declaration_syntax_analyzer::evaluate_template_declaration));

    return evaluate_only_child_node(node, id_eval, false);
}

std::shared_ptr<access_specifier>
declaration_syntax_analyzer::evaluate_access_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar::ACCESS_SPECIFIER);

    std::string value_str(get_unique_child_value(node));

    access_specifier::value value;
    if(value_str == "public")
        value = access_specifier::PUBLIC;
    else if(value_str == "protected")
        value = access_specifier::PROTECTED;
    else if(value_str == "private")
        value = access_specifier::PRIVATE;
    else
        assert(false);

    return std::make_shared<access_specifier>
    (
        value
    );
}

std::shared_ptr<template_declaration>
declaration_syntax_analyzer::evaluate_template_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_DECLARATION);

    //is the declaration exported?
    bool exported = find_value(node, "export", 0);

    //get declaration part
    const tree_node_t declaration_part_node = *node.children.rbegin();
    std::shared_ptr<declaration> declaration_part(evaluate_declaration(declaration_part_node));

    //create corresponding template_declaration object
    std::shared_ptr<template_declaration> new_template_declaration(new template_declaration(exported, declaration_part));
    return new_template_declaration;
}

std::shared_ptr<template_id>
declaration_syntax_analyzer::evaluate_template_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar::TEMPLATE_ID);

    return std::make_shared<template_id>
    (
        *ASSERTED_EVALUATE(identifier, IDENTIFIER)
    );
}

const declaration_syntax_analyzer::tree_node_t*
declaration_syntax_analyzer::find_child_node(const tree_node_t& parent_node, int child_id)
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
declaration_syntax_analyzer::find_value(const tree_node_t& parent_node, const std::string& value, unsigned int position)
{
    if(parent_node.children.size() <= position)
        return false;

    return get_value(parent_node.children[position]) == value;
}

bool
declaration_syntax_analyzer::find_value(const tree_node_t& parent_node, const std::string& value)
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

const std::string
declaration_syntax_analyzer::get_unique_child_value(const tree_node_t& node)
{
    assert(node.children.size() == 1);

    //get child node
    const tree_node_t& child_node = *node.children.begin();

    return get_value(child_node);
}

const std::string
declaration_syntax_analyzer::get_value(const tree_node_t& node)
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
declaration_syntax_analyzer::strip_redundant_spaces(const std::string& str)
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
declaration_syntax_analyzer::get_id(const tree_node_t& node)
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

#undef EVALUATE
#undef ASSERTED_EVALUATE
