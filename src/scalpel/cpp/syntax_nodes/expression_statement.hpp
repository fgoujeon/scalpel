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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXPRESSION_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXPRESSION_STATEMENT_HPP

#include "composite_node.hpp"
#include "expression.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
expression_statement
	= [expression], ";"
;
\endverbatim
*/
class expression_statement: public composite_node
{
	public:
		expression_statement
		(
			optional_node<expression>&& expression_node,
			optional_node<space>&& post_expression_space_node
		);

		expression_statement(const expression_statement& o);

		expression_statement(expression_statement&& o);

		const expression_statement&
		operator=(const expression_statement& o);

	private:
		void
		update_node_list();

		optional_node<expression> expression_;
		optional_node<space> post_expression_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
