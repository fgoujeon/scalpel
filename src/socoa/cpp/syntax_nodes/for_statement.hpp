/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP
#define SOCOA_CPP_SYNTAX_NODES_FOR_STATEMENT_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "expression.hpp"
#include "for_init_statement.hpp"
#include "condition.hpp"
#include "statement_fwd.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
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
			boost::optional<space>&& post_for_keyword_space_node,
			boost::optional<space>&& post_opening_bracket_space_node,
			boost::optional<for_init_statement>&& for_init_statement_node,
			boost::optional<space>&& post_for_init_statement_space_node,
			boost::optional<condition>&& condition_node,
			boost::optional<space>&& post_condition_space_node,
			boost::optional<space>&& post_semicolon_space_node,
			boost::optional<expression>&& expression_node,
			boost::optional<space>&& post_expression_space_node,
			boost::optional<space>&& post_closing_bracket_space_node,
			statement&& statement_node
		);

		for_statement(const for_statement& o);

		for_statement(for_statement&& o);

		const for_statement&
		operator=(const for_statement& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_for_keyword_space_;
		boost::optional<space> post_opening_bracket_space_;
		boost::optional<for_init_statement> for_init_statement_;
		boost::optional<space> post_for_init_statement_space_;
		boost::optional<condition> condition_;
		boost::optional<space> post_condition_space_;
		boost::optional<space> post_semicolon_space_;
		boost::optional<expression> expression_;
		boost::optional<space> post_expression_space_;
		boost::optional<space> post_closing_bracket_space_;
		std::unique_ptr<statement> statement_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
