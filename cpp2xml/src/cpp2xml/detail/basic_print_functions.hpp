/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CPP2XML_DETAIL_BASIC_PRINT_FUNCTIONS_HPP
#define CPP2XML_DETAIL_BASIC_PRINT_FUNCTIONS_HPP

#include <string>
#include <sstream>

namespace cpp2xml { namespace detail
{

std::string
indent(unsigned int level);

std::string
strip_special_chars(const std::string& value);

}} //namespace cpp2xml::detail

#endif

