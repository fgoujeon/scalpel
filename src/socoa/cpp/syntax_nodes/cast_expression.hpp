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

#ifndef SOCOA_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP
#define SOCOA_CPP_SYNTAX_NODES_CAST_EXPRESSION_HPP

#include "composite_node.hpp"
#include "unary_expression.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class cast_expression: public composite_node
{
	public:
		cast_expression
		(
			unary_expression&& unary_expression_node
		);

		cast_expression(const cast_expression& o);

		cast_expression(cast_expression&& o);

		const cast_expression&
		operator=(const cast_expression& o);

	private:
		void
		update_node_list();

		unary_expression unary_expression_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
