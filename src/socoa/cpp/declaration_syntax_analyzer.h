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


namespace socoa { namespace cpp
{

namespace program_syntax_tree
{

class identifier;
class id_expression;
class unqualified_id;
class declaration_seq;
class declaration;
class simple_declaration;
class decl_specifier_seq;
class decl_specifier;
class type_specifier;
class simple_type_specifier;
class namespace_definition;
class init_declarator_list;
class init_declarator;
class declarator;
class direct_declarator;
class declarator_id;
class function_definition;
class class_specifier;
class template_declaration;

} //namespace program_syntax_tree

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

        void
        evaluate_declaration_seq(const tree_node_t& node, program_syntax_tree::declaration_seq& ds);

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

        std::shared_ptr<program_syntax_tree::declarator_id>
        evaluate_declarator_id(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::function_definition>
        evaluate_function_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::class_specifier>
        evaluate_class_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::template_declaration>
        evaluate_template_declaration(const tree_node_t& node);

        const tree_node_t*
        find_child_node(const tree_node_t& parent_node, int child_id);

        std::string
        get_value(const tree_node_t& node);

        std::string
        strip_redundant_spaces(const std::string& str);

        const std::string
        get_id(const tree_node_t& node);


        spirit_launcher m_spirit_launcher;
};

}} //namespace socoa::cpp

#endif
