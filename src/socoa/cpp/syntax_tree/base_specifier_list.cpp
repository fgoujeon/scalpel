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

#include "base_specifier_list.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

base_specifier_list::base_specifier_list()
{
}

base_specifier_list::base_specifier_list
(
    items_t&& items
):
    items_(items)
{
}

base_specifier_list::const_iterator
base_specifier_list::begin() const
{
	return items_.begin();
}

base_specifier_list::const_iterator
base_specifier_list::end() const
{
	return items_.end();
}

const std::string&
base_specifier_list::get_separator() const
{
    return separator;
}

void
base_specifier_list::push_back(base_specifier&& t)
{
	items_.push_back(t);
}

const std::string&
base_specifier_list::separator = util::extern_strings::comma;

}}} //namespace socoa::cpp::syntax_tree

