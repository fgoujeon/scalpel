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

#ifndef SOCOA_CPP_SYNTAX_TREE_TO_STRING_CONVERTER_HPP
#define SOCOA_CPP_SYNTAX_TREE_TO_STRING_CONVERTER_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include "syntax_tree.hpp"

namespace socoa { namespace cpp
{

class syntax_tree_to_string_converter
{
    public:
        std::string
        operator()(const syntax_tree_t& a_syntax_tree);
};

}} //namespace socoa::cpp

#endif
