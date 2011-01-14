/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_INITIALIZER_LIST_INITIALIZER_CLAUSE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_INITIALIZER_LIST_INITIALIZER_CLAUSE_HPP

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class initializer_list;

/**
initializer_list_initializer_clause
	= ch_p('{') >> !s >> initializer_list >> !s >> !(ch_p(',') >> !s) >> ch_p('}')
	| ch_p('{') >> !s >> ch_p('}')
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	initializer_list_initializer_clause,
	(predefined_text_node<str::opening_brace>)
	(optional_node<space>)
	(optional_node<initializer_list>)
	(optional_node<space>)
	(optional_node<predefined_text_node<str::comma>>)
	(optional_node<space>)
	(predefined_text_node<str::closing_brace>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
