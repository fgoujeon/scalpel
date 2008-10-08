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

#ifndef SOCOA_UTIL_SEQUENCE_H
#define SOCOA_UTIL_SEQUENCE_H

#include <vector>
#include <memory>
#include "extern_strings.h"

namespace socoa { namespace util
{

template<class T, const std::string& Separator = space>
class sequence
{
    public:
        explicit sequence
        (
            std::vector<std::shared_ptr<T>>&& items
        );

        const std::vector<std::shared_ptr<T>>&
        get_items() const;

        const std::string&
        get_separator() const;

        static const std::string& separator;

    private:
        std::vector<std::shared_ptr<T>> items_;
};

template<class T, const std::string& Separator>
sequence<T, Separator>::sequence
(
    std::vector<std::shared_ptr<T>>&& items
):
    items_(items)
{
}

template<class T, const std::string& Separator>
const std::vector<std::shared_ptr<T>>&
sequence<T, Separator>::get_items() const
{
    return items_;
}

template<class T, const std::string& Separator>
const std::string&
sequence<T, Separator>::get_separator() const
{
    return Separator;
}

template<class T, const std::string& Separator>
const std::string& sequence<T, Separator>::separator = Separator;

}} //namespace socoa::util

#endif
