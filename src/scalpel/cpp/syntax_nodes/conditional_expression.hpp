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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CONDITIONAL_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CONDITIONAL_EXPRESSION_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "expressions_fwd.hpp"
#include "expression_fwd.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class assignment_expression;

/**
\verbatim
conditional_expression
	= logical_or_expression, ["?", expression, ":", assignment_expression]
;
\endverbatim
*/
class conditional_expression: public composite_node
{
	public:
		conditional_expression
		(
			logical_or_expression&& logical_or_expression_node,
			optional_node<space>&& pre_question_mark_space_node,
			optional_node<space>&& post_question_mark_space_node,
			optional_node<expression>&& expression_node,
			optional_node<space>&& post_expression_space_node,
			optional_node<space>&& post_colon_space_node,
			optional_node<assignment_expression>&& assignment_expression_node
		);

		conditional_expression(const conditional_expression& o);

		conditional_expression(conditional_expression&& o);

		~conditional_expression();

		const conditional_expression&
		operator=(const conditional_expression& o);

	private:
		void
		update_node_list();

		logical_or_expression* logical_or_expression_;
		optional_node<space> pre_question_mark_space_;
		optional_node<space> post_question_mark_space_;
		std::unique_ptr<expression> expression_;
		optional_node<space> post_expression_space_;
		optional_node<space> post_colon_space_;
		std::unique_ptr<assignment_expression> assignment_expression_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
