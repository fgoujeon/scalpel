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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEM_INITIALIZER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEM_INITIALIZER_HPP

#include "common.hpp"
#include "mem_initializer_id.hpp"
#include "expression_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
mem_initializer
	= mem_initializer_id >> !s >> '(' >> !s >> !(expression_list >> !s) >> ')'
;
*/
typedef
	sequence_node
	<
		mem_initializer_id,
		optional_node<space>,
		simple_text_node<str::opening_round_bracket>,
		optional_node<space>,
		optional_node<expression_list>,
		optional_node<space>,
		simple_text_node<str::closing_round_bracket>
	>
	mem_initializer
;
/*
class mem_initializer: public composite_node
{
	public:
		explicit
		mem_initializer
		(
			mem_initializer_id&& mem_initializer_id_node,
			optional_node<space>&& post_mem_initializer_id_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			optional_node<expression_list>&& expression_list_node,
			optional_node<space>&& post_expression_list_space_node
		);

		mem_initializer(const mem_initializer& o);

		mem_initializer(mem_initializer&& o);

		const mem_initializer&
		operator=(const mem_initializer& o);

		inline
		const mem_initializer_id&
		mem_initializer_id_node() const;

	private:
		void
		update_node_list();

		mem_initializer_id mem_initializer_id_;
		optional_node<space> post_mem_initializer_id_space_;
		optional_node<space> post_opening_bracket_space_;
		optional_node<expression_list> expression_list_;
		optional_node<space> post_expression_list_space_;
};

inline
const mem_initializer_id&
mem_initializer::mem_initializer_id_node() const
{
	return mem_initializer_id_;
}
*/
}}} //namespace scalpel::cpp::syntax_nodes

#endif
