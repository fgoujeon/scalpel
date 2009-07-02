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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NEW_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NEW_DECLARATOR_HPP

#include "ptr_operator_seq.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class direct_new_declarator;

/**
new_declarator
	= ptr_operator_seq, direct_new_declarator
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	new_declarator,
	(optional_node<ptr_operator_seq>)
	(optional_node<space>)
	(optional_node<direct_new_declarator>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
