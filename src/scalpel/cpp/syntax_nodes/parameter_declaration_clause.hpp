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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PARAMETER_DECLARATION_CLAUSE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PARAMETER_DECLARATION_CLAUSE_HPP

#include "common.hpp"
#include "parameter_declaration_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
parameter_declaration_clause
	= parameter_declaration_list >> !s >> ',' >> !s >> "..."
	| parameter_declaration_list >> !s >> str_p("...")
	| parameter_declaration_list
	| str_p("...")
;
*/
typedef
	sequence_node
	<
		optional_node<parameter_declaration_list>,
		optional_node<space>,
		optional_node<simple_text_node<str::comma>>,
		optional_node<space>,
		optional_node<simple_text_node<str::ellipsis>>
	>
	parameter_declaration_clause
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
