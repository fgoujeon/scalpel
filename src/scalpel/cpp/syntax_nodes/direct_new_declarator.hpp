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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DIRECT_NEW_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DIRECT_NEW_DECLARATOR_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "expression.hpp"
#include "conditional_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
direct_new_declarator
	= '[' >> !s >> expression >> !s >> ']' >> !(!s >> '[' >> !s >> conditional_expression >> !s >> ']')
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::opening_square_bracket>,
		optional_node<space>,
		expression,
		optional_node<space>,
		predefined_text_node<str::closing_square_bracket>,
		optional_node<space>,
		optional_node<predefined_text_node<str::opening_square_bracket>>,
		optional_node<space>,
		optional_node<conditional_expression>,
		optional_node<space>,
		optional_node<predefined_text_node<str::closing_square_bracket>>
	>
	direct_new_declarator_t
;

class direct_new_declarator: public direct_new_declarator_t
{
	public:
		typedef direct_new_declarator_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		direct_new_declarator
		(
			predefined_text_node<str::opening_square_bracket>&& o1,
			optional_node<space>&& o2,
			expression&& o3,
			optional_node<space>&& o4,
			predefined_text_node<str::closing_square_bracket>&& o5,
			optional_node<space>&& o6,
			optional_node<predefined_text_node<str::opening_square_bracket>>&& o7,
			optional_node<space>&& o8,
			optional_node<conditional_expression>&& o9,
			optional_node<space>&& o10,
			optional_node<predefined_text_node<str::closing_square_bracket>>&& o11
		):
			type
			(
				o1,
				o2,
				o3,
				o4,
				o5,
				o6,
				o7,
				o8,
				o9,
				o10,
				o11
			)
		{
		}

		direct_new_declarator
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		):
			type(head, tail)
		{
		}

		direct_new_declarator(const direct_new_declarator& o):
			type(o)
		{
		}

		direct_new_declarator(direct_new_declarator&& o):
			type(o)
		{
		}

		using type::operator=;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
