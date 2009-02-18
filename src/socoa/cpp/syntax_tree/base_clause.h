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

#ifndef SOCOA_CPP_SYNTAX_TREE_BASE_CLAUSE_H
#define SOCOA_CPP_SYNTAX_TREE_BASE_CLAUSE_H

#include <boost/optional.hpp>
#include "base_specifier_list.h"

namespace socoa { namespace cpp { namespace syntax_tree
{

class base_clause
{
    public:
        base_clause(base_specifier_list&& a_base_specifier_list);

        inline
        const base_specifier_list&
        get_base_specifier_list() const;

    private:
		base_specifier_list base_specifier_list_;
};

inline
const base_specifier_list&
base_clause::get_base_specifier_list() const
{
    return base_specifier_list_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif