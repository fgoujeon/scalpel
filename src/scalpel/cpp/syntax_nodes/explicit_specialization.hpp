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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXPLICIT_SPECIALIZATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXPLICIT_SPECIALIZATION_HPP

#include "declaration.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
explicit_specialization
	= str_p("template") >> !s >> '<' >> !s >> '>' >> !s >> declaration
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	explicit_specialization,
	(predefined_text_node<str::template_>)
	(predefined_text_node<str::left_angle_bracket>)
	(predefined_text_node<str::right_angle_bracket>)
	(declaration)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

