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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "expression.hpp"
#include "for_init_statement.hpp"
#include "condition.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
for_statement
	= "for", "(", for_init_statement, [condition], ";", [expression], ")", statement
;
\endverbatim
*/
class for_statement: public composite_node
{
	public:
		for_statement
		(
			optional_node<space>&& post_for_keyword_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			optional_node<for_init_statement>&& for_init_statement_node,
			optional_node<space>&& post_for_init_statement_space_node,
			optional_node<condition>&& condition_node,
			optional_node<space>&& post_condition_space_node,
			optional_node<space>&& post_semicolon_space_node,
			optional_node<expression>&& expression_node,
			optional_node<space>&& post_expression_space_node,
			optional_node<space>&& post_closing_bracket_space_node,
			statement&& statement_node
		);

		for_statement(const for_statement& o);

		for_statement(for_statement&& o);

		const for_statement&
		operator=(const for_statement& o);

		inline
		const statement&
		statement_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_for_keyword_space_;
		optional_node<space> post_opening_bracket_space_;
		optional_node<for_init_statement> for_init_statement_;
		optional_node<space> post_for_init_statement_space_;
		optional_node<condition> condition_;
		optional_node<space> post_condition_space_;
		optional_node<space> post_semicolon_space_;
		optional_node<expression> expression_;
		optional_node<space> post_expression_space_;
		optional_node<space> post_closing_bracket_space_;
		statement statement_;
};

const statement&
for_statement::statement_node() const
{
	return statement_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
