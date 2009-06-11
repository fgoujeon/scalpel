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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ENUMERATOR_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ENUMERATOR_DEFINITION_HPP

#include <memory>
#include "common.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class conditional_expression;

typedef
	sequence_node
	<
		identifier,
		optional_node<space>,
		optional_node<simple_text_node<str::equal>>,
		optional_node<space>,
		optional_node<conditional_expression>
	>
	enumerator_definition_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		optional_node<simple_text_node<str::equal>>,
		optional_node<space>,
		optional_node<conditional_expression>
	>
	enumerator_definition_tail_t
;

/**
enumerator_definition
	= identifier >> !s >> !('=' >> !s >> conditional_expression)
;
*/
class enumerator_definition: public composite_node
{
	public:
		typedef enumerator_definition_t type;
		typedef identifier head_node_t;
		typedef enumerator_definition_tail_t tail_sequence_node_t;

		enumerator_definition
		(
			identifier&& o0,
			optional_node<space>&& o1,
			optional_node<simple_text_node<str::equal>>&& o2,
			optional_node<space>&& o3,
			optional_node<conditional_expression>&& o4
		);

		enumerator_definition
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		enumerator_definition(const enumerator_definition& o);

		enumerator_definition(enumerator_definition&& o);

		~enumerator_definition();

		const enumerator_definition&
		operator=(const enumerator_definition& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
