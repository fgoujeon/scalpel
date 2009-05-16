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

#ifndef SCALPEL_CPP_SYNTAX_NODES_RETURN_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_RETURN_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
return_statement
	= "return", [expression], ";"
;
\endverbatim
*/
class return_statement: public composite_node
{
	public:
		return_statement
		(
			optional_node<space>&& post_return_space_node,
			optional_node<expression>&& expression_node,
			optional_node<space>&& post_expression_space_node
		);

		return_statement(const return_statement& o);

		return_statement(return_statement&& o);

		const return_statement&
		operator=(const return_statement& o);

	private:
		void
		update_node_list();

		optional_node<space> post_return_space_;
		optional_node<expression> expression_;
		optional_node<space> post_expression_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
