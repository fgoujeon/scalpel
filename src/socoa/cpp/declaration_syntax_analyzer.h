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

#ifndef SOCOA_CPP_DECLARATION_SYNTAX_ANALYZER_H
#define SOCOA_CPP_DECLARATION_SYNTAX_ANALYZER_H

#include <string>
#include <memory>
#include <boost/spirit.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>
#include "spirit_launcher.h"
#include "grammar_parser_id.h"
#include "program_syntax_tree_fwd.h"

namespace socoa { namespace cpp
{

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
        std::shared_ptr<program_syntax_tree::declaration_seq>
        analyze(const std::string& input);

    private:
        std::shared_ptr<program_syntax_tree::declaration_seq>
        evaluate_translation_unit(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::identifier>
        evaluate_identifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::id_expression>
        evaluate_id_expression(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::unqualified_id>
        evaluate_unqualified_id(const tree_node_t& node);

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

        std::shared_ptr<program_syntax_tree::function_direct_declarator_part>
        evaluate_function_direct_declarator_part(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::array_direct_declarator_part>
        evaluate_array_direct_declarator_part(const tree_node_t& node);

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

        std::shared_ptr<program_syntax_tree::template_declaration>
        evaluate_template_declaration(const tree_node_t& node);

        template <class T>
        std::shared_ptr<T>
        evaluate
        (
            const tree_node_t& parent_node,
            const int id,
            std::shared_ptr<T> (declaration_syntax_analyzer::*evaluation_function)(const tree_node_t&),
            bool assert_node_exists = false
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

        const std::string
        get_id(const tree_node_t& node);


        spirit_launcher m_spirit_launcher;
};

template <class T>
std::shared_ptr<T>
declaration_syntax_analyzer::evaluate
(
    const tree_node_t& parent_node,
    const int id,
    std::shared_ptr<T> (declaration_syntax_analyzer::*evaluation_function)(const tree_node_t&),
    bool assert_node_exists
)
{
    const tree_node_t* node = find_child_node(parent_node, id);

    if(assert_node_exists)
    {
        assert(node);
        return (this->*evaluation_function)(*node);
    }
    else if(node)
    {
        return (this->*evaluation_function)(*node);
    }
    else
    {
        return std::shared_ptr<T>();
    }
}

}} //namespace socoa::cpp

#endif
