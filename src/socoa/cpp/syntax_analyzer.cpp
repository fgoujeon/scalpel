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

#include "syntax_analyzer.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include "grammar.h"

using namespace boost::spirit;

namespace socoa { namespace cpp
{

syntax_analyzer::syntax_analyzer():
    analyzer_(grammar_)
{
    grammar::configuration grammar_configuration;
    grammar_configuration.skip_function_bodies = true;
    grammar_.set_configuration(grammar_configuration);
}

std::shared_ptr<util::sequence<program_syntax_tree::declaration>>
syntax_analyzer::operator()(const std::string& input)
{
    //reset the grammar
    grammar_.reset();

    return analyzer_.analyze
    <
        util::sequence<program_syntax_tree::declaration>,
        grammar::start_parser_id::START_FILE
    >
    (
        input,
        &generic_syntax_analyzer::evaluate_file
    );
}

}} //namespace socoa::cpp
