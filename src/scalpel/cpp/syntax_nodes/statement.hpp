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

#ifndef SCALPEL_CPP_SYNTAX_NODES_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_STATEMENT_HPP

#include "composite_node.hpp"
#include "jump_statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class labeled_statement;
class expression_statement;
class compound_statement;
class try_block;
class iteration_statement;
class selection_statement;
class block_declaration;

typedef
	alternative_node
	<
		labeled_statement,
		expression_statement,
		compound_statement,
		selection_statement,
		iteration_statement,
		jump_statement,
		block_declaration,
		try_block
	>
	statement_t
;

typedef
	alternative_node
	<
		expression_statement,
		compound_statement,
		selection_statement,
		iteration_statement,
		jump_statement,
		block_declaration,
		try_block
	>
	statement_tail_t
;

class statement: public composite_node
{
	public:
		typedef statement_t type;
		typedef labeled_statement head_node_t;
		typedef statement_tail_t tail_alternative_node_t;

		statement(labeled_statement&& o);

		statement(expression_statement&& o);

		statement(compound_statement&& o);

		statement(selection_statement&& o);

		statement(iteration_statement&& o);

		statement(jump_statement&& o);

		statement(block_declaration&& o);

		statement(try_block&& o);

		statement(const statement& o);

		statement(statement&& o);

		~statement();

		const statement&
		operator=(const statement& o);

		void
		get(boost::optional<const labeled_statement&>& node) const;

		void
		get(boost::optional<const expression_statement&>& node) const;

		void
		get(boost::optional<const compound_statement&>& node) const;

		void
		get(boost::optional<const selection_statement&>& node) const;

		void
		get(boost::optional<const iteration_statement&>& node) const;

		void
		get(boost::optional<const jump_statement&>& node) const;

		void
		get(boost::optional<const block_declaration&>& node) const;

		void
		get(boost::optional<const try_block&>& node) const;

	private:
		type* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
