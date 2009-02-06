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

#include "syntax_analyzer.h"

#include <iostream>
#include <boost/spirit/tree/parse_tree.hpp>
#include "parse_tree_to_syntax_tree.h"

using namespace boost::spirit;
using namespace socoa::cpp::syntax_tree;
using namespace socoa::util;

namespace socoa { namespace cpp
{

syntax_analyzer::syntax_analyzer():
	grammar_(type_name_parser_)
{
}

std::shared_ptr<syntax_tree_t>
syntax_analyzer::operator()(const std::string& input)
{
    //configure functor parsers
    type_name_parser_.set_input(input);

    //parse the input with the C++ grammar
    boost::spirit::tree_parse_info<> info = boost::spirit::pt_parse
    (
        input.c_str(),
        grammar_.get_start_rule(),
        boost::spirit::space_p
    );

    //throw an exception if parsing fails
    if(!info.full)
    {
        std::ostringstream failure_message;
        failure_message << "Parsing stopped at:\n***\n" << info.stop << "\n***";
        throw std::runtime_error(failure_message.str().c_str());
    }

    //convert spirit's parse tree to syntax tree
    return parse_tree_to_syntax_tree::convert_file(*info.trees.begin());
}

}} //namespace socoa::cpp
