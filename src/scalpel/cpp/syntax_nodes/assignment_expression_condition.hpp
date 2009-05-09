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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ASSIGNMENT_EXPRESSION_CONDITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ASSIGNMENT_EXPRESSION_CONDITION_HPP

#include "composite_node.hpp"
#include "type_specifier_seq.hpp"
#include "space.hpp"
#include "declarator.hpp"
#include "assignment_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
assignment_expression_condition
	= type_specifier_seq, declarator, "=", assignment_expression
;
\endverbatim
*/
class assignment_expression_condition: public composite_node
{
	public:
		assignment_expression_condition
		(
			type_specifier_seq&& type_specifier_seq_node,
			boost::optional<space>&& post_type_specifier_seq_space_node,
			declarator&& declarator_node,
			boost::optional<space>&& post_declarator_space_node,
			boost::optional<space>&& post_equal_space_node,
			assignment_expression&& assignment_expression_node
		);

		assignment_expression_condition(const assignment_expression_condition& o);

		assignment_expression_condition(assignment_expression_condition&& o);

		const assignment_expression_condition&
		operator=(const assignment_expression_condition& o);

	private:
		void
		update_node_list();

		type_specifier_seq type_specifier_seq_;
		boost::optional<space> post_type_specifier_seq_space_;
		declarator declarator_;
		boost::optional<space> post_declarator_space_;
		boost::optional<space> post_equal_space_;
		assignment_expression assignment_expression_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
