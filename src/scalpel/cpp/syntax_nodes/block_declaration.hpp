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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BLOCK_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BLOCK_DECLARATION_HPP

#include <boost/optional.hpp>
#include "common.hpp"
#include "asm_definition.hpp"
#include "namespace_alias_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class simple_declaration;
class using_declaration;
class using_directive;

typedef
	alternative_node
	<
		simple_declaration,
		asm_definition,
		namespace_alias_definition,
		using_declaration,
		using_directive
	>
	block_declaration_t
;

typedef
	alternative_node
	<
		asm_definition,
		namespace_alias_definition,
		using_declaration,
		using_directive
	>
	block_declaration_tail_t
;

/**
block_declaration
	= asm_definition
	| simple_declaration
	| namespace_alias_definition
	| using_declaration
	| using_directive
;
*/
class block_declaration: public composite_node
{
	public:
		typedef block_declaration_t type;
		typedef simple_declaration head_node_t;
		typedef block_declaration_tail_t tail_alternative_node_t;

		block_declaration(simple_declaration&& o);

		block_declaration(asm_definition&& o);

		block_declaration(namespace_alias_definition&& o);

		block_declaration(using_declaration&& o);

		block_declaration(using_directive&& o);

		block_declaration(const block_declaration& o);

		block_declaration(block_declaration&& o);

		~block_declaration();

		const block_declaration&
		operator=(const block_declaration& o);

		void
		get(boost::optional<const simple_declaration&>& node) const;

		void
		get(boost::optional<const asm_definition&>& node) const;

		void
		get(boost::optional<const namespace_alias_definition&>& node) const;

		void
		get(boost::optional<const using_declaration&>& node) const;

		void
		get(boost::optional<const using_directive&>& node) const;

	private:
		type* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
