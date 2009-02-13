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

#ifndef SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_H
#define SOCOA_CPP_PARSE_TREE_TO_SYNTAX_TREE_H

#include <string>
#include <map>
#include <memory>
#include <stdexcept>
#include <boost/spirit/tree/parse_tree.hpp>
#include "grammar.h"
#include "syntax_tree.h"

namespace socoa { namespace cpp
{

namespace parse_tree_to_syntax_tree
{
    typedef char const* iterator_t;
    typedef boost::spirit::tree_match<iterator_t> parse_tree_match_t;
    typedef parse_tree_match_t::container_t tree_t;
    typedef parse_tree_match_t::node_t tree_node_t;
    typedef parse_tree_match_t::const_tree_iterator tree_node_iterator_t;
    typedef tree_node_t::parse_node_t tree_node_value_t;
    typedef tree_node_value_t::const_iterator_t tree_node_value_iterator_t;

    template <class T>
    struct convert_function_typedefs
    {
        typedef std::shared_ptr<T> return_type_t;
        typedef std::function<return_type_t (const tree_node_t&)> function_type_t;
        typedef std::map<const grammar::parser_id, function_type_t> id_function_map_t;
    };


    std::shared_ptr<util::sequence<syntax_tree::declaration>>
    convert_file(const tree_node_t& node);

    std::shared_ptr<syntax_tree::identifier>
    convert_identifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::id_expression>
    convert_id_expression(const tree_node_t& node);

    std::shared_ptr<syntax_tree::unqualified_id>
    convert_unqualified_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::qualified_id>
    convert_qualified_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::qualified_nested_id>
    convert_qualified_nested_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::qualified_operator_function_id>
    convert_qualified_operator_function_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::qualified_template_id>
    convert_qualified_template_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::qualified_identifier>
    convert_qualified_identifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::nested_name_specifier>
    convert_nested_name_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::nested_name_specifier_template_id_part>
    convert_nested_name_specifier_template_id_part(const tree_node_t& node);

    std::shared_ptr<syntax_tree::declaration>
    convert_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::declaration>
    convert_block_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::simple_declaration>
    convert_simple_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::decl_specifier>
    convert_decl_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::type_specifier>
    convert_type_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::simple_type_specifier>
    convert_simple_type_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::simple_template_type_specifier>
    convert_simple_template_type_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::identifier_or_template_id>
    convert_identifier_or_template_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::namespace_definition>
    convert_namespace_definition(const tree_node_t& node);

    std::shared_ptr<syntax_tree::using_declaration>
    convert_using_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::using_directive>
    convert_using_directive(const tree_node_t& node);

    std::shared_ptr<syntax_tree::init_declarator>
    convert_init_declarator(const tree_node_t& node);

    std::shared_ptr<syntax_tree::declarator>
    convert_declarator(const tree_node_t& node);

    std::shared_ptr<syntax_tree::direct_declarator>
    convert_direct_declarator(const tree_node_t& node);

    std::shared_ptr<syntax_tree::direct_declarator_function_part>
    convert_direct_declarator_function_part(const tree_node_t& node);

    std::shared_ptr<syntax_tree::direct_declarator_array_part>
    convert_direct_declarator_array_part(const tree_node_t& node);

    std::shared_ptr<syntax_tree::ptr_operator>
    convert_ptr_operator(const tree_node_t& node);

    std::shared_ptr<syntax_tree::cv_qualifier>
    convert_cv_qualifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::declarator_id>
    convert_declarator_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::parameter_declaration_clause>
    convert_parameter_declaration_clause(const tree_node_t& node);

    std::shared_ptr<syntax_tree::parameter_declaration>
    convert_parameter_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::function_definition>
    convert_function_definition(const tree_node_t& node);

