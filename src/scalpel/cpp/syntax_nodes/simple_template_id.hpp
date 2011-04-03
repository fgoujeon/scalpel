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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_TEMPLATE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_TEMPLATE_ID_HPP

#include "identifier.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class template_argument;
typedef list_node<template_argument, common_nodes::comma> template_argument_list;

/**
template_id
	= type_name >> !s >> '<' >> !s >> !(template_argument_list >> !s) >> '>'
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	simple_template_id,
	(identifier)
	(predefined_text_node<str::left_angle_bracket>)
	(optional_node<template_argument_list>)
	(predefined_text_node<str::right_angle_bracket>)
)

const identifier&
get_identifier(const simple_template_id& o);

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

