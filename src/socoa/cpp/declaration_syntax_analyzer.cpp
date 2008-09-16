/*
Socoa - Source Code Analysis Library
Copyright © 2008  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

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
#include <iomanip>
#include "grammar_parser_id.h"
#include "program_syntax_tree.h"

using namespace boost::spirit;
using namespace socoa::cpp::program_syntax_tree;

namespace socoa { namespace cpp
{

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::analyze(const std::string& input)
{
    std::cout << std::endl;

    //declare a new declaration_seq object and populate it
    const tree_node_t& root_node = m_spirit_launcher(input);
    const tree_node_t& translation_unit_node = *root_node.children.begin();

    std::shared_ptr<declaration_seq> new_declaration_seq(evaluate_translation_unit(translation_unit_node));

    std::cout << "--" << std::endl;

    return new_declaration_seq;
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::evaluate_translation_unit(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::TRANSLATION_UNIT);

    const tree_node_t& declaration_seq_node = *node.children.begin();
    return evaluate_declaration_seq(declaration_seq_node);
}

std::shared_ptr<identifier>
declaration_syntax_analyzer::evaluate_identifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::IDENTIFIER);

    std::cout << "identifier: " << get_value(node) << "\n";

    return std::make_shared<identifier>(get_value(node));
}

std::shared_ptr<id_expression>
declaration_syntax_analyzer::evaluate_id_expression(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::ID_EXPRESSION);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    if(child_id == grammar_parser_id::QUALIFIED_ID)
    {
        //return evaluate_qualified_id(*child_node);
    }
    else if(child_id == grammar_parser_id::UNQUALIFIED_ID)
    {
        return evaluate_unqualified_id(child_node);
    }
    else
    {
        //assert(false);
    }

    return std::shared_ptr<id_expression>();
}

std::shared_ptr<unqualified_id>
declaration_syntax_analyzer::evaluate_unqualified_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::UNQUALIFIED_ID);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    if(child_id == grammar_parser_id::OPERATOR_FUNCTION_ID)
    {
        //return evaluate_qualified_id(*child_node);
    }
    else if(child_id == grammar_parser_id::CONVERSION_FUNCTION_ID)
    {
        //return evaluate_unqualified_id(*child_node);
    }
    else if(child_id == grammar_parser_id::DESTRUCTOR_NAME)
    {
        //return evaluate_unqualified_id(*child_node);
    }
    else if(child_id == grammar_parser_id::TEMPLATE_ID)
    {
        //return evaluate_unqualified_id(*child_node);
    }
    else if(child_id == grammar_parser_id::IDENTIFIER)
    {
        return evaluate_identifier(child_node);
    }
    else
    {
        //assert(false);
    }

    return std::shared_ptr<unqualified_id>();
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::evaluate_declaration_seq(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DECLARATION_SEQ);

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
    assert(node.value.id() == grammar_parser_id::DECLARATION);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    if(child_id == grammar_parser_id::BLOCK_DECLARATION)
    {
        return evaluate_block_declaration(child_node);
    }
    else if(child_id == grammar_parser_id::FUNCTION_DEFINITION)
    {
        return evaluate_function_definition(child_node);
    }
    else if(child_id == grammar_parser_id::TEMPLATE_DECLARATION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::EXPLICIT_INSTANTIATION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::EXPLICIT_SPECIALIZATION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::LINKAGE_SPECIFICATION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::NAMESPACE_DEFINITION)
    {
        return evaluate_namespace_definition(child_node);
    }
    else
    {
        assert(false);
    }

    return std::shared_ptr<declaration>();
}

std::shared_ptr<declaration>
declaration_syntax_analyzer::evaluate_block_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::BLOCK_DECLARATION);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    if(child_id == grammar_parser_id::ASM_DEFINITION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::SIMPLE_DECLARATION)
    {
        return evaluate_simple_declaration(child_node);
    }
    else if(child_id == grammar_parser_id::NAMESPACE_ALIAS_DEFINITION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::USING_DECLARATION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::USING_DIRECTIVE)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else
    {
        assert(false);
    }

    return std::shared_ptr<declaration>();
}

std::shared_ptr<simple_declaration>
declaration_syntax_analyzer::evaluate_simple_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::SIMPLE_DECLARATION);

    std::shared_ptr<decl_specifier_seq> new_decl_specifier_seq;
    std::shared_ptr<init_declarator_list> new_init_declarator_list;

    //get decl_specifier_seq node...
    const tree_node_t* decl_specifier_seq_node = find_child_node(node, grammar_parser_id::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ);
    if(decl_specifier_seq_node)
    {
        //...and evaluate it
        new_decl_specifier_seq = evaluate_decl_specifier_seq(*decl_specifier_seq_node);
    }

    //get init_declarator_list node...
    const tree_node_t* init_declarator_list_node = find_child_node(node, grammar_parser_id::INIT_DECLARATOR_LIST);
    if(init_declarator_list_node)
    {
        //...and evaluate it
        new_init_declarator_list = evaluate_init_declarator_list(*init_declarator_list_node);
    }

    return std::make_shared<simple_declaration>
    (
        new_decl_specifier_seq,
        new_init_declarator_list
    );
}

std::shared_ptr<decl_specifier>
declaration_syntax_analyzer::evaluate_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DECL_SPECIFIER);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    if(child_id == grammar_parser_id::STORAGE_CLASS_SPECIFIER)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::TYPE_SPECIFIER)
    {
        return evaluate_type_specifier(child_node);
    }
    else if(child_id == grammar_parser_id::FUNCTION_SPECIFIER)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else
    {
        //assert(false);
    }

    return std::shared_ptr<decl_specifier>();
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
    assert(node.value.id() == grammar_parser_id::TYPE_SPECIFIER);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    if(child_id == grammar_parser_id::SIMPLE_TYPE_SPECIFIER)
    {
        return evaluate_simple_type_specifier(child_node);
    }
    else if(child_id == grammar_parser_id::CLASS_SPECIFIER)
    {
        return evaluate_class_specifier(child_node);
    }
    else if(child_id == grammar_parser_id::ENUM_SPECIFIER)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::ELABORATED_TYPE_SPECIFIER)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::CV_QUALIFIER)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::TYPEOF_EXPRESSION)
    {
        //return evaluate_named_namespace_definition(node);
    }
    else
    {
        assert(false);
    }

    return std::shared_ptr<type_specifier>();
}

std::shared_ptr<simple_type_specifier>
declaration_syntax_analyzer::evaluate_simple_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::SIMPLE_TYPE_SPECIFIER);

    if(node.children.size() == 1)
    {
        std::string value = get_value(node);

        if(value.size() > 2)
        {
            return std::shared_ptr<simple_type_specifier>(new simple_type_specifier(value));
        }
    }
    else
    {

    }

    return std::shared_ptr<simple_type_specifier>();
}

std::shared_ptr<namespace_definition>
declaration_syntax_analyzer::evaluate_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::NAMESPACE_DEFINITION);

    std::shared_ptr<namespace_definition> new_namespace_definition;

    //get the name of the namespace
    std::shared_ptr<identifier> new_identifier;
    const tree_node_t* identifier_node = find_child_node(node, grammar_parser_id::IDENTIFIER);
    if(identifier_node)
    {
        new_identifier = evaluate_identifier(*identifier_node);
    }

    //get the declaration_seq node of the namespace's body...
    std::shared_ptr<declaration_seq> namespace_body;
    const tree_node_t* declaration_seq_node = find_child_node(node, grammar_parser_id::DECLARATION_SEQ);
    if(declaration_seq_node)
    {
        //..and evaluate it
        namespace_body = evaluate_declaration_seq(*declaration_seq_node);
    }


    return std::make_shared<namespace_definition>
    (
        new_identifier,
        namespace_body
    );
}

std::shared_ptr<init_declarator_list>
declaration_syntax_analyzer::evaluate_init_declarator_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::INIT_DECLARATOR_LIST);

    //create init declarator list
    std::shared_ptr<init_declarator_list> new_init_declarator_list(new init_declarator_list());

    //fill the list
    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        if(child_node.value.id() == grammar_parser_id::INIT_DECLARATOR)
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
    assert(node.value.id() == grammar_parser_id::INIT_DECLARATOR);

    std::shared_ptr<init_declarator> new_init_declarator(new init_declarator());

    //get declarator node
    const tree_node_t* declarator_node = find_child_node(node, grammar_parser_id::DECLARATOR);
    assert(declarator_node);
    new_init_declarator->set_declarator(evaluate_declarator(*declarator_node));

    return new_init_declarator;
}

std::shared_ptr<declarator>
declaration_syntax_analyzer::evaluate_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DECLARATOR);

    //get direct_declarator node
    const tree_node_t* direct_declarator_node = find_child_node(node, grammar_parser_id::DIRECT_DECLARATOR);
    assert(direct_declarator_node);
    std::shared_ptr<declarator> new_declarator(new declarator(evaluate_direct_declarator(*direct_declarator_node)));

    //get ptr_operator nodes
    /*for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        std::shared_ptr<init_declarator> new_init_declarator(evaluate_init_declarator(child_node));

        if(new_init_declarator)
        {
            new_init_declarator_list->add(new_init_declarator);
        }
    }*/

    return new_declarator;
}

