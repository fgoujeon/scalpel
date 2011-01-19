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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ENUMERATOR_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ENUMERATOR_DEFINITION_HPP

#include "identifier.hpp"
#include "common.hpp"
#include <memory>

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class conditional_expression;

/**
enumerator_definition
	= identifier >> !s >> !('=' >> !s >> conditional_expression)
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	enumerator_definition,
	(identifier)
	(optional_node<space>)
	(optional_node<predefined_text_node<str::equal>>)
	(optional_node<space>)
	(optional_node<conditional_expression>)
)

inline
const identifier&
get_identifier(const enumerator_definition& o)
{
	return get<0>(o);
}

inline
const optional_node<conditional_expression>&
get_conditional_expression(const enumerator_definition& o)
{
	return get<4>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

