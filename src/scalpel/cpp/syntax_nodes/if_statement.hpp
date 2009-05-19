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

#ifndef SCALPEL_CPP_SYNTAX_NODES_IF_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_IF_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "condition.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
if_statement
	= "if", "(", condition, ")", statement, ["else", statement]
;
\endverbatim
*/
class if_statement: public composite_node
{
	public:
		if_statement
		(
			optional_node<space>&& post_if_keyword_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			condition&& condition_node,
			optional_node<space>&& post_condition_space_node,
			optional_node<space>&& post_closing_bracket_space_node,
			statement&& statement_node,
			optional_node<space>&& pre_else_keyword_space_node,
			optional_node<statement>&& else_statement_node,
			optional_node<space>&& post_else_keyword_space_node
		);

		if_statement(const if_statement& o);

		if_statement(if_statement&& o);

		const if_statement&
		operator=(const if_statement& o);

		inline
		const statement&
		statement_node() const;

		const optional_node<statement>&
		else_statement_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_if_keyword_space_;
		optional_node<space> post_opening_bracket_space_;
		condition condition_;
		optional_node<space> post_condition_space_;
		optional_node<space> post_closing_bracket_space_;
		std::unique_ptr<statement> statement_;
		optional_node<space> pre_else_keyword_space_;
		optional_node<space> post_else_keyword_space_;
		std::unique_ptr<optional_node<statement>> else_statement_;
};

const statement&
if_statement::statement_node() const
{
	return *statement_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
