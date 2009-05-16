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

#ifndef SCALPEL_CPP_SYNTAX_NODES_GOTO_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_GOTO_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
goto_statement
	= "goto", identifier, ";"
;
\endverbatim
*/
class goto_statement: public composite_node
{
	public:
		goto_statement
		(
			optional_node<space>&& post_goto_space_node,
			identifier&& identifier_node,
			optional_node<space>&& post_identifier_space_node
		);

		goto_statement(const goto_statement& o);

		goto_statement(goto_statement&& o);

		const goto_statement&
		operator=(const goto_statement& o);

	private:
		void
		update_node_list();

		optional_node<space> post_goto_space_;
		identifier identifier_;
		optional_node<space> post_identifier_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
