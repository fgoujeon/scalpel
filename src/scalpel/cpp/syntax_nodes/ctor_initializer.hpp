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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CTOR_INITIALIZER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CTOR_INITIALIZER_HPP

#include "composite_node.hpp"
#include "mem_initializer_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
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
        ctor_initializer
		(
			boost::optional<space>&& space_node,
			mem_initializer_list&& a_mem_initializer_list
		);

        ctor_initializer(const ctor_initializer& o);

        ctor_initializer(ctor_initializer&& o);

		const ctor_initializer&
        operator=(const ctor_initializer& o);

        inline
        const mem_initializer_list&
        mem_initializer_list_node() const;

    private:
		void
		update_node_list();

		boost::optional<space> space_;
        mem_initializer_list mem_initializer_list_;
};

inline
const mem_initializer_list&
ctor_initializer::mem_initializer_list_node() const
{
    return mem_initializer_list_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
