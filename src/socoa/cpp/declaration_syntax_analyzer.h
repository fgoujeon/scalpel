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

#ifndef SOCOA_CPP_DECLARATION_SYNTAX_ANALYZER_H
#define SOCOA_CPP_DECLARATION_SYNTAX_ANALYZER_H

#include <string>
#include <map>
#include <memory>
#include <boost/spirit/tree/parse_tree.hpp>
#include "grammar.h"
#include "program_syntax_tree_fwd.h"

namespace socoa { namespace cpp
{

/**
@brief Analyses the syntax of every declaration token of a source code.

Analyses the syntax of a source code, by calling the operator() function.
This analyzer configures the grammar so it parses declaration tokens only.
After parsing the input, it generates a syntax tree of the source code and
returns it.
*/
class declaration_syntax_analyzer
{
    private:
        typedef char const* iterator_t;
        typedef boost::spirit::tree_match<iterator_t> parse_tree_match_t;
        typedef parse_tree_match_t::container_t tree_t;
        typedef parse_tree_match_t::node_t tree_node_t;
        typedef parse_tree_match_t::const_tree_iterator tree_node_iterator_t;
        typedef tree_node_t::parse_node_t tree_node_value_t;
        typedef tree_node_value_t::const_iterator_t tree_node_value_iterator_t;

    public:
        declaration_syntax_analyzer();

        std::shared_ptr<program_syntax_tree::declaration_seq>
        operator()(const std::string& input);

