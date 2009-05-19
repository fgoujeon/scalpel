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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SWITCH_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SWITCH_STATEMENT_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "condition.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
switch_statement
	= "switch", "(", condition, ")", statement
;
\endverbatim
*/
class switch_statement: public composite_node
{
	public:
		switch_statement
		(
			optional_node<space>&& post_switch_keyword_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			condition&& condition_node,
			optional_node<space>&& post_condition_space_node,
			optional_node<space>&& post_closing_bracket_space_node,
			statement&& statement_node
		);

		switch_statement(const switch_statement& o);

		switch_statement(switch_statement&& o);

		const switch_statement&
		operator=(const switch_statement& o);

	private:
		void
		update_node_list();

		optional_node<space> post_switch_keyword_space_;
		optional_node<space> post_opening_bracket_space_;
		condition condition_;
		optional_node<space> post_condition_space_;
		optional_node<space> post_closing_bracket_space_;
		statement statement_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