    std::shared_ptr<syntax_tree::class_specifier>
    convert_class_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::class_head>
    convert_class_head(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_specification>
    convert_member_specification(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_specification_access_specifier>
    convert_member_specification_access_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declaration>
    convert_member_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declaration_member_declarator_list>
    convert_member_declaration_member_declarator_list(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declaration_unqualified_id>
    convert_member_declaration_unqualified_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declaration_function_definition>
    convert_member_declaration_function_definition(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declarator>
    convert_member_declarator(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declarator_declarator>
    convert_member_declarator_declarator(const tree_node_t& node);

    std::shared_ptr<syntax_tree::member_declarator_bit_field_member>
    convert_member_declarator_bit_field_member(const tree_node_t& node);

    std::shared_ptr<syntax_tree::base_clause>
    convert_base_clause(const tree_node_t& node);

    std::shared_ptr<syntax_tree::base_specifier>
    convert_base_specifier(const tree_node_t& node);

    std::shared_ptr<syntax_tree::ctor_initializer>
    convert_ctor_initializer(const tree_node_t& node);

    std::shared_ptr<syntax_tree::mem_initializer>
    convert_mem_initializer(const tree_node_t& node);

    std::shared_ptr<syntax_tree::mem_initializer_id>
    convert_mem_initializer_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::template_declaration>
    convert_template_declaration(const tree_node_t& node);

    std::shared_ptr<syntax_tree::template_id>
    convert_template_id(const tree_node_t& node);

    std::shared_ptr<syntax_tree::template_argument>
    convert_template_argument(const tree_node_t& node);

    std::shared_ptr<syntax_tree::nested_identifier_or_template_id>
    convert_nested_identifier_or_template_id(const tree_node_t& node);


    template
    <
        class T,
        std::shared_ptr<T> (*EvaluateFunction)(const tree_node_t&),
        const std::string& Separator// = util::extern_strings::space
    >
    std::shared_ptr<util::sequence<T, Separator>>
    convert_sequence(const tree_node_t& node);

    template<class T>
    std::shared_ptr<T>
    convert_string_enumeration(const tree_node_t& node);

    /**
    Finds a node in the given parent node, with the given id and evatuates
    it.
    @tparam T the type representing the syntax of the node to be evaluated
    @param parent_node the parent node where to find the node to be
           evaluated
    @param id the parser_id of the node to be evaluated
    @param convert_function a pointer to the function to be called to
           evaluate the node
    @param assert_node_exists if true, the function will call the assert()
           macro to ensure that the given parent node does have a child
           node of the given id
    @return a pointer to an object representing the syntax of the
            evaluated node
    */
    template <class T>
    std::shared_ptr<T>
    convert_node
    (
        const tree_node_t& parent_node,
        const grammar::parser_id id,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&),
        bool assert_node_exists = false
    );

    /**
    Evaluates each child node of the given parent node.
    @tparam T the type representing the syntax of the nodes to be evaluated
    @param parent_node the parent node where to find the nodes to be
           evaluated
    @param convert_function a pointer to the function to be called to
           evaluate the nodes
    @return a vector of pointers to objects representing the syntax of each
            evaluated node
    */
    template <class T>
    std::vector<std::shared_ptr<T>>
    convert_nodes
    (
        const tree_node_t& parent_node,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&)
    );

    /**
    Evaluates each child node of the given parent node.
    @tparam T the type representing the syntax of the nodes to be evaluated
    @param parent_node the parent node where to find the nodes to be
           evaluated
    @param convert_function a pointer to the function to be called to
           evaluate the nodes
    @param separator value of the nodes to be ignored (useful for comma
           separated lists)
    @return a vector of pointers to objects representing the syntax of each
            evaluated node
    */
    template <class T>
    std::vector<std::shared_ptr<T>>
    convert_nodes
    (
        const tree_node_t& parent_node,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&),
        const std::string& separator
    );

    /**
    Finds a list of nodes in the given parent node, with the given id and
    evatuates them.
    @tparam T the type representing the syntax of the nodes to be evaluated
    @param parent_node the parent node where to find the nodes to be
           evaluated
    @param id the parser_id of the nodes to be evaluated
    @param convert_function a pointer to the function to be called to
           evaluate the nodes
    @return a vector of pointers to objects representing the syntax of each
            evaluated node
    */
    template <class T>
    std::vector<T>
    convert_nodes
    (
        const tree_node_t& parent_node,
        const grammar::parser_id id,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&)
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
           IDENTIFIER/convert_identifier, another one for
           TEMPLATE_ID/convert_template_id, etc.)
    @return a vector of pointers to objects representing the syntax of each
            evaluated node
    */
    template <class T>
    std::vector<std::shared_ptr<T>>
    convert_nodes
    (
        const tree_node_t& parent_node,
        const std::map
        <
            const grammar::parser_id,
            std::function<std::shared_ptr<T> (const tree_node_t&)>
        >& id_evaluate_function_map
    );

    template <class T>
    std::shared_ptr<T>
    convert_only_child_node
    (
        const tree_node_t& parent_node,
        const std::map
        <
            const grammar::parser_id,
            std::function<std::shared_ptr<T> (const tree_node_t&)>
        >& id_evaluate_function_map,
        bool assert_evaluated = true
    );

    const tree_node_t*
    find_child_node(const tree_node_t& parent_node, const grammar::parser_id child_id);

    bool
    check_node_existence(const tree_node_t& parent_node, const std::string& value, unsigned int position);

    bool
    check_node_existence(const tree_node_t& parent_node, const std::string& value);

    bool
    check_node_existence(const tree_node_t& parent_node, const grammar::parser_id id, unsigned int position);

    bool
    check_node_existence(const tree_node_t& parent_node, const grammar::parser_id id);

    std::string
    get_value(const tree_node_t& node);

    std::string
    get_only_child_value(const tree_node_t& node);

    std::string
    strip_redundant_spaces(const std::string& str);

    int
    get_id(const tree_node_t& node);



    template
    <
        class T,
        std::shared_ptr<T> (*EvaluateFunction)(const tree_node_t&),
        const std::string& Separator
    >
    std::shared_ptr<util::sequence<T, Separator>>
    convert_sequence(const tree_node_t& node)
    {
        return std::make_shared<util::sequence<T, Separator>>
        (
            convert_nodes
            (
                node,
                EvaluateFunction,
                Separator
            )
        );
    }

    template<class T>
    std::shared_ptr<T>
    convert_string_enumeration(const tree_node_t& node)
    {
        return std::make_shared<T>
        (
            get_only_child_value(node)
        );
    }

    template <class T>
    std::shared_ptr<T>
    convert_node
    (
        const tree_node_t& parent_node,
        const grammar::parser_id id,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&),
        bool assert_node_exists
    )
    {
        const tree_node_t* node = find_child_node(parent_node, id);

        if(assert_node_exists)
        {
            assert(node);
            return (*convert_function)(*node);
        }
        else if(node)
        {
            return (*convert_function)(*node);
        }
        else
        {
            return std::shared_ptr<T>();
        }
    }

