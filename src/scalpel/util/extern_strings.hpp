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

#ifndef SCALPEL_UTIL_EXTERN_STRINGS_HPP
#define SCALPEL_UTIL_EXTERN_STRINGS_HPP

#include <string>

namespace scalpel { namespace util
{

namespace extern_strings
{
    extern const std::string ampersand;
    extern const std::string circumflex;
    extern const std::string comma;
    extern const std::string double_ampersand;
    extern const std::string double_minus;
    extern const std::string double_pipe;
    extern const std::string double_plus;
    extern const std::string ellipsis;
    extern const std::string empty;
    extern const std::string pipe;
    extern const std::string space;

	extern const std::string this_;
}

}} //namespace scalpel::util

#endif
