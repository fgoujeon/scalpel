/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DIRECT_NEW_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DIRECT_NEW_DECLARATOR_HPP

#include "expression.hpp"
#include "conditional_expression.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
direct_new_declarator
	= '[' >> !s >> expression >> !s >> ']' >> !(!s >> '[' >> !s >> conditional_expression >> !s >> ']')
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	direct_new_declarator,
	(predefined_text_node<str::opening_square_bracket>)
	(expression)
	(predefined_text_node<str::closing_square_bracket>)
	(optional_node<predefined_text_node<str::opening_square_bracket>>)
	(optional_node<conditional_expression>)
	(optional_node<predefined_text_node<str::closing_square_bracket>>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

