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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECLARATOR_HPP

#include "space.hpp"
#include "ptr_operator.hpp"
#include "list_node.hpp"
#include "common.hpp"
#include <memory>

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class direct_declarator;
typedef list_node<ptr_operator> ptr_operator_seq;

/**
\verbatim
declarator
	= {ptr_operator}, direct_declarator
;
\endverbatim
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	declarator,
	(optional_node<ptr_operator_seq>)
	(optional_node<space>)
	(direct_declarator)
)

const optional_node<ptr_operator_seq>&
get_ptr_operator_seq(const declarator& o);

const direct_declarator&
get_direct_declarator(const declarator& o);

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
