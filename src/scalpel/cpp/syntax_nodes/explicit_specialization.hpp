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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXPLICIT_SPECIALIZATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXPLICIT_SPECIALIZATION_HPP

#include "common.hpp"
#include "declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		simple_text_node<str::template_>,
		optional_node<space>,
		simple_text_node<str::left_angle_bracket>,
		optional_node<space>,
		simple_text_node<str::right_angle_bracket>,
		optional_node<space>,
		declaration
	>
	explicit_specialization_t
;

/**
explicit_specialization
	= str_p("template") >> !s >> '<' >> !s >> '>' >> !s >> declaration
;
*/
class explicit_specialization: public composite_node
{
	public:
		typedef explicit_specialization_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		explicit_specialization
		(
			simple_text_node<str::template_>&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::left_angle_bracket>&& o2,
			optional_node<space>&& o3,
			simple_text_node<str::right_angle_bracket>&& o4,
			optional_node<space>&& o5,
			declaration&& o6
		);

		explicit_specialization
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		explicit_specialization(const explicit_specialization& o);

		explicit_specialization(explicit_specialization&& o);

		const explicit_specialization&
		operator=(const explicit_specialization& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
