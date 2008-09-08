/*
CppParser - Standard C++ programming language parsing library
Copyright © 2008  Florian Goujeon

This file is part of CppParser.

CppParser is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, version 3 of the License.

CppParser is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CppParser.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sstream>
#include <stdexcept>
#include <iomanip>
#include "program_syntax_tree/namespace_definition.h"
#include "program_syntax_tree/class_specifier.h"
#include "program_syntax_tree/template_declaration.h"

#include "declaration_syntax_analyzer.h"

using namespace boost::spirit;
using namespace cppparser::program_syntax_tree;

namespace cppparser
{

declaration_syntax_analyzer::declaration_syntax_analyzer():
    m_grammar(m_grammar_configuration)
{
    m_grammar_configuration.skip_function_bodies = true;
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::analyze(const std::string& input)
{
    std::cout << std::endl;

    //parse the input with the C++ grammar
    tree_parse_info<> info = ast_parse(input.c_str(), m_grammar, space_p);

    //throw an exception if parsing failed
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    //declare a new declaration_seq object and populate it
    std::shared_ptr<declaration_seq> new_declaration_seq(evaluate_tree(*info.trees.begin()));

    std::cout << "--" << std::endl;

    return new_declaration_seq;
}

std::shared_ptr<declaration_seq>
declaration_syntax_analyzer::evaluate_tree(const tree_node_t& node)
{
    std::shared_ptr<declaration_seq> translation_unit(new declaration_seq());

    //check whether the node's id is really DECLARATION_SEQ
    boost::spirit::parser_id id = node.value.id();
    if(id == grammar::DECLARATION_SEQ)
    {
        evaluate_declaration_seq(node, *translation_unit);
    }
    //if the root declaration_seq has only one declaration, the AST's root node
    //is not a declaration_seq but the single declaration itself
    else
    {
        std::shared_ptr<declaration> decl = evaluate_declaration(node);

        if(decl)
        {
            translation_unit->add(decl);
        }
    }

    return translation_unit;
}

void
declaration_syntax_analyzer::evaluate_declaration_seq(const tree_node_t& node, declaration_seq& ds)
{
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
    std::cout << get_id(node);

    boost::spirit::parser_id id = node.value.id();
    if(id == grammar::NAMED_NAMESPACE_DEFINITION)
    {
        std::cout << "namespace" << std::endl;
        return evaluate_named_namespace_definition(node);
    }
    else if(id == grammar::FUNCTION_DEFINITION)
    {
        std::cout << "function" << std::endl;
        //evaluate_named_namespace_definition(node, parent);
    }
    /*else if(id == grammar::CLASS_SPECIFIER)
    {
        std::cout << "class specifier" << std::endl;
        return evaluate_class_specifier(node);
    }*/
    else if(id == grammar::TEMPLATE_DECLARATION)
    {
        std::cout << "template declaration" << std::endl;
        return evaluate_template_declaration(node);
    }
    else if(id == grammar::MEMBER_DECLARATION)
    {
        std::cout << "member declaration" << std::endl;
        //evaluate_class_specifier(node, parent);
    }
    else if(id == grammar::ELABORATED_TYPE_SPECIFIER)
    {
        std::cout << "elaborated type specifier" << std::endl;
        //evaluate_class_specifier(node, parent);
    }
    else if(id == grammar::DECLARATION)
    {
        std::cout << "declaration" << std::endl;
        //evaluate_class_specifier(node, parent);
    }
    else if(id == grammar::BLOCK_DECLARATION)
    {
        std::cout << "block_declaration" << std::endl;
        //evaluate_class_specifier(node, parent);
    }
    else if(id == grammar::SIMPLE_DECLARATION)
    {
        std::cout << "simple_declaration" << std::endl;
        return evaluate_simple_declaration(node);
    }
    else
    {
        std::cout << std::endl;
    }

    return std::shared_ptr<declaration>();
}

std::shared_ptr<simple_declaration>
declaration_syntax_analyzer::evaluate_simple_declaration(const tree_node_t& node)
{
    std::shared_ptr<simple_declaration> new_simple_declaration(new simple_declaration());

    std::cout << get_id(*node.children.begin());

    //get decl_specifier_seq node
    const tree_node_t* decl_specifier_seq_node = find_child_node(node, grammar::SIMPLE_DECLARATION_DECL_SPECIFIER_SEQ);
    if(decl_specifier_seq_node)
    {
        std::cout << "decl_specifier_seq" << std::endl;
        //evaluate decl_specifier_seq
        evaluate_decl_specifier_seq(*decl_specifier_seq_node, new_simple_declaration->decl_specifiers());
    }

    return new_simple_declaration;
}

std::shared_ptr<decl_specifier>
declaration_syntax_analyzer::evaluate_decl_specifier(const tree_node_t& node)
{
    std::cout << get_id(node);

    boost::spirit::parser_id id = node.value.id();
    if(id == grammar::CLASS_SPECIFIER)
    {
        std::cout << "class specifier" << std::endl;
        return evaluate_class_specifier(node);
    }
    else if(id == grammar::ELABORATED_TYPE_SPECIFIER)
    {
        std::cout << "elaborated type specifier" << std::endl;
        //evaluate_class_specifier(node, parent);
    }
    else
    {
        std::cout << std::endl;
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

std::shared_ptr<namespace_definition>
declaration_syntax_analyzer::evaluate_named_namespace_definition(const tree_node_t& node)
{
    //get the name of the namespace
    const tree_node_t* identifier_node = find_child_node(node, grammar::IDENTIFIER);
    assert(identifier_node);
    std::string name = get_value(*identifier_node);

    //create a new namespace with this name
    std::shared_ptr<namespace_definition> new_namespace_definition = std::shared_ptr<namespace_definition>(new namespace_definition(name));

    //get the body of the namespace
    const tree_node_t* body_node = find_child_node(node, grammar::DECLARATION_SEQ);
    if(body_node)
    {
        //evaluate the namespace's body
        evaluate_declaration_seq(*body_node, new_namespace_definition->body());
    }

    return new_namespace_definition;
}

std::shared_ptr<class_specifier>
declaration_syntax_analyzer::evaluate_class_specifier(const tree_node_t& node)
{
    //get the name of the class
    std::string name;
    const tree_node_t* class_head_node = find_child_node(node, grammar::CLASS_HEAD);
    assert(class_head_node);
    const tree_node_t* identifier_node = find_child_node(*class_head_node, grammar::IDENTIFIER);
    if(identifier_node)
    {
        name = get_value(*identifier_node);
    }

    //get the key of the class
    const tree_node_t* class_key_node = find_child_node(*class_head_node, grammar::CLASS_KEY);
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
    //is the declaration export?
    bool exported = find_child_node(node, grammar::EXPORT_KEYWORD);

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

}
