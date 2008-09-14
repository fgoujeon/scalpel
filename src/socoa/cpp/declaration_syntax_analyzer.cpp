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
#include "program_syntax_tree/identifier.h"
#include "program_syntax_tree/id_expression.h"
#include "program_syntax_tree/declaration_seq.h"
#include "program_syntax_tree/declaration.h"
#include "program_syntax_tree/simple_declaration.h"
#include "program_syntax_tree/decl_specifier_seq.h"
#include "program_syntax_tree/decl_specifier.h"
#include "program_syntax_tree/type_specifier.h"
#include "program_syntax_tree/simple_type_specifier.h"
#include "program_syntax_tree/namespace_definition.h"
#include "program_syntax_tree/init_declarator_list.h"
#include "program_syntax_tree/init_declarator.h"
#include "program_syntax_tree/declarator.h"
#include "program_syntax_tree/direct_declarator.h"
#include "program_syntax_tree/declarator_id.h"
#include "program_syntax_tree/class_specifier.h"
#include "program_syntax_tree/template_declaration.h"

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

    std::shared_ptr<declaration_seq> translation_unit(new declaration_seq());

    const tree_node_t& declaration_seq_node = *node.children.begin();
    evaluate_declaration_seq(declaration_seq_node, *translation_unit);

    return translation_unit;
}

std::shared_ptr<identifier>
declaration_syntax_analyzer::evaluate_identifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::IDENTIFIER);

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

void
declaration_syntax_analyzer::evaluate_declaration_seq(const tree_node_t& node, declaration_seq& ds)
{
    assert(node.value.id() == grammar_parser_id::DECLARATION_SEQ);

    /*
    The declaration_seq node we're evaluating is either the root node or a
    statically created member variable of a previously created object (such as
    namespace_definition), so a corresponding declaration_seq object has
    already been created.
    'ds' is this object.
    */

    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        std::shared_ptr<declaration> decl = evaluate_declaration(child_node);

        if(decl)
        {
            ds.add(decl);
        }
    }
}

std::shared_ptr<declaration>
declaration_syntax_analyzer::evaluate_declaration(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DECLARATION);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    std::cout << get_id(child_node);

    if(child_id == grammar_parser_id::BLOCK_DECLARATION)
    {
        std::cout << "BLOCK_DECLARATION" << std::endl;
        return evaluate_block_declaration(child_node);
    }
    else if(child_id == grammar_parser_id::FUNCTION_DEFINITION)
    {
        std::cout << "FUNCTION_DEFINITION" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::TEMPLATE_DECLARATION)
    {
        std::cout << "TEMPLATE_DECLARATION" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::EXPLICIT_INSTANTIATION)
    {
        std::cout << "EXPLICIT_INSTANTIATION" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::EXPLICIT_SPECIALIZATION)
    {
        std::cout << "EXPLICIT_SPECIALIZATION" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::LINKAGE_SPECIFICATION)
    {
        std::cout << "LINKAGE_SPECIFICATION" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::NAMESPACE_DEFINITION)
    {
        std::cout << "NAMESPACE_DEFINITION" << std::endl;
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

    std::cout << get_id(child_node);

    if(child_id == grammar_parser_id::ASM_DEFINITION)
    {
        std::cout << "asm_definition" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::SIMPLE_DECLARATION)
    {
        std::cout << "simple_declaration" << std::endl;
        return evaluate_simple_declaration(child_node);
    }
    else if(child_id == grammar_parser_id::NAMESPACE_ALIAS_DEFINITION)
    {
        std::cout << "namespace_alias_definition" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::USING_DECLARATION)
    {
        std::cout << "using_declaration" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::USING_DIRECTIVE)
    {
        std::cout << "using_directive" << std::endl;
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

    std::shared_ptr<simple_declaration> new_simple_declaration(new simple_declaration());

    //std::cout << get_id(*node.children.begin());

    //get decl_specifier_seq node...
    const tree_node_t* decl_specifier_seq_node = find_child_node(node, grammar_parser_id::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ);
    if(decl_specifier_seq_node)
    {
        std::cout << "decl_specifier_seq" << std::endl;
        //...and evaluate it
        evaluate_decl_specifier_seq(*decl_specifier_seq_node, new_simple_declaration->get_decl_specifier_seq());
    }

    //get init_declarator_list node...
    const tree_node_t* init_declarator_list_node = find_child_node(node, grammar_parser_id::INIT_DECLARATOR_LIST);
    if(init_declarator_list_node)
    {
        std::cout << "init_declarator_list" << std::endl;
        //...and evaluate it
        new_simple_declaration->set_init_declarator_list(evaluate_init_declarator_list(*init_declarator_list_node));
    }

    return new_simple_declaration;
}

std::shared_ptr<decl_specifier>
declaration_syntax_analyzer::evaluate_decl_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::DECL_SPECIFIER);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    std::cout << get_id(child_node);

    if(child_id == grammar_parser_id::STORAGE_CLASS_SPECIFIER)
    {
        std::cout << "storage_class_specifier" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::TYPE_SPECIFIER)
    {
        std::cout << "type_specifier" << std::endl;
        return evaluate_type_specifier(child_node);
    }
    else if(child_id == grammar_parser_id::FUNCTION_SPECIFIER)
    {
        std::cout << "function_specifier" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else
    {
        //assert(false);
    }

    return std::shared_ptr<decl_specifier>();
}

