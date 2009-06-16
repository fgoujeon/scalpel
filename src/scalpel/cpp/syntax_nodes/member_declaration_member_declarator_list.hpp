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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_MEMBER_DECLARATOR_LIST_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "member_declarator_list.hpp"
#include "decl_specifier_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_declaration_member_declarator_list
	= !(member_declaration_decl_specifier_seq >> !s) >> !(member_declarator_list >> !s) >> ch_p(';')
;
*/
typedef
	sequence_node
	<
		optional_node<decl_specifier_seq>,
		optional_node<space>,
		optional_node<member_declarator_list>,
		optional_node<space>,
		simple_text_node<str::semicolon>
	>
	member_declaration_member_declarator_list
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
