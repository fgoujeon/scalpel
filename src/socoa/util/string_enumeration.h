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

#ifndef SOCOA_UTIL_STRING_ENUMERATION_H
#define SOCOA_UTIL_STRING_ENUMERATION_H

#include <cassert>
#include <vector>
#include <string>
#include <algorithm>

namespace socoa { namespace util
{

template<const std::vector<std::string>& StringList>
class string_enumeration
{
    public:
        string_enumeration(const std::string& value);

        const std::string&
        get_value() const;

    private:
        std::vector<std::string>::const_iterator value_ptr_;
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
string_enumeration<StringList>::get_value() const
{
    return *value_ptr_;
}

}} //namespace socoa::util

#endif
