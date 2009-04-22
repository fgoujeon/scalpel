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

#ifndef SOCOA_CPP_SYNTAX_TREE_UNARY_EXPRESSION_HPP
#define SOCOA_CPP_SYNTAX_TREE_UNARY_EXPRESSION_HPP

#include "alternative_node.hpp"
#include "postfix_expression.hpp"
#include "new_expression.hpp"
#include "delete_expression.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		postfix_expression,
		new_expression,
		delete_expression
	>
	unary_expression
;

}}} //namespace socoa::cpp::syntax_nodes

#endif
