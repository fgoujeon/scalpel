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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DO_WHILE_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DO_WHILE_STATEMENT_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "statement_fwd.hpp"
#include "expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
do_while_statement
	= str_p("do") >> !s >> statement >> !s >> "while" >> !s >> '(' >> !s >> expression >> !s >> ')' >> !s >> ch_p(';')
;
*/
class do_while_statement: public composite_node
{
	public:
		do_while_statement
		(
			optional_node<space>&& post_do_keyword_space_node,
			statement&& statement_node,
			optional_node<space>&& post_statement_space_node,
			optional_node<space>&& post_while_keyword_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			expression&& expression_node,
			optional_node<space>&& post_expression_space_node,
			optional_node<space>&& post_closing_bracket_space_node
		);

		do_while_statement(const do_while_statement& o);

		do_while_statement(do_while_statement&& o);

		const do_while_statement&
		operator=(const do_while_statement& o);

		inline
		const statement&
		statement_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_do_keyword_space_;
		std::unique_ptr<statement> statement_;
		optional_node<space> post_statement_space_;
		optional_node<space> post_while_keyword_space_;
		optional_node<space> post_opening_bracket_space_;
		expression expression_;
		optional_node<space> post_expression_space_;
		optional_node<space> post_closing_bracket_space_;
};

inline
const statement&
do_while_statement::statement_node() const
{
	return *statement_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
