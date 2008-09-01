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

#ifndef CPPPARSER_DECLARATION_SEMANTIC_ANALYZER_H
#define CPPPARSER_DECLARATION_SEMANTIC_ANALYZER_H

#include <string>
#include <boost/spirit.hpp>
#include <boost/spirit/include/classic_ast.hpp>
#include "program_tree/program.h"

namespace cppparser
{

class declaration_semantic_analyzer
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
        void
        analyze(const tree_t& abstract_syntax_tree);

    private:
        void
        evaluate_tree(const tree_node_t& node, std::shared_ptr<program_tree::namespace_> global_namespace, unsigned int level = 0);

        void
        evaluate_named_namespace_definition(const tree_node_t& node, std::shared_ptr<program_tree::namespace_> parent_namespace);

        void
        evaluate_class_specifier(const tree_node_t& node);

        const tree_node_t*
        find_child_node(const tree_node_t& parent_node, int child_id);

        std::string
        get_value(const tree_node_t& node);

        std::string
        strip_redundant_spaces(const std::string& str);

        std::string
        indent(const std::string& str, unsigned int indentation_count);
};

}

#endif
