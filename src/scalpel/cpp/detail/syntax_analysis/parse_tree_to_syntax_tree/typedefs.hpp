/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_TYPEDEFS_HPP
#define SCALPEL_CPP_DETAIL_SYNTAX_ANALYSIS_PARSE_TREE_TO_SYNTAX_TREE_TYPEDEFS_HPP

#ifndef BOOST_SPIRIT_USE_OLD_NAMESPACE
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif

#include "../grammar.hpp"
#include <boost/spirit/include/classic_parse_tree.hpp>
#include <string>

namespace scalpel { namespace cpp { namespace detail { namespace syntax_analysis { namespace parse_tree_to_syntax_tree
{

typedef char const* iterator_t;
typedef boost::spirit::tree_match<iterator_t> parse_tree_match_t;
typedef parse_tree_match_t::container_t tree_t;
typedef parse_tree_match_t::node_t tree_node_t;
typedef parse_tree_match_t::const_tree_iterator tree_node_iterator_t;
typedef tree_node_t::parse_node_t tree_node_value_t;
typedef tree_node_value_t::const_iterator_t tree_node_value_iterator_t;

typedef grammar::parser_id id_t;

}}}}} //namespace scalpel::cpp::detail::syntax_analysis::parse_tree_to_syntax_tree

#endif
