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

#ifndef SCALPEL_CPP_SYNTAX_NODES_LINKAGE_SPECIFICATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LINKAGE_SPECIFICATION_HPP

#include "declaration_linkage_specification.hpp"
#include "declaration_seq_linkage_specification.hpp"
#include "common.hpp"

#include "detail/macros/alternative_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
linkage_specification
	= declaration_seq_linkage_specification
	| declaration_linkage_specification
;
*/
SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION
(
	linkage_specification,
	(declaration_seq_linkage_specification)
	(declaration_linkage_specification)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_declaration_undef.hpp"

#endif
