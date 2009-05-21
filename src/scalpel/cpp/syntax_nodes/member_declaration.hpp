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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATION_HPP

#include "alternative_node.hpp"
#include "member_declaration_function_definition.hpp"
#include "member_declaration_member_declarator_list.hpp"
#include "member_declaration_unqualified_id.hpp"
#include "using_declaration.hpp"
#include "template_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		member_declaration_function_definition,
		member_declaration_member_declarator_list,
		member_declaration_unqualified_id,
		using_declaration,
		template_declaration
	>
	member_declaration_t
;

struct member_declaration: public member_declaration_t
{
	member_declaration(member_declaration_function_definition&& o);

	member_declaration(member_declaration_member_declarator_list&& o);

	member_declaration(member_declaration_unqualified_id&& o);

	member_declaration(using_declaration&& o);

	member_declaration(template_declaration&& o);

	member_declaration(const member_declaration& o);

	member_declaration(member_declaration&& o);
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
