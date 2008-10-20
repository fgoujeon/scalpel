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

#ifndef SOCOA_CPP_SYNTAX_ANALYZER_H
#define SOCOA_CPP_SYNTAX_ANALYZER_H

#include <string>
#include <map>
#include <memory>
#include <boost/spirit/tree/parse_tree.hpp>
#include "grammar.h"
#include "program_syntax_tree.h"

namespace socoa { namespace cpp
{

/**
@brief Analyses the syntax of every declaration token of a source code.

Analyses the syntax of a source code, by calling the operator() function.
This analyzer configures the grammar so it parses declaration tokens only.
After parsing the input, it generates a syntax tree of the source code and
returns it.
*/
class syntax_analyzer
{
    private:
        typedef char const* iterator_t;
        typedef boost::spirit::tree_match<iterator_t> parse_tree_match_t;
        typedef parse_tree_match_t::container_t tree_t;
        typedef parse_tree_match_t::node_t tree_node_t;
        typedef parse_tree_match_t::const_tree_iterator tree_node_iterator_t;
        typedef tree_node_t::parse_node_t tree_node_value_t;
        typedef tree_node_value_t::const_iterator_t tree_node_value_iterator_t;

        template <class T>
        struct evaluate_function_typedefs
        {
            typedef std::shared_ptr<T> return_type_t;
            typedef std::function<return_type_t (syntax_analyzer*, const tree_node_t&)> function_type_t;
            typedef std::map<int, function_type_t> id_function_map_t;
        };

    public:
        syntax_analyzer();

        std::shared_ptr<util::sequence<program_syntax_tree::declaration>>
        operator()(const std::string& input);

