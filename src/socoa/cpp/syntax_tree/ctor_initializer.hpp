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

#ifndef SOCOA_CPP_SYNTAX_TREE_CTOR_INITIALIZER_HPP
#define SOCOA_CPP_SYNTAX_TREE_CTOR_INITIALIZER_HPP

#include "composite_node.hpp"
#include "mem_initializer_list.hpp"

namespace socoa { namespace cpp { namespace syntax_tree
{

class mem_initializer;

/**
\verbatim
ctor_initializer
    = ":", mem_initializer_list
;
\endverbatim
*/
class ctor_initializer: public composite_node
{
    public:
		explicit
        ctor_initializer(mem_initializer_list&& a_mem_initializer_list);

        ctor_initializer(const ctor_initializer& o);

        ctor_initializer(ctor_initializer&& o);

		const ctor_initializer&
        operator=(const ctor_initializer& o);

        inline
        const mem_initializer_list&
        get_mem_initializer_list() const;

    private:
		void
		update_node_list();

        mem_initializer_list mem_initializer_list_;
};

inline
const mem_initializer_list&
ctor_initializer::get_mem_initializer_list() const
{
    return mem_initializer_list_;
}

}}} //namespace socoa::cpp::syntax_tree

#endif
