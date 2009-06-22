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

#ifndef SCALPEL_CPP_SYNTAX_NODES_HANDLER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_HANDLER_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "compound_statement.hpp"
#include "space.hpp"
#include "exception_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
handler
	= str_p("catch") >> !s >> '(' >> !s >> exception_declaration >> !s >> ')' >> !s >> compound_statement
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::catch_>,
		optional_node<space>,
		predefined_text_node<str::opening_round_bracket>,
		optional_node<space>,
		exception_declaration,
		optional_node<space>,
		predefined_text_node<str::closing_round_bracket>,
		optional_node<space>,
		compound_statement
	>
	handler_t
;

class handler: public composite_node
{
	public:
		typedef handler_t type;
		typedef handler_t::head_node_t head_node_t;
		typedef handler_t::tail_sequence_node_t tail_sequence_node_t;

		handler
		(
			predefined_text_node<str::catch_>&& o0,
			optional_node<space>&& o1,
			predefined_text_node<str::opening_round_bracket>&& o2,
			optional_node<space>&& o3,
			exception_declaration&& o4,
			optional_node<space>&& o5,
			predefined_text_node<str::closing_round_bracket>&& o6,
			optional_node<space>&& o7,
			compound_statement&& o8
		);

		handler
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		handler(const handler& o);

		handler(handler&& o);

		const handler&
		operator=(const handler& o);

		inline
		const compound_statement&
		compound_statement_node() const;

	private:
		type impl_;
};

const compound_statement&
handler::compound_statement_node() const
{
	return get<8>(impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
