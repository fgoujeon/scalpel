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

#ifndef SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_IDENTIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_IDENTIFIER_HPP

#include "common.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
qualified_identifier
	= str_p("::") >> !s >> identifier
;
*/
typedef
	sequence_node
	<
		simple_text_node<str::double_colon>,
		optional_node<space>,
		identifier
	>
	qualified_identifier_t
;

class qualified_identifier: public composite_node
{
	public:
		typedef qualified_identifier_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		qualified_identifier
		(
			simple_text_node<str::double_colon>&& o0,
			optional_node<space>&& o1,
			identifier&& o2
		);

		qualified_identifier
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		qualified_identifier(const qualified_identifier& o);

		qualified_identifier(qualified_identifier&& o);

		const qualified_identifier&
		operator=(const qualified_identifier& o);

		inline
		const identifier&
	   	identifier_node() const;

	private:
		type impl_;
};

const identifier&
qualified_identifier::identifier_node() const
{
	return get<2>(impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