std::shared_ptr<direct_declarator>
declaration_syntax_analyzer::evaluate_direct_declarator(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DIRECT_DECLARATOR);

    std::shared_ptr<declarator_id> new_declarator_id;
    std::shared_ptr<declarator> new_declarator;
    std::vector<std::shared_ptr<direct_declarator_part>> other_parts;

    //get declarator_id node
    const tree_node_t* declarator_id_node = find_child_node(node, grammar_parser_id::DECLARATOR_ID);
    if(declarator_id_node)
    {
        new_declarator_id = evaluate_declarator_id(*declarator_id_node);
    }

    //get declarator node
    const tree_node_t* declarator_node = find_child_node(node, grammar_parser_id::DECLARATOR);
    if(declarator_node)
    {
        new_declarator = evaluate_declarator(*declarator_node);
    }

    //get other parts
    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i)
    {
        const tree_node_t& child_node = *i;
        parser_id child_node_id = child_node.value.id();

        if(child_node_id == grammar_parser_id::FUNCTION_DIRECT_DECLARATOR_PART)
        {
            other_parts.push_back(evaluate_function_direct_declarator_part(child_node));
        }
        else if(child_node_id == grammar_parser_id::ARRAY_DIRECT_DECLARATOR_PART)
        {
            //other_parts.push_back(evaluate_array_direct_declarator_part(child_node));
        }
    }

    if(declarator_id_node)
    {
        return std::make_shared<direct_declarator>
        (
            new_declarator_id,
            other_parts
        );
    }
    else if(declarator_node)
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
    }

    return std::shared_ptr<direct_declarator>();
}

