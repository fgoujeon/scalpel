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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_TYPE_PARAMETER
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_TYPE_PARAMETER

#include "identifier.hpp"
#include "id_expression.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class template_parameter_list;

/**
template_type_parameter
	= "template" >> !s >> '<' >> !s >> template_parameter_list >> !s >> '>' >> !s >> "class" >> !(!s >> identifier) >> !(!s >> '=' >> !s >> id_expression)
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	template_type_parameter,
	(predefined_text_node<str::template_>)
	(optional_node<space>)
	(predefined_text_node<str::left_angle_bracket>)
	(optional_node<space>)
	(template_parameter_list)
	(optional_node<space>)
	(predefined_text_node<str::right_angle_bracket>)
	(optional_node<space>)
	(predefined_text_node<str::class_>)
	(optional_node<space>)
	(optional_node<identifier>)
	(optional_node<space>)
	(optional_node<predefined_text_node<str::equal>>)
	(optional_node<space>)
	(optional_node<id_expression>)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif
