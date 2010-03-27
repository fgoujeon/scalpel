/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_UNARY_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_UNARY_EXPRESSION_HPP

#include "unary_operator_unary_expression.hpp"
#include "type_id_sizeof_expression.hpp"
#include "unary_sizeof_expression.hpp"
#include "postfix_expression.hpp"
#include "new_expression.hpp"
#include "delete_expression.hpp"

#include "detail/macros/alternative_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION
(
	unary_expression,
	(unary_operator_unary_expression)
	(type_id_sizeof_expression)
	(unary_sizeof_expression)
	(postfix_expression)
	(new_expression)
	(delete_expression)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_declaration_undef.hpp"

#endif
