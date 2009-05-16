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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CONTINUE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CONTINUE_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
continue_statement
	= "continue", ";"
;
\endverbatim
*/
class continue_statement: public composite_node
{
	public:
		continue_statement
		(
			optional_node<space>&& space_node
		);

		continue_statement(const continue_statement& o);

		continue_statement(continue_statement&& o);

		const continue_statement&
		operator=(const continue_statement& o);

	private:
		void
		update_node_list();

		optional_node<space> space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
