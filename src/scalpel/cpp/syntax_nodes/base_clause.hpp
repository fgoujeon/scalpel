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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BASE_CLAUSE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BASE_CLAUSE_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "base_specifier_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
base_clause
	= ":", [s], base_specifier_list
;
\endverbatim
*/
class base_clause: public composite_node
{
    public:
        base_clause
		(
			optional_node<space>&& space_node,
			base_specifier_list&& a_base_specifier_list
		);

		base_clause(const base_clause& o);

		base_clause(base_clause&& o);

		const base_clause&
		operator=(const base_clause& o);

		inline
		const optional_node<space>&
		space_node() const;

        inline
        const base_specifier_list&
        base_specifier_list_node() const;

    private:
		void
		update_node_list();

		optional_node<space> space_;
		base_specifier_list base_specifier_list_;
};

inline
const optional_node<space>&
base_clause::space_node() const
{
	return space_;
}

inline
const base_specifier_list&
base_clause::base_specifier_list_node() const
{
    return base_specifier_list_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
