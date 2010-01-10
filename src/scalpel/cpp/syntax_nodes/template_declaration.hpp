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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_DECLARATION_HPP

#include "template_parameter_list.hpp"
#include "declaration.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
template_declaration
	= !(str_p("export") >> !s) >> str_p("template") >> !s >> '<' >> !s >> template_parameter_list >> !s >> '>' >> !s >> declaration
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	template_declaration,
	(optional_node<predefined_text_node<str::export_>>)
	(optional_node<space>)
	(predefined_text_node<str::template_>)
	(optional_node<space>)
	(predefined_text_node<str::left_angle_bracket>)
	(optional_node<space>)
	(template_parameter_list)
	(optional_node<space>)
	(predefined_text_node<str::right_angle_bracket>)
	(optional_node<space>)
	(declaration)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