    template <class T>
    std::vector<std::shared_ptr<T>>
    convert_nodes
    (
        const tree_node_t& parent_node,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&)
    )
    {
        std::vector<std::shared_ptr<T>> seq;
        for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
        {
            const tree_node_t& child_node = *i;
            seq.push_back((*convert_function)(child_node));
        }

        return seq;
    }

    template <class T>
    std::vector<std::shared_ptr<T>>
    convert_nodes
    (
        const tree_node_t& parent_node,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&),
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
                seq.push_back((*convert_function)(child_node));
            }
        }

        return seq;
    }

    template <class T>
    std::vector<T>
    convert_nodes
    (
        const tree_node_t& parent_node,
        const grammar::parser_id id,
        std::shared_ptr<T> (*convert_function)(const tree_node_t&)
    )
    {
        std::vector<T> seq;
        for(tree_node_iterator_t i = parent_node.children.begin(); i != parent_node.children.end(); ++i) //for each child
        {
            const tree_node_t& child_node = *i;

            if(child_node.value.id() == id)
            {
				std::shared_ptr<T> item = (*convert_function)(child_node);
				if(item)
					seq.push_back(*item);
            }
        }

        return seq;
    }

    template <class T>
    std::vector<std::shared_ptr<T>>
    convert_nodes
    (
        const tree_node_t& parent_node,
        const std::map
        <
            const grammar::parser_id,
            std::function<std::shared_ptr<T> (const tree_node_t&)>
        >& id_evaluate_function_map
    )
    {
        typedef std::function<std::shared_ptr<T> (const tree_node_t&)> convert_function_t;
        typedef std::map<const grammar::parser_id, convert_function_t> id_evaluate_function_map_t;

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
                const grammar::parser_id id = j->first;
                const convert_function_t convert_function = j->second;

                if(child_node.value.id() == id)
                {
                    seq.push_back(convert_function(child_node));
                    break;
                }
            }
        }

        return seq;
    }

    template <class T>
    std::shared_ptr<T>
    convert_only_child_node
    (
        const tree_node_t& parent_node,
        const std::map
        <
            const grammar::parser_id,
            std::function<std::shared_ptr<T> (const tree_node_t&)>
        >& id_evaluate_function_map,
        bool assert_evaluated
    )
    {
        typedef std::function<std::shared_ptr<T> (const tree_node_t&)> convert_function_t;
        typedef std::map<const grammar::parser_id, convert_function_t> id_evaluate_function_map_t;

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
            const convert_function_t convert_function = i->second;

            if(child_node.value.id() == id)
            {
                return convert_function(child_node);
            }
        }

        assert(!assert_evaluated && "The only child node's id is not is the map");

        return std::shared_ptr<T>();
    }
}

}} //namespace socoa::cpp

#endif