void
declaration_syntax_analyzer::evaluate_decl_specifier_seq(const tree_node_t& node, decl_specifier_seq& dss)
{
    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        std::shared_ptr<decl_specifier> specifier = evaluate_decl_specifier(child_node);

        if(specifier)
        {
            dss.add(specifier);
        }
    }
}

std::shared_ptr<type_specifier>
declaration_syntax_analyzer::evaluate_type_specifier(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::TYPE_SPECIFIER);

    assert(node.children.size() == 1);
    const tree_node_t& child_node = *node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    std::cout << get_id(child_node);

    if(child_id == grammar_parser_id::SIMPLE_TYPE_SPECIFIER)
    {
        std::cout << "simple_type_specifier" << std::endl;
        return evaluate_simple_type_specifier(child_node);
    }
    else if(child_id == grammar_parser_id::CLASS_SPECIFIER)
    {
        std::cout << "class_specifier" << std::endl;
        return evaluate_class_specifier(child_node);
    }
    else if(child_id == grammar_parser_id::ENUM_SPECIFIER)
    {
        std::cout << "enum_specifier" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::ELABORATED_TYPE_SPECIFIER)
    {
        std::cout << "elaborated_type_specifier" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::CV_QUALIFIER)
    {
        std::cout << "cv_qualifier" << std::endl;
        //return evaluate_named_namespace_definition(node);
    }
    else if(child_id == grammar_parser_id::TYPEOF_EXPRESSION)
    {
        std::cout << "typeof_expression" << std::endl;
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
            std::cout << value << std::endl;
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

    assert(node.children.size() == 1);
    const tree_node_t& namespace_definition_node = *node.children.begin();

    boost::spirit::parser_id id = namespace_definition_node.value.id();
    if(id == grammar_parser_id::NAMED_NAMESPACE_DEFINITION)
    {
        std::cout << "NAMED_NAMESPACE_DEFINITION" << std::endl;
        return evaluate_named_namespace_definition(namespace_definition_node);
    }
    else if(id == grammar_parser_id::UNNAMED_NAMESPACE_DEFINITION)
    {
        std::cout << "UNNAMED_NAMESPACE_DEFINITION" << std::endl;
        return std::shared_ptr<namespace_definition>();
    }
    else
    {
        assert(false && "incorrect namespace definition's node");
    }
}

std::shared_ptr<namespace_definition>
declaration_syntax_analyzer::evaluate_named_namespace_definition(const tree_node_t& node)
{
    assert(node.value.id() == grammar_parser_id::NAMED_NAMESPACE_DEFINITION);

    //get the name of the namespace
    const tree_node_t* identifier_node = find_child_node(node, grammar_parser_id::IDENTIFIER);
    assert(identifier_node);
    std::string name = get_value(*identifier_node);

    //create a new namespace with this name
    std::shared_ptr<namespace_definition> new_namespace_definition(new namespace_definition(name));

    //get the declaration_seq node of the namespace's body...
    const tree_node_t* body_node = find_child_node(node, grammar_parser_id::NAMESPACE_BODY);
    assert(body_node);
    const tree_node_t* declaration_seq_node = find_child_node(*body_node, grammar_parser_id::DECLARATION_SEQ);
    if(declaration_seq_node)
    {
        //..and evaluate it
        evaluate_declaration_seq(*declaration_seq_node, new_namespace_definition->get_body());
    }

    return new_namespace_definition;
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
    /*
    There is a particularily difficult node to evaluate, because the original
    rule have been highly rewritten. We have to create an object which
    represents a direct declarator just like the rule didn't have been
    rewritten.
    */

    assert(node.value.id() == grammar_parser_id::DIRECT_DECLARATOR);

    //get declarator_id node
    const tree_node_t* declarator_id_node = find_child_node(node, grammar_parser_id::DECLARATOR_ID);
    if(declarator_id_node)
    {
        return std::make_shared<direct_declarator>(evaluate_declarator_id(*declarator_id_node));
    }

    //get declarator node
    const tree_node_t* declarator_node = find_child_node(node, grammar_parser_id::DECLARATOR);
    if(declarator_node)
    {
        return std::make_shared<direct_declarator>(evaluate_declarator(*declarator_node));
    }

    return std::shared_ptr<direct_declarator>();
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
    assert(node.children.size() == 1);

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
