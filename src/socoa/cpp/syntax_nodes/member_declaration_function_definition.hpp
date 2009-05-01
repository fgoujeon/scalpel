/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_NODES_MEMBER_DECLARATION_FUNCTION_DEFINITION_HPP
#define SOCOA_CPP_SYNTAX_NODES_MEMBER_DECLARATION_FUNCTION_DEFINITION_HPP

#include "composite_node.hpp"
#include "function_definition.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class member_declaration_function_definition: public composite_node
{
	public:
		explicit
		member_declaration_function_definition
		(
			function_definition&& a_function_definition
		);

		member_declaration_function_definition(const member_declaration_function_definition& o);

		member_declaration_function_definition(member_declaration_function_definition&& o);

		const member_declaration_function_definition&
		operator=(const member_declaration_function_definition& o);

		inline
		const function_definition&
		function_definition_node() const;

	private:
		void
		update_node_list();

		function_definition function_definition_;
};

inline
const function_definition&
member_declaration_function_definition::function_definition_node() const
{
	return function_definition_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
