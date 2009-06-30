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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECLARATION_HPP

#include "detail/macros/alternative_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class block_declaration;
class function_definition;
class template_declaration;
class explicit_instantiation;
class explicit_specialization;
class linkage_specification;
class namespace_definition;

SCALPEL_ALTERNATIVE_NODE_PIMPL_DECLARATION
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

#include "detail/macros/alternative_node_pimpl_declaration_undef.hpp"

#endif
