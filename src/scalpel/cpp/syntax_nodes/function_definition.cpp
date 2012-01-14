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

#include "function_definition.hpp"

#include "detail/macros/alternative_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_ALTERNATIVE_NODE_PIMPL_DEFINITION
(
	function_definition,
	(simple_function_definition)
	(try_block_function_definition)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_definition_undef.hpp"

