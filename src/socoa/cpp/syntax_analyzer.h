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

#ifndef SOCOA_CPP_SYNTAX_ANALYZER_H
#define SOCOA_CPP_SYNTAX_ANALYZER_H

#include <string>
#include <map>
#include <memory>
#include <boost/spirit/tree/parse_tree.hpp>
#include "grammar.h"
#include "program_syntax_tree.h"
#include "generic_syntax_analyzer.h"

namespace socoa { namespace cpp
{

/**
@brief Analyses the syntax of every declaration token of a source code.

Analyses the syntax of a source code, by calling the operator() function.
After parsing the input, it generates a syntax tree of the source code and
returns it.
This class can analyze the source code of full programs only. See
generic_syntax_analyzer for an any token analysis.
*/
class syntax_analyzer
{
    public:
        syntax_analyzer();

        std::shared_ptr<util::sequence<program_syntax_tree::declaration>>
        operator()(const std::string& input);

    private:
        grammar grammar_;
        generic_syntax_analyzer analyzer_;
};

}} //namespace socoa::cpp

#endif
