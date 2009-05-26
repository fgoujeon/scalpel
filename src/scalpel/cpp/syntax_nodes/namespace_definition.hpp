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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NAMESPACE_DEFINITION_HPP

#include "common.hpp"
#include "identifier.hpp"
#include "declaration_fwd.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef list_node<declaration> declaration_seq;

typedef
	sequence_node
	<
		simple_text_node<str::namespace_>,
		optional_node<space>,
		optional_node<identifier>,
		optional_node<space>,
		simple_text_node<str::opening_brace>,
		optional_node<space>,
		optional_node<declaration_seq>,
		optional_node<space>,
		simple_text_node<str::closing_brace>
	>
	namespace_definition_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		optional_node<identifier>,
		optional_node<space>,
		simple_text_node<str::opening_brace>,
		optional_node<space>,
		optional_node<declaration_seq>,
		optional_node<space>,
		simple_text_node<str::closing_brace>
	>
	namespace_definition_tail_t
;

/**
namespace_definition
	= "namespace", [identifier], "{", [declaration_seq], "}"
;
*/
class namespace_definition: public composite_node
{
	public:
		typedef namespace_definition_t type;
		typedef simple_text_node<str::namespace_> head_node_t;
		typedef namespace_definition_tail_t tail_sequence_node_t;

		namespace_definition
		(
			simple_text_node<str::namespace_>&& o0,
			optional_node<space>&& o1,
			optional_node<identifier>&& o2,
			optional_node<space>&& o3,
			simple_text_node<str::opening_brace>&& o4,
			optional_node<space>&& o5,
			optional_node<declaration_seq>&& o6,
			optional_node<space>&& o7,
			simple_text_node<str::closing_brace>&& o8
		);

		namespace_definition(head_node_t&& head, tail_sequence_node_t&& tail);

		namespace_definition(const namespace_definition& o);

		namespace_definition(namespace_definition&& o);

		~namespace_definition();

		const namespace_definition&
		operator=(const namespace_definition& o);

		const optional_node<identifier>&
	   	identifier_node() const;

		const optional_node<list_node<declaration>>&
		declaration_seq_node() const;

	private:
		namespace_definition_t* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
