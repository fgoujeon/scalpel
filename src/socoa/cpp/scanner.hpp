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

#ifndef SOCOA_CPP_SCANNER_HPP
#define SOCOA_CPP_SCANNER_HPP

#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/parse_tree.hpp>

//scanner type of boost::spirit::pt_parse() function
typedef
    boost::spirit::scanner
    <
        const char*,
        boost::spirit::scanner_policies
        <
            boost::spirit::skip_parser_iteration_policy
            <
                boost::spirit::space_parser,
                boost::spirit::iteration_policy
            >,
            boost::spirit::pt_match_policy
            <
                const char*,
                boost::spirit::node_val_data_factory<boost::spirit::nil_t>,
                boost::spirit::nil_t
            >,
            boost::spirit::action_policy
        >
    >
    scanner_t
;

#endif