    private:
        std::shared_ptr<program_syntax_tree::declaration_seq>
        evaluate_translation_unit(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::identifier>
        evaluate_identifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::id_expression>
        evaluate_id_expression(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::unqualified_id>
        evaluate_unqualified_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::nested_name_specifier>
        evaluate_nested_name_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::nested_name_specifier_template_id_part>
        evaluate_nested_name_specifier_template_id_part(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declaration_seq>
        evaluate_declaration_seq(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declaration>
        evaluate_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declaration>
        evaluate_block_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::simple_declaration>
        evaluate_simple_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::decl_specifier>
        evaluate_decl_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::decl_specifier_seq>
        evaluate_decl_specifier_seq(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::type_specifier>
        evaluate_type_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::simple_type_specifier>
        evaluate_simple_type_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::identifier_or_template_id>
        evaluate_identifier_or_template_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::namespace_definition>
        evaluate_namespace_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::namespace_definition>
        evaluate_named_namespace_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::init_declarator_list>
        evaluate_init_declarator_list(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::init_declarator>
        evaluate_init_declarator(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declarator>
        evaluate_declarator(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::direct_declarator>
        evaluate_direct_declarator(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::direct_declarator_function_part>
        evaluate_direct_declarator_function_part(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::direct_declarator_array_part>
        evaluate_direct_declarator_array_part(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::ptr_operator>
        evaluate_ptr_operator(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::cv_qualifier_seq>
        evaluate_cv_qualifier_seq(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::cv_qualifier>
        evaluate_cv_qualifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declarator_id>
        evaluate_declarator_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::parameter_declaration_clause>
        evaluate_parameter_declaration_clause(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::parameter_declaration_list>
        evaluate_parameter_declaration_list(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::parameter_declaration>
        evaluate_parameter_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::function_definition>
        evaluate_function_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::class_specifier>
        evaluate_class_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::class_head>
        evaluate_class_head(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::class_key>
        evaluate_class_key(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_specification>
        evaluate_member_specification(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declaration>
        evaluate_member_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::access_specifier>
        evaluate_access_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::template_declaration>
        evaluate_template_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::template_id>
        evaluate_template_id(const tree_node_t& node);

        /**
        Finds a node in the given parent node, with the given id and evatuates
        it.
        @tparam T the type representing the syntax of the node to be evaluated
        @param parent_node the parent node where to find the node to be
               evaluated
        @param id the parser_id of the node to be evaluated
        @param evaluate_function a pointer to the function to be called to
               evaluate the node
        @param assert_node_exists if true, the function will call the assert()
               macro to ensure that the given parent node does have a child
               node of the given id
        @return a pointer to an object representing the syntax of the
                evaluated node
        */
        template <class T>
        std::shared_ptr<T>
        evaluate
        (
            const tree_node_t& parent_node,
            const int id,
            std::shared_ptr<T> (declaration_syntax_analyzer::*evaluate_function)(const tree_node_t&),
            bool assert_node_exists = false
        );

        /**
        Finds a list of nodes in the given parent node, with the given id and
        evatuates them.
        @tparam T the type representing the syntax of the nodes to be evaluated
        @param parent_node the parent node where to find the nodes to be
               evaluated
        @param id the parser_id of the nodes to be evaluated
        @param evaluate_function a pointer to the function to be called to
               evaluate the nodes
        @return a vector of pointers to objects representing the syntax of each
                evaluated node
        */
        template <class T>
        std::vector<std::shared_ptr<T>>
        evaluate_seq
        (
            const tree_node_t& parent_node,
            int id,
            std::shared_ptr<T> (declaration_syntax_analyzer::*evaluate_function)(const tree_node_t&)
        );

        template <class T>
        std::vector<std::shared_ptr<T>>
        evaluate_seq
        (
            const tree_node_t& parent_node,
            const std::map
            <
                int,
                std::function<std::shared_ptr<T> (declaration_syntax_analyzer*, const tree_node_t&)>
            >& id_evaluate_function_map
        );

        const tree_node_t*
        find_child_node(const tree_node_t& parent_node, int child_id);

        bool
        find_value(const tree_node_t& parent_node, const std::string& value, unsigned int position);

        bool
        find_value(const tree_node_t& parent_node, const std::string& value);

        const std::string
        get_value(const tree_node_t& node);

        const std::string
        get_unique_child_value(const tree_node_t& node);

        std::string
        strip_redundant_spaces(const std::string& str);

        int
        get_id(const tree_node_t& node);


        grammar::configuration m_grammar_configuration;
        grammar m_grammar;
};

template <class T>
std::shared_ptr<T>
declaration_syntax_analyzer::evaluate
(
    const tree_node_t& parent_node,
    const int id,
    std::shared_ptr<T> (declaration_syntax_analyzer::*evaluate_function)(const tree_node_t&),
    bool assert_node_exists
)
{
    const tree_node_t* node = find_child_node(parent_node, id);

    if(assert_node_exists)
    {
        assert(node);
        return (this->*evaluate_function)(*node);
    }
    else if(node)
    {
        return (this->*evaluate_function)(*node);
    }
    else
    {
        return std::shared_ptr<T>();
    }
}

template <class T>
std::vector<std::shared_ptr<T>>
declaration_syntax_analyzer::evaluate_seq
(
    const tree_node_t& parent_node,
    int id,
    std::shared_ptr<T> (declaration_syntax_analyzer::*evaluate_function)(const tree_node_t&)
)
{
    std::vector<std::shared_ptr<T>> seq;
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        if(child_node.value.id() == id)
        {
            seq.push_back((this->*evaluate_function)(child_node));
        }
    }

    return seq;
}

template <class T>
std::vector<std::shared_ptr<T>>
declaration_syntax_analyzer::evaluate_seq
(
    const tree_node_t& parent_node,
    const std::map
    <
        int,
        std::function<std::shared_ptr<T> (declaration_syntax_analyzer*, const tree_node_t&)>
    >& id_evaluate_function_map
)
{
    typedef std::function<std::shared_ptr<T> (declaration_syntax_analyzer*, const tree_node_t&)> evaluate_function_t;
    typedef std::map<int, evaluate_function_t> id_evaluate_function_map_t;

    std::vector<std::shared_ptr<T>> seq;
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;

        for
        (
            typename id_evaluate_function_map_t::const_iterator j = id_evaluate_function_map.begin();
            j != id_evaluate_function_map.end();
            ++j
        ) //for each id/evaluate function
        {
            const int id = j->first;
            const evaluate_function_t evaluate_function = j->second;

            if(child_node.value.id() == id)
            {
                seq.push_back(evaluate_function(this, child_node));
                break;
            }
        }
    }

    return seq;
}

}} //namespace socoa::cpp

#endif