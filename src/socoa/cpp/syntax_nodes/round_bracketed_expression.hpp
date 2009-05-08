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

#ifndef SOCOA_CPP_SYNTAX_NODES_ROUND_BRACKETED_EXPRESION_HPP
#define SOCOA_CPP_SYNTAX_NODES_ROUND_BRACKETED_EXPRESION_HPP

#include <boost/optional.hpp>
#include "sequence_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class assignment_expression;
typedef sequence_node<assignment_expression, global_nodes::comma> expression;

/**
round_bracketed_expression
	= '(' >> !s >> expression >> !s >> ')'
;
*/
class round_bracketed_expression: public composite_node
{
	public:
		round_bracketed_expression
		(
			boost::optional<space>&& post_opening_bracket_space_node,
			expression&& expression_node,
			boost::optional<space>&& post_expression_space_node
		);

		round_bracketed_expression(const round_bracketed_expression& o);

		round_bracketed_expression(round_bracketed_expression&& o);

		~round_bracketed_expression();

		const round_bracketed_expression&
		operator=(const round_bracketed_expression& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_opening_bracket_space_;
		expression* expression_;
		boost::optional<space> post_expression_space_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
