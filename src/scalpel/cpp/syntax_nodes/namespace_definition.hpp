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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP

#include "declaration_seq.hpp"
#include "identifier.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
namespace_definition
	= "namespace", [identifier], "{", [declaration_seq], "}"
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	namespace_definition,
	(predefined_text_node<str::namespace_>)
	(optional_node<space>)
	(optional_node<identifier>)
	(optional_node<space>)
	(optional_node<leaf_node>)
	(optional_node<space>)
	(predefined_text_node<str::opening_brace>)
	(optional_node<space>)
	(optional_node<declaration_seq>)
	(optional_node<space>)
	(predefined_text_node<str::closing_brace>)
)

inline
const optional_node<identifier>&
get_identifier(const namespace_definition& o)
{
	return get<2>(o);
}

inline
const optional_node<list_node<declaration>>&
get_declaration_seq(const namespace_definition& o)
{
	return get<8>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

#endif
