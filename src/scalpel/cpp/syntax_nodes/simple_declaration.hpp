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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP

#include "decl_specifier_seq.hpp"
#include "init_declarator_list.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
simple_declaration
	= [decl_specifier_seq], [init_declarator_list], ";"
;
\endverbatim
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	simple_declaration,
	(optional_node<decl_specifier_seq>)
	(optional_node<init_declarator_list>)
	(predefined_text_node<str::semicolon>)
)

inline
const optional_node<decl_specifier_seq>&
get_decl_specifier_seq(const simple_declaration& o)
{
	return get<0>(o);
}

inline
const optional_node<init_declarator_list>&
get_init_declarator_list(const simple_declaration& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

