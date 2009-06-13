/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "syntax_analyzer.hpp"

#include <iostream>
#include <stdexcept>
#include <boost/spirit/tree/parse_tree.hpp>
#include "detail/syntax_analysis/parse_tree_to_syntax_tree/conversion_functions.hpp"
#include "detail/syntax_analysis/parse_tree_to_syntax_tree/generic_node_converters.hpp"
#include "detail/syntax_analysis/parse_tree_to_syntax_tree/basic_functions.hpp"
#include "detail/syntax_analysis/parse_tree_to_syntax_tree/sequence_node_converter.hpp"

using namespace scalpel::cpp::detail::syntax_analysis;

namespace scalpel { namespace cpp
{

syntax_tree
syntax_analyzer::operator()(const std::string& input)
{
    //parse the input with the C++ grammar
    boost::spirit::tree_parse_info<> info = boost::spirit::pt_parse
    (
        input.c_str(),
        grammar_.get_start_rule()
    );

    //throw an exception if parsing fails
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    //convert spirit's parse tree to syntax tree and return the result
	return parse_tree_to_syntax_tree::convert_node<syntax_nodes::translation_unit>
	(
		parse_tree_to_syntax_tree::get_only_child_node
		(
			*info.trees.begin()
		)
	);
}

}} //namespace scalpel::cpp