std::shared_ptr<function_direct_declarator_part>
declaration_syntax_analyzer::evaluate_function_direct_declarator_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::FUNCTION_DIRECT_DECLARATOR_PART);

    //get parameter_declaration_clause node
    //grammar defines that this node MUST exist, but in practice it's not always the case
    std::shared_ptr<parameter_declaration_clause> new_parameter_declaration_clause;
    const tree_node_t* parameter_declaration_clause_node = find_child_node(node, grammar_parser_id::PARAMETER_DECLARATION_CLAUSE);
    if(parameter_declaration_clause_node)
    {
        new_parameter_declaration_clause = evaluate_parameter_declaration_clause(*parameter_declaration_clause_node);
    }
    else
    {
        //create an empty parameter declaration clause, if node didn't have been found
        new_parameter_declaration_clause = std::make_shared<parameter_declaration_clause>
        (
            std::shared_ptr<parameter_declaration_list>(),
            false,
            false
        );
    }

    return std::make_shared<function_direct_declarator_part>
    (
        *new_parameter_declaration_clause
    );
}

std::shared_ptr<array_direct_declarator_part>
declaration_syntax_analyzer::evaluate_array_direct_declarator_part(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::ARRAY_DIRECT_DECLARATOR_PART);

    return std::shared_ptr<array_direct_declarator_part>();
}

