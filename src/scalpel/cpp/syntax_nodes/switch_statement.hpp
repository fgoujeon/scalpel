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
typedef
	sequence_node
	<
		simple_text_node<str::switch_>,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		condition,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>,
		optional_node<space>,
		statement
	>
	switch_statement_t
;

class switch_statement: public composite_node
{
	public:
		typedef switch_statement_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		switch_statement
		(
			simple_text_node<str::switch_>&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::opening_round_bracket>&& o2,
			optional_node<space>&& o3,
			condition&& o4,
			optional_node<space>&& o5,
			simple_text_node<str::closing_round_bracket>&& o6,
			optional_node<space>&& o7,
			statement&& o8
		);

		switch_statement
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		switch_statement(const switch_statement& o);

		switch_statement(switch_statement&& o);

		const switch_statement&
		operator=(const switch_statement& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
