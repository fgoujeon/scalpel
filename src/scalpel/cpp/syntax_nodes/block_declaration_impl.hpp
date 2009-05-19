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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BLOCK_DECLARATION_IMPL_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BLOCK_DECLARATION_IMPL_HPP

#include "alternative_node.hpp"
#include "simple_declaration.hpp"
//#include "asm_definition.hpp"
//#include "namespace_alias_definition.hpp"
#include "using_declaration.hpp"
#include "using_directive.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		simple_declaration,
//		asm_definition,
//		namespace_alias_definition,
		using_declaration,
		using_directive
	>
	block_declaration_t
;

struct block_declaration_impl: public block_declaration_t
{
	explicit
	block_declaration_impl(simple_declaration&& o);

	explicit
	block_declaration_impl(using_declaration&& o);

	explicit
	block_declaration_impl(using_directive&& o);

	block_declaration_impl(const block_declaration_impl& o);

	block_declaration_impl(block_declaration_impl&& o);

	using block_declaration_t::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
