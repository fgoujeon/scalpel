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

#ifndef SCALPEL_UTIL_STRING_ENUMERATION_HPP
#define SCALPEL_UTIL_STRING_ENUMERATION_HPP

#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

namespace scalpel { namespace util
{

template<const std::vector<std::string>& StringList>
class string_enumeration
{
    public:
		typedef std::vector<std::string> string_list_t;

        string_enumeration(const std::string& value);

        const std::string&
        value() const;

    private:
        string_list_t::const_iterator value_ptr_;
};

template<const std::vector<std::string>& StringList>
string_enumeration<StringList>::string_enumeration(const std::string& value):
    value_ptr_
    (
        std::find
        (
            StringList.begin(),
            StringList.end(),
            value
        )
    )
{
    assert(value_ptr_ != StringList.end());
}

template<const std::vector<std::string>& StringList>
const std::string&
string_enumeration<StringList>::value() const
{
    return *value_ptr_;
}

}} //namespace scalpel::util

#endif
