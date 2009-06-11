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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECLARATION_LINKAGE_SPECIFICATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECLARATION_LINKAGE_SPECIFICATION_HPP

#include "common.hpp"
#include "string_literal.hpp"
#include "declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
declaration_linkage_specification
	= "extern" >> !s >> string_literal >> !s >> declaration
;
*/
typedef
	sequence_node
	<
		simple_text_node<str::extern_>,
		optional_node<space>,
		string_literal,
		optional_node<space>,
		declaration
	>
	declaration_linkage_specification
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
