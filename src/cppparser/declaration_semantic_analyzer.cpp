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

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "grammar.h"
#include "program_model/class_.h"
#include "program_model/union_.h"

#include "declaration_semantic_analyzer.h"

namespace cppparser
{

using namespace program_model;

void
declaration_semantic_analyzer::analyze(const tree_t& abstract_syntax_tree)
{
    std::shared_ptr<program> new_program(new program());

    std::cout << std::endl;
    evaluate_tree(*abstract_syntax_tree.begin(), new_program->global_namespace());
}

void
declaration_semantic_analyzer::evaluate_tree(const tree_node_t& node, std::shared_ptr<namespace_> global_namespace, unsigned int level)
{
    using namespace boost::spirit;

    //get parser identifier
    std::string parser;
    parser_id id = node.value.id();

    if(id == grammar::NAMESPACE_NAME)
    {
        parser = "namespace name";
    }
    else if(id == grammar::NAMED_NAMESPACE_DEFINITION)
    {
        parser = "namespace def.";
        evaluate_named_namespace_definition(node, global_namespace);
    }
    else if(id == grammar::IDENTIFIER)
    {
        parser = "identifier";
    }
    else if(id == grammar::CLASS_SPECIFIER)
    {
        parser = "class spec.";
        evaluate_class_specifier(node);
    }
    else if(id == grammar::CLASS_HEAD)
    {
        parser = "class head";
    }
    else if(id == grammar::CLASS_KEY)
    {
        parser = "class key";
    }
    else
    {
        for(unsigned int i = 1; i < 300; ++i)
        {
            if(id == i)
            {
                std::ostringstream parser_oss;
                parser_oss << i;
                parser = parser_oss.str();
                break;
            }
        }
    }

    //print out parser identifier
    std::cout << '[' << std::setw(15)<< parser << ']';

    //get value
    std::ostringstream value_oss;
    for(tree_node_value_iterator_t i = node.value.begin(); i != node.value.end(); ++i) //iterate node value
    {
        value_oss << *i;
    }

    //format value
    std::string value = value_oss.str();
    value = strip_redundant_spaces(value);
    value = indent(value, level);

    //print out value
    std::cout << value;

    std::cout << std::endl;


    //recursive call with children
    for(tree_node_iterator_t i = node.children.begin(); i != node.children.end(); ++i) //for each child
    {
        evaluate_tree(*i, global_namespace, level + 1);
    }
}

void
declaration_semantic_analyzer::evaluate_named_namespace_definition(const tree_node_t& node, std::shared_ptr<namespace_> parent_namespace)
{
    //get the name of the namespace
    const tree_node_t* identifier_node = find_child_node(node, grammar::IDENTIFIER);
    assert(identifier_node);
    std::string name = get_value(*identifier_node);

    //try to find an already existing namespace with this name
    std::shared_ptr<namespace_> current_namespace = parent_namespace->find_member_by_name<namespace_>(name);

    //create a new namespace with this name if no one exists
    if(!current_namespace)
    {
        std::cout << "*** new namespace '" << name << "' ***:\n";
        current_namespace = std::shared_ptr<namespace_>(new namespace_(name));
        parent_namespace->add(current_namespace);
    }
}

void
declaration_semantic_analyzer::evaluate_class_specifier(const tree_node_t& node)
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

    if(class_key == "class" || class_key == "struct")
    {
        std::shared_ptr<class_> new_class(new class_(name));
    }
    else if(class_key == "union")
    {
        std::shared_ptr<union_> new_union(new union_(name));
    }
    else
    {
        assert(false && "incorrect class key");
    }

    std::cout << "*** new class '" << name << "' ***:\n";
    //std::shared_ptr<class_> new_class = new class_(name);
}

const declaration_semantic_analyzer::tree_node_t*
declaration_semantic_analyzer::find_child_node(const tree_node_t& parent_node, int child_id)
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
declaration_semantic_analyzer::get_value(const tree_node_t& node)
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
declaration_semantic_analyzer::strip_redundant_spaces(const std::string& str)
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

std::string
declaration_semantic_analyzer::indent(const std::string& str, unsigned int indentation_count)
{
    std::string result;

    bool new_line = true;
    for(unsigned int i = 0; i < str.size(); ++i)
    {
        const char c = str[i];

        if(new_line)
        {
            for(unsigned int j = 0; j < indentation_count * 2; ++j)
            {
                result += ' ';
            }
            new_line = false;
        }

        if(c == '\n')
        {
            new_line = true;
        }

        result += c;
    }

    return result;
}

}
