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

#ifndef SOCOA_UTIL_KEYWORD_ENUMERATION_H
#define SOCOA_UTIL_KEYWORD_ENUMERATION_H

#include <cassert>
#include <string>

namespace socoa { namespace util
{

template<const char** StringList>
class keyword_enumeration
{
    public:
        keyword_enumeration(const std::string& value);

        const char*
        get_value() const;

    private:
        static const char** string_list_;
        unsigned int value_index_;
};

template<const char** StringList>
keyword_enumeration<StringList>::keyword_enumeration(const std::string& value)
{
    bool found = false;

    for(unsigned int i = 0; string_list_[i] != std::string(""); ++i)
    {
        if(value == string_list_[i])
        {
            value_index_ = i;
            found = true;
            break;
        }
    }

    assert(found);
}

template<const char** StringList>
const char*
keyword_enumeration<StringList>::get_value() const
{
    return string_list_[value_index_];
}

template<const char** StringList>
const char** keyword_enumeration<StringList>::string_list_ = StringList;

}} //namespace socoa::util

#endif
