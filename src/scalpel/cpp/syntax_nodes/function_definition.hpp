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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FUNCTION_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FUNCTION_DEFINITION_HPP

#include "common.hpp"
#include "simple_function_definition.hpp"
#include "try_block_function_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
function_definition
	= simple_function_definition
	| try_block_function_definition
;
\endverbatim
*/
class function_definition: public composite_node
{
	public:
		typedef
			alternative_node
			<
				simple_function_definition,
				try_block_function_definition
			>
			type
		;
		typedef
			simple_function_definition
			head_node_t
		;
		typedef
			alternative_node
			<
				try_block_function_definition
			>
			tail_alternative_node_t
		;

		function_definition(simple_function_definition&& o);

		function_definition(try_block_function_definition&& o);

		function_definition(const function_definition& o);

		function_definition(function_definition&& o);

		const function_definition&
		operator=(const function_definition& o);

		void
		get(boost::optional<const simple_function_definition&>& o) const;

		void
		get(boost::optional<const try_block_function_definition&>& o) const;

	private:
		type impl_;
};

const declarator&
get_declarator(const function_definition& o);

}}} //namespace scalpel::cpp::syntax_nodes

#endif
