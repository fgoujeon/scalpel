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

#ifndef SOCOA_CPP_SYNTAX_NODES_IF_STATEMENT_HPP
#define SOCOA_CPP_SYNTAX_NODES_IF_STATEMENT_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "condition.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class statement;

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
			boost::optional<space>&& post_if_keyword_space_node,
			boost::optional<space>&& post_opening_bracket_space_node,
			condition&& condition_node,
			boost::optional<space>&& post_condition_space_node,
			boost::optional<space>&& post_closing_bracket_space_node,
			statement&& statement_node,
			boost::optional<space>&& pre_else_keyword_space_node,
			boost::optional<statement>&& else_statement_node,
			boost::optional<space>&& post_else_keyword_space_node
		);

		if_statement(const if_statement& o);

		if_statement(if_statement&& o);

		const if_statement&
		operator=(const if_statement& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_if_keyword_space_;
		boost::optional<space> post_opening_bracket_space_;
		condition condition_;
		boost::optional<space> post_condition_space_;
		boost::optional<space> post_closing_bracket_space_;
		std::unique_ptr<statement> statement_;
		boost::optional<space> pre_else_keyword_space_;
		std::unique_ptr<statement> else_statement_;
		boost::optional<space> post_else_keyword_space_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
