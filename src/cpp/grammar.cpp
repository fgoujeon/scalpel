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

#include <socoa/cpp/grammar.h>

#include <boost/spirit/tree/parse_tree.hpp>
#include "grammar_definition_initializer.h"

namespace socoa { namespace cpp
{

grammar::grammar():
    global_namespace_ptr_(&global_namespace_, util::null_deleter()),
    scope_cursor_(global_namespace_ptr_)
{
}

void
grammar::reset()
{
    scope_cursor_.reset();
    global_namespace_.clear();
}

const grammar::configuration&
grammar::get_configuration() const
{
    return configuration_;
}

void
grammar::set_configuration(const configuration& a_configuration)
{
    configuration_ = a_configuration;
}

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

template<>
grammar::definition<scanner_t>::definition(const grammar& self):
    grammar_definition_initializer_
    (
        std::make_shared<grammar_definition_initializer<scanner_t>>
        (
            *this,
            self
        )
    )
{
    start_parsers(file, base_specifier);
}

template<>
const boost::spirit::rule<scanner_t>&
grammar::definition<scanner_t>::start() const
{
    return file;
}

}} //namespace socoa::cpp
