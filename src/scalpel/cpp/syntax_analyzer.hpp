/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "syntax_tree.hpp"
#include "detail/syntax_analysis/grammar.hpp"

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
		syntax_tree
        operator()(const std::string& input);

    private:
		detail::syntax_analysis::grammar grammar_;
};

}} //namespace scalpel::cpp

#endif

