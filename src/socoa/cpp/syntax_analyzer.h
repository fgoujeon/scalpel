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
        class type_name_parser: public grammar::type_name_parser
        {
            public:
                type_name_parser(syntax_analyzer& a);

                std::ptrdiff_t
                operator()(const scanner_t& scan) const;

            private:
                syntax_analyzer& syntax_analyzer_;
        };
        friend class type_name_parser;

    public:
		syntax_analyzer();

		syntax_tree_t
        operator()(const std::string& input);

    private:
        syntax_tree_t
        analyze(const std::string& input);

        std::ptrdiff_t
        parse_type_name(const scanner_t& scan);

        type_name_parser type_name_parser_;
        grammar grammar_;
        const std::string* input_;
        const char* parsing_progress_;
        bool performing_semantic_analysis_;
};

}} //namespace socoa::cpp

#endif
