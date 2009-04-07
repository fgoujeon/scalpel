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

#ifndef SOCOA_UTIL_SEQUENCE_HPP
#define SOCOA_UTIL_SEQUENCE_HPP

#include <vector>
#include "extern_strings.hpp"

namespace socoa { namespace util
{

template<class T, const std::string& Separator = extern_strings::space>
class sequence
{
    public:
		typedef T type;
		typedef std::vector<T> items_t;
		typedef typename items_t::const_iterator const_iterator;

        sequence();

        explicit sequence
        (
            items_t&& items
        );

		const_iterator
		begin() const;

		const_iterator
		end() const;

        const std::string&
        get_separator() const;

		void
		push_back(T&& t);

		static const std::string& separator;

    private:
        items_t items_;
};

template<class T, const std::string& Separator>
sequence<T, Separator>::sequence()
{
}

template<class T, const std::string& Separator>
sequence<T, Separator>::sequence
(
    items_t&& items
):
    items_(items)
{
}

template<class T, const std::string& Separator>
typename sequence<T, Separator>::const_iterator
sequence<T, Separator>::begin() const
{
	return items_.begin();
}

template<class T, const std::string& Separator>
typename sequence<T, Separator>::const_iterator
sequence<T, Separator>::end() const
{
	return items_.end();
}

template<class T, const std::string& Separator>
const std::string&
sequence<T, Separator>::get_separator() const
{
    return Separator;
}

template<class T, const std::string& Separator>
void
sequence<T, Separator>::push_back(T&& t)
{
	items_.push_back(t);
}

template<class T, const std::string& Separator>
const std::string&
sequence<T, Separator>::separator = Separator;

}} //namespace socoa::util

#endif