std::shared_ptr<declarator_id>
declaration_syntax_analyzer::evaluate_declarator_id(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DECLARATOR_ID);

    //get id expression node
    const tree_node_t* id_expression_node = find_child_node(node, grammar_parser_id::ID_EXPRESSION);
    if(id_expression_node)
    {
        return std::shared_ptr<declarator_id>(new declarator_id(evaluate_id_expression(*id_expression_node)));
    }

    return std::shared_ptr<declarator_id>();
}

std::shared_ptr<parameter_declaration_clause>
declaration_syntax_analyzer::evaluate_parameter_declaration_clause(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::PARAMETER_DECLARATION_CLAUSE);

    std::shared_ptr<parameter_declaration_list> new_parameter_declaration_list;
    bool trailing_comma = false;
    bool ellipsis = false;

    //get parameter_declaration_list node
    const tree_node_t* parameter_declaration_list_node = find_child_node(node, grammar_parser_id::PARAMETER_DECLARATION_LIST);
    if(parameter_declaration_list_node)
    {
        new_parameter_declaration_list = evaluate_parameter_declaration_list(*parameter_declaration_list_node);
    }

    //find trailing comma
    if(node.children.size() >= 2)
    {
        tree_node_iterator_t i = node.children.begin();
        ++i;

        if(get_value(*i) == ",")
        {
            trailing_comma = true;
            ellipsis = true;

            ++i;
            assert(get_value(*i) == "...");
        }
    }

    //find ellipsis
    if(!trailing_comma)
    {
        tree_node_iterator_t i = node.children.end();
        --i;

        if(get_value(*i) == "...")
        {
            ellipsis = true;
        }
    }

    return std::make_shared<parameter_declaration_clause>
    (
        new_parameter_declaration_list,
        trailing_comma,
        ellipsis
    );
}

std::shared_ptr<parameter_declaration_list>
declaration_syntax_analyzer::evaluate_parameter_declaration_list(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::PARAMETER_DECLARATION_LIST);

    std::shared_ptr<parameter_declaration_list> new_parameter_declaration_list(std::make_shared<parameter_declaration_list>());

    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i)
    {
        const tree_node_t& parameter_declaration_node = *i;
        parser_id parameter_declaration_node_id = parameter_declaration_node.value.id();

        if(parameter_declaration_node_id == grammar_parser_id::PARAMETER_DECLARATION)
        {
            new_parameter_declaration_list->add(evaluate_parameter_declaration(parameter_declaration_node));
        }
    }

    return new_parameter_declaration_list;
}

std::shared_ptr<parameter_declaration>
declaration_syntax_analyzer::evaluate_parameter_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::PARAMETER_DECLARATION);

    std::shared_ptr<decl_specifier_seq> new_decl_specifier_seq;
    std::shared_ptr<declarator> new_declarator;

    //get decl_specifier_seq node
    const tree_node_t& decl_specifier_seq_node = *node.children.begin();
    parser_id decl_specifier_seq_node_id = decl_specifier_seq_node.value.id();
    assert
    (
        decl_specifier_seq_node_id == grammar_parser_id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ1 ||
        decl_specifier_seq_node_id == grammar_parser_id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ2 ||
        decl_specifier_seq_node_id == grammar_parser_id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ3 ||
        decl_specifier_seq_node_id == grammar_parser_id::PARAMETER_DECLARATION_DECL_SPECIFIER_SEQ4 ||
        decl_specifier_seq_node_id == grammar_parser_id::DECL_SPECIFIER_SEQ
    );
    new_decl_specifier_seq = evaluate_decl_specifier_seq(decl_specifier_seq_node);

    //get declarator
    const tree_node_t* declarator_node = find_child_node(node, grammar_parser_id::DECLARATOR);
    if(declarator_node)
    {
        new_declarator = evaluate_declarator(*declarator_node);
    }

    return std::make_shared<parameter_declaration>
    (
        *new_decl_specifier_seq,
        new_declarator,
        false
    );
}

