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

#ifndef SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_IDENTIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_IDENTIFIER_HPP

#include "composite_node.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class qualified_identifier: public composite_node
{
	public:
		explicit
		qualified_identifier
		(
			identifier&& an_identifier
		);

		qualified_identifier(const qualified_identifier& o);

		qualified_identifier(qualified_identifier&& o);

		const qualified_identifier&
		operator=(const qualified_identifier& o);

		inline
		const identifier&
	   	identifier_node() const;

	private:
		void
		update_node_list();

		identifier identifier_;
};

inline
const identifier&
qualified_identifier::identifier_node() const
{
	return identifier_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
