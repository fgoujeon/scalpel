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

#ifndef SCALPEL_CPP_SYNTAX_NODES_HANDLER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_HANDLER_HPP

#include "compound_statement.hpp"
#include "exception_declaration.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
handler
	= str_p("catch") >> !s >> '(' >> !s >> exception_declaration >> !s >> ')' >> !s >> compound_statement
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::catch_>,
		predefined_text_node<str::opening_round_bracket>,
		exception_declaration,
		predefined_text_node<str::closing_round_bracket>,
		compound_statement
	>
	handler
;

inline
const compound_statement&
get_compound_statement(const handler& o)
{
	return get<4>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

