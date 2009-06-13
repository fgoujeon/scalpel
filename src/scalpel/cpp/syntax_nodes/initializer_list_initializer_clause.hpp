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

#ifndef SCALPEL_CPP_SYNTAX_NODES_INITIALIZER_LIST_INITIALIZER_CLAUSE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_INITIALIZER_LIST_INITIALIZER_CLAUSE_HPP

#include <memory>
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class initializer_list;

/**
initializer_list_initializer_clause
	= ch_p('{') >> !s >> initializer_list >> !s >> !(ch_p(',') >> !s) >> ch_p('}')
	| ch_p('{') >> !s >> ch_p('}')
;
*/
class initializer_list_initializer_clause: public composite_node
{
	public:
		typedef
			sequence_node
			<
				simple_text_node<str::opening_brace>,
				optional_node<space>,
				optional_node<initializer_list>,
				optional_node<space>,
				optional_node<simple_text_node<str::comma>>,
				optional_node<space>,
				simple_text_node<str::closing_brace>
			>
			type
		;
		typedef simple_text_node<str::opening_brace> head_node_t;
		typedef
			sequence_node
			<
				optional_node<space>,
				optional_node<initializer_list>,
				optional_node<space>,
				optional_node<simple_text_node<str::comma>>,
				optional_node<space>,
				simple_text_node<str::closing_brace>
			>
			tail_sequence_node_t;
		;

		initializer_list_initializer_clause
		(
			simple_text_node<str::opening_brace>&& o0,
			optional_node<space>&& o1,
			optional_node<initializer_list>&& o2,
			optional_node<space>&& o3,
			optional_node<simple_text_node<str::comma>>&& o4,
			optional_node<space>&& o5,
			simple_text_node<str::closing_brace>&& o6
		);

		initializer_list_initializer_clause
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		initializer_list_initializer_clause(const initializer_list_initializer_clause& o);

		initializer_list_initializer_clause(initializer_list_initializer_clause&& o);

		~initializer_list_initializer_clause();

		const initializer_list_initializer_clause&
		operator=(const initializer_list_initializer_clause& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