std::shared_ptr<function_definition>
declaration_syntax_analyzer::evaluate_function_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::FUNCTION_DEFINITION);

    //find decl_specifier_seq node...
    const tree_node_t* decl_specifier_seq_node;
    decl_specifier_seq_node = find_child_node(node, grammar_parser_id::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ1);
    if(!decl_specifier_seq_node)
        decl_specifier_seq_node = find_child_node(node, grammar_parser_id::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ2);
    if(!decl_specifier_seq_node)
        decl_specifier_seq_node = find_child_node(node, grammar_parser_id::FUNCTION_DEFINITION_DECL_SPECIFIER_SEQ3);

    //... and evaluate it
    std::shared_ptr<decl_specifier_seq> new_decl_specifier_seq;
    if(decl_specifier_seq_node)
    {
        new_decl_specifier_seq = evaluate_decl_specifier_seq(*decl_specifier_seq_node);
    }

    //get declarator node
    const tree_node_t* declarator_node = find_child_node(node, grammar_parser_id::DECLARATOR);
    assert(declarator_node);
    std::shared_ptr<declarator> new_declarator = evaluate_declarator(*declarator_node);

    //create function definition object
    return std::make_shared<function_definition>
    (
        new_decl_specifier_seq,
        *new_declarator
    );
}

std::shared_ptr<class_specifier>
declaration_syntax_analyzer::evaluate_class_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::CLASS_SPECIFIER);

    //get the name of the class
    std::string name;
    const tree_node_t* class_head_node = find_child_node(node, grammar_parser_id::CLASS_HEAD);
    assert(class_head_node);
    const tree_node_t* identifier_node = find_child_node(*class_head_node, grammar_parser_id::IDENTIFIER);
    if(identifier_node)
    {
        name = get_value(*identifier_node);
    }

    //get the key of the class
    const tree_node_t* class_key_node = find_child_node(*class_head_node, grammar_parser_id::CLASS_KEY);
    assert(class_key_node);
    std::string class_key = get_value(*class_key_node);

    //create a class/struct/union and add it to the parent namespace
    if(class_key == "class")
    {
    }
    else if(class_key == "struct")
    {
    }
    else if(class_key == "union")
    {
    }
    else
    {
        assert(false && "incorrect class key");
    }
    std::shared_ptr<class_specifier> new_class_specifier = std::shared_ptr<class_specifier>(new class_specifier(name));

    //evaluate children
    //...

    return new_class_specifier;
}

std::shared_ptr<template_declaration>
declaration_syntax_analyzer::evaluate_template_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::TEMPLATE_DECLARATION);

    //is the declaration exported?
    bool exported = find_child_node(node, grammar_parser_id::EXPORT_KEYWORD);

    //get declaration part
    const tree_node_t declaration_part_node = *node.children.rbegin();
    std::shared_ptr<declaration> declaration_part(evaluate_declaration(declaration_part_node));

    //create corresponding template_declaration object
    std::shared_ptr<template_declaration> new_template_declaration(new template_declaration(exported, declaration_part));
    return new_template_declaration;
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

std::string
declaration_syntax_analyzer::get_value(const tree_node_t& node)
{
    //assert(node.children.size() == 1);

    //get child node
    const tree_node_t& child_node = *node.children.begin();

    //get value
    std::ostringstream value_oss;
    for(tree_node_value_iterator_t i = child_node.value.begin(); i != child_node.value.end(); ++i) //iterate node value
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

const std::string
declaration_syntax_analyzer::get_id(const tree_node_t& node)
{
    boost::spirit::parser_id id = node.value.id();
    std::ostringstream oss;

    oss << "[";
    for(unsigned int i = 0; i < 400; ++i)
    {
        if(id == i)
        {
            oss << i;
            break;
        }
    }
    oss << "]";

    return oss.str();
}

}} //namespace socoa::cpp
