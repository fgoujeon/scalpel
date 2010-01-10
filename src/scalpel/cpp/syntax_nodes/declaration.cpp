/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#include "declaration.hpp"
#include "block_declaration.hpp"
#include "function_definition.hpp"
#include "template_declaration.hpp"
#include "explicit_instantiation.hpp"
#include "explicit_specialization.hpp"
#include "linkage_specification.hpp"
#include "namespace_definition.hpp"

#include "detail/macros/alternative_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_ALTERNATIVE_NODE_PIMPL_DEFINITION
(
	declaration,
	(block_declaration)
	(function_definition)
	(template_declaration)
	(explicit_instantiation)
	(explicit_specialization)
	(linkage_specification)
	(namespace_definition)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_definition_undef.hpp"

