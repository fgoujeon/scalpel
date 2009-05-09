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

#ifndef SCALPEL_CPP_SYNTAX_ANALYZER_HPP
#define SCALPEL_CPP_SYNTAX_ANALYZER_HPP

#include <map>
#include "detail/syntax_analysis/grammar.hpp"
#include "syntax_tree.hpp"
#include "semantic_analyzer.hpp"

namespace scalpel { namespace cpp
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
        class type_name_parser: public detail::syntax_analysis::grammar::type_name_parser
        {
            public:
                type_name_parser(syntax_analyzer& a);

                std::ptrdiff_t
                operator()(const detail::syntax_analysis::scanner_t& scan) const;

            private:
                syntax_analyzer& syntax_analyzer_;
        };
        friend class type_name_parser;

    public:
		syntax_analyzer();

		syntax_tree
        operator()(const std::string& input);

    private:
        syntax_tree
        analyze(const std::string& input);

        std::ptrdiff_t
        parse_type_name(const detail::syntax_analysis::scanner_t& scan);

		void
		print_type_name_map_();

        type_name_parser type_name_parser_;
		detail::syntax_analysis::grammar grammar_;
        const std::string* input_;
        const std::string* currently_analyzed_partial_input_;
        unsigned int highest_parsing_progress_;
        bool performing_semantic_analysis_;
		semantic_analyzer semantic_analyzer_;
		std::map<unsigned int, bool> type_name_map_;
};

}} //namespace scalpel::cpp

#endif
