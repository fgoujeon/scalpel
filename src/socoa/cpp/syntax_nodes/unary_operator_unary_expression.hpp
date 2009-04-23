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

#ifndef SOCOA_CPP_SYNTAX_NODES_UNARY_OPERATOR_UNARY_EXPRESSION_HPP
#define SOCOA_CPP_SYNTAX_NODES_UNARY_OPERATOR_UNARY_EXPRESSION_HPP

#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class unary_operator_unary_expression: public composite_node
{
	public:
		unary_operator_unary_expression
		(
		);

		unary_operator_unary_expression(const unary_operator_unary_expression& o);

		unary_operator_unary_expression(unary_operator_unary_expression&& o);

		const unary_operator_unary_expression&
		operator=(const unary_operator_unary_expression& o);

	private:
		void
		update_node_list();
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
