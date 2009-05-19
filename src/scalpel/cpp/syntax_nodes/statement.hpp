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

class statement_impl;

class statement: public composite_node
{
	public:
		explicit
		statement(labeled_statement&& o);

		explicit
		statement(expression_statement&& o);

		explicit
		statement(compound_statement&& o);

		explicit
		statement(selection_statement&& o);

		explicit
		statement(iteration_statement&& o);

		explicit
		statement(jump_statement&& o);

		explicit
		statement(block_declaration&& o);

		explicit
		statement(try_block&& o);

		statement(const statement& o);

		statement(statement&& o);

		~statement();

		const statement&
		operator=(const statement& o);

	private:
		statement_impl* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
