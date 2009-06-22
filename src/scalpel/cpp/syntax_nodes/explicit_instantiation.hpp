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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXPLICIT_INSTANTIATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXPLICIT_INSTANTIATION_HPP

#include "common.hpp"
#include "declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::extern_>>,
		optional_node<space>,
		predefined_text_node<str::template_>,
		optional_node<space>,
		declaration
	>
	explicit_instantiation_t
;

/**
explicit_instantiation
	= !(str_p("extern") >> !s) >> str_p("template") >> !s >> declaration
;
*/
class explicit_instantiation: public composite_node
{
	public:
		typedef explicit_instantiation_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		explicit_instantiation
		(
			optional_node<predefined_text_node<str::extern_>>&& o0,
			optional_node<space>&& o1,
			predefined_text_node<str::template_>&& o2,
			optional_node<space>&& o3,
			declaration&& o4
		);

		explicit_instantiation
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		explicit_instantiation(const explicit_instantiation& o);

		explicit_instantiation(explicit_instantiation&& o);

		const explicit_instantiation&
		operator=(const explicit_instantiation& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
