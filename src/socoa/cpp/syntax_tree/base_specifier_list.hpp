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

#ifndef SOCOA_CPP_SYNTAX_TREE_BASE_SPECIFIER_LIST_HPP
#define SOCOA_CPP_SYNTAX_TREE_BASE_SPECIFIER_LIST_HPP

#include "../../util/sequence.hpp"
#include "../../util/extern_strings.hpp"
#include "base_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

typedef
    util::sequence
    <
        base_specifier,
        util::extern_strings::comma
    >
    base_specifier_list_t
;

class base_specifier_list
{
    public:
		typedef base_specifier type;
		typedef std::vector<base_specifier> items_t;
		typedef items_t::const_iterator const_iterator;

        base_specifier_list();

        explicit base_specifier_list
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
		push_back(base_specifier&& t);

		static const std::string& separator;

    private:
        items_t items_;
};

}}} //namespace socoa::cpp::syntax_tree

#endif
