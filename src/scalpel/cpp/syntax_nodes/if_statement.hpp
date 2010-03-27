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

#ifndef SCALPEL_CPP_SYNTAX_NODES_IF_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_IF_STATEMENT_HPP

#include "condition.hpp"
#include "statement.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
if_statement
	= "if", "(", condition, ")", statement, ["else", statement]
;
\endverbatim
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	if_statement,
	(predefined_text_node<str::if_>)
	(optional_node<space>)
	(predefined_text_node<str::opening_round_bracket>)
	(optional_node<space>)
	(condition)
	(optional_node<space>)
	(predefined_text_node<str::closing_round_bracket>)
	(optional_node<space>)
	(statement)
	(optional_node<space>)
	(optional_node<predefined_text_node<str::else_>>)
	(optional_node<space>)
	(optional_node<statement>)
)

inline
const statement&
get_statement(const if_statement& o)
{
	return get<8>(o);
}

inline
const optional_node<statement>&
get_else_statement(const if_statement& o)
{
	return get<12>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
