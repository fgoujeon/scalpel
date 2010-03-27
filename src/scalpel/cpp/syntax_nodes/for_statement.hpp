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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP

#include "expression.hpp"
#include "for_init_statement.hpp"
#include "condition.hpp"
#include "statement.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
for_statement
	= "for", "(", for_init_statement, [condition], ";", [expression], ")", statement
;
\endverbatim
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	for_statement,
	(predefined_text_node<str::for_>)
	(optional_node<space>)
	(predefined_text_node<str::opening_round_bracket>)
	(optional_node<space>)
	(for_init_statement)
	(optional_node<space>)
	(optional_node<condition>)
	(optional_node<space>)
	(predefined_text_node<str::semicolon>)
	(optional_node<space>)
	(optional_node<expression>)
	(optional_node<space>)
	(predefined_text_node<str::closing_round_bracket>)
	(optional_node<space>)
	(statement)
)

inline
const statement&
get_statement(const for_statement& o)
{
	return get<14>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
