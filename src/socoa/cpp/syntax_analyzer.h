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

#ifndef SOCOA_CPP_SYNTAX_ANALYZER_H
#define SOCOA_CPP_SYNTAX_ANALYZER_H

#include <memory>
#include "grammar.h"
#include "syntax_tree.h"
#include "parsers/type_name.h"

namespace socoa { namespace cpp
{

/**
@brief Analyses the syntax of the source code of a full C++ program.

Analyses the syntax of the source code of a full C++ program, by calling the
operator() function. After parsing the input, it generates a syntax tree of the
source code and returns it.
*/
class syntax_analyzer
{
    public:
		syntax_analyzer();

		std::shared_ptr<syntax_tree_t>
        operator()(const std::string& input);

        std::ptrdiff_t
        operator()(const scanner_t& scan);

    private:
        parsers::type_name type_name_parser_;
        grammar grammar_;
};

}} //namespace socoa::cpp

#endif