    private:
        std::shared_ptr<util::sequence<program_syntax_tree::declaration>>
        evaluate_translation_unit(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::identifier>
        evaluate_identifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::id_expression>
        evaluate_id_expression(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::unqualified_id>
        evaluate_unqualified_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::qualified_id>
        evaluate_qualified_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::qualified_nested_id>
        evaluate_qualified_nested_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::qualified_operator_function_id>
        evaluate_qualified_operator_function_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::qualified_template_id>
        evaluate_qualified_template_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::qualified_identifier>
        evaluate_qualified_identifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::nested_name_specifier>
        evaluate_nested_name_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::nested_name_specifier_template_id_part>
        evaluate_nested_name_specifier_template_id_part(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declaration>
        evaluate_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declaration>
        evaluate_block_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::simple_declaration>
        evaluate_simple_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::decl_specifier>
        evaluate_decl_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::type_specifier>
        evaluate_type_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::simple_type_specifier>
        evaluate_simple_type_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::simple_template_type_specifier>
        evaluate_simple_template_type_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::identifier_or_template_id>
        evaluate_identifier_or_template_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::namespace_definition>
        evaluate_namespace_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::using_declaration>
        evaluate_using_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::using_directive>
        evaluate_using_directive(const tree_node_t& node);

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

        std::shared_ptr<program_syntax_tree::cv_qualifier>
        evaluate_cv_qualifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::declarator_id>
        evaluate_declarator_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::parameter_declaration_clause>
        evaluate_parameter_declaration_clause(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::parameter_declaration>
        evaluate_parameter_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::function_definition>
        evaluate_function_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::class_specifier>
        evaluate_class_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::class_head>
        evaluate_class_head(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_specification>
        evaluate_member_specification(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_specification_access_specifier>
        evaluate_member_specification_access_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declaration>
        evaluate_member_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declaration_member_declarator_list>
        evaluate_member_declaration_member_declarator_list(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declaration_unqualified_id>
        evaluate_member_declaration_unqualified_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declaration_function_definition>
        evaluate_member_declaration_function_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declarator>
        evaluate_member_declarator(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declarator_declarator>
        evaluate_member_declarator_declarator(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::member_declarator_bit_field_member>
        evaluate_member_declarator_bit_field_member(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::ctor_initializer>
        evaluate_ctor_initializer(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::mem_initializer>
        evaluate_mem_initializer(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::mem_initializer_id>
        evaluate_mem_initializer_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::template_declaration>
        evaluate_template_declaration(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::template_id>
        evaluate_template_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::template_argument>
        evaluate_template_argument(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::nested_identifier_or_template_id>
        evaluate_nested_identifier_or_template_id(const tree_node_t& node);

        template
        <
            class T,
            std::shared_ptr<T> (syntax_analyzer::*EvaluateFunction)(const tree_node_t&),
            const std::string& Separator// = util::space
        >
        std::shared_ptr<util::sequence<T, Separator>>
        evaluate_sequence(const tree_node_t& node);

        template<class T>
        std::shared_ptr<T>
        evaluate_keyword_enumeration(const tree_node_t& node);

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
        evaluate_node
        (
            const tree_node_t& parent_node,
            const int id,
            std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&),
            bool assert_node_exists = false
        );

        /**
        Evaluates each child node of the given parent node.
        @tparam T the type representing the syntax of the nodes to be evaluated
        @param parent_node the parent node where to find the nodes to be
               evaluated
        @param evaluate_function a pointer to the function to be called to
               evaluate the nodes
        @return a vector of pointers to objects representing the syntax of each
                evaluated node
        */
        template <class T>
        std::vector<std::shared_ptr<T>>
        evaluate_nodes
        (
            const tree_node_t& parent_node,
            std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&)
        );

        /**
        Evaluates each child node of the given parent node.
        @tparam T the type representing the syntax of the nodes to be evaluated
        @param parent_node the parent node where to find the nodes to be
               evaluated
        @param evaluate_function a pointer to the function to be called to
               evaluate the nodes
        @param separator value of the nodes to be ignored (useful for comma
               separated lists)
        @return a vector of pointers to objects representing the syntax of each
                evaluated node
        */
        template <class T>
        std::vector<std::shared_ptr<T>>
        evaluate_nodes
        (
            const tree_node_t& parent_node,
            std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&),
            const std::string& separator
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
        evaluate_nodes
        (
            const tree_node_t& parent_node,
            int id,
            std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&)
        );

        /**
        Finds a list of nodes in the given parent node, with the given id and
        evatuates them.
        @tparam T the type representing the syntax of the nodes to be evaluated
        @param parent_node the parent node where to find the nodes to be
               evaluated
        @param id_evaluate_function_map list of parser_ids that searched nodes
               may have, associated with the corresponding function to be
               called to evaluate the nodes (e.g. one pair for
               IDENTIFIER/evaluate_identifier, another one for
               TEMPLATE_ID/evaluate_template_id, etc.)
        @return a vector of pointers to objects representing the syntax of each
                evaluated node
        */
        template <class T>
        std::vector<std::shared_ptr<T>>
        evaluate_nodes
        (
            const tree_node_t& parent_node,
            const std::map
            <
                int,
                std::function<std::shared_ptr<T> (syntax_analyzer*, const tree_node_t&)>
            >& id_evaluate_function_map
        );

        template <class T>
        std::shared_ptr<T>
        evaluate_only_child_node
        (
            const tree_node_t& parent_node,
            const std::map
            <
                int,
                std::function<std::shared_ptr<T> (syntax_analyzer*, const tree_node_t&)>
            >& id_evaluate_function_map,
            bool assert_evaluated = true
        );

        const tree_node_t*
        find_child_node(const tree_node_t& parent_node, int child_id);

        bool
        check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position);

        bool
        check_node_existence(const tree_node_t& parent_node, const std::string& value);

        bool
        check_node_existence(const tree_node_t& parent_node, grammar::parser_id id, unsigned int position);

        bool
        check_node_existence(const tree_node_t& parent_node, grammar::parser_id id);

        std::string
        get_value(const tree_node_t& node);

        std::string
        get_only_child_value(const tree_node_t& node);

        std::string
        strip_redundant_spaces(const std::string& str);

        int
        get_id(const tree_node_t& node);

        grammar::configuration grammar_configuration_;
        grammar grammar_;
};

template
<
    class T,
    std::shared_ptr<T> (syntax_analyzer::*EvaluateFunction)(const syntax_analyzer::tree_node_t&),
    const std::string& Separator
>
std::shared_ptr<util::sequence<T, Separator>>
syntax_analyzer::evaluate_sequence(const tree_node_t& node)
{
    return std::make_shared<util::sequence<T, Separator>>
    (
        evaluate_nodes
        (
            node,
            EvaluateFunction,
            Separator
        )
    );
}

template<class T>
std::shared_ptr<T>
syntax_analyzer::evaluate_keyword_enumeration(const tree_node_t& node)
{
    return std::make_shared<T>
    (
        get_only_child_value(node)
    );
}

template <class T>
std::shared_ptr<T>
syntax_analyzer::evaluate_node
(
    const tree_node_t& parent_node,
    const int id,
    std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&),
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
syntax_analyzer::evaluate_nodes
(
    const tree_node_t& parent_node,
    std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&)
)
{
    std::vector<std::shared_ptr<T>> seq;
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        seq.push_back((this->*evaluate_function)(child_node));
    }

    return seq;
}

template <class T>
std::vector<std::shared_ptr<T>>
syntax_analyzer::evaluate_nodes
(
    const tree_node_t& parent_node,
    std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&),
    const std::string& separator
)
{
    std::vector<std::shared_ptr<T>> seq;
    for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
    {
        const tree_node_t& child_node = *i;
        const std::string child_value = get_value(child_node);

        if(child_value != separator) //if the current node is not a separator
        {
            seq.push_back((this->*evaluate_function)(child_node));
        }
    }

    return seq;
}

template <class T>
std::vector<std::shared_ptr<T>>
syntax_analyzer::evaluate_nodes
(
    const tree_node_t& parent_node,
    int id,
    std::shared_ptr<T> (syntax_analyzer::*evaluate_function)(const tree_node_t&)
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
syntax_analyzer::evaluate_nodes
(
    const tree_node_t& parent_node,
    const std::map
    <
        int,
        std::function<std::shared_ptr<T> (syntax_analyzer*, const tree_node_t&)>
    >& id_evaluate_function_map
)
{
    typedef std::function<std::shared_ptr<T> (syntax_analyzer*, const tree_node_t&)> evaluate_function_t;
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

template <class T>
std::shared_ptr<T>
syntax_analyzer::evaluate_only_child_node
(
    const tree_node_t& parent_node,
    const std::map
    <
        int,
        std::function<std::shared_ptr<T> (syntax_analyzer*, const tree_node_t&)>
    >& id_evaluate_function_map,
    bool assert_evaluated
)
{
    typedef std::function<std::shared_ptr<T> (syntax_analyzer*, const tree_node_t&)> evaluate_function_t;
    typedef std::map<int, evaluate_function_t> id_evaluate_function_map_t;

    assert(parent_node.children.size() == 1);
    const tree_node_t& child_node = *parent_node.children.begin();
    boost::spirit::parser_id child_id = child_node.value.id();

    for
    (
        typename id_evaluate_function_map_t::const_iterator i = id_evaluate_function_map.begin();
        i != id_evaluate_function_map.end();
        ++i
    ) //for each id/evaluate function
    {
        const int id = i->first;
        const evaluate_function_t evaluate_function = i->second;

        if(child_node.value.id() == id)
        {
            return evaluate_function(this, child_node);
        }
    }

    assert(!assert_evaluated && "The only child node's id is not is the map");

    return std::shared_ptr<T>();
}

}} //namespace socoa::cpp

#endif