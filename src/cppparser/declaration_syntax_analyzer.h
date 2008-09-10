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

#ifndef CPPPARSER_DECLARATION_SYNTAX_ANALYZER_H
#define CPPPARSER_DECLARATION_SYNTAX_ANALYZER_H

#include <string>
#include <memory>
#include <boost/spirit.hpp>
#include <boost/spirit/include/classic_parse_tree.hpp>
#include "grammar.h"
#include "program_syntax_tree/declaration_seq.h"
#include "program_syntax_tree/simple_declaration.h"
#include "program_syntax_tree/type_specifier.h"

namespace cppparser
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
        declaration_syntax_analyzer();

        std::shared_ptr<program_syntax_tree::declaration_seq>
        analyze(const std::string& input);

    private:
        std::shared_ptr<program_syntax_tree::declaration_seq>
        evaluate_translation_unit(const tree_node_t& node);

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

        void
        evaluate_decl_specifier_seq(const tree_node_t& node, program_syntax_tree::decl_specifier_seq& dss);

        std::shared_ptr<program_syntax_tree::type_specifier>
        evaluate_type_specifier(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::namespace_definition>
        evaluate_namespace_definition(const tree_node_t& node);

        std::shared_ptr<program_syntax_tree::namespace_definition>
        evaluate_named_namespace_definition(const tree_node_t& node);

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


        grammar::configuration m_grammar_configuration;
        grammar m_grammar;
};

}

#endif
