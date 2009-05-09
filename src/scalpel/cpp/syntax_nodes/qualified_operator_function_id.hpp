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

#ifndef SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_OPERATOR_FUNCTION_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_QUALIFIED_OPERATOR_FUNCTION_ID_HPP

#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class qualified_operator_function_id: public composite_node
{
    public:
		qualified_operator_function_id();

		qualified_operator_function_id(const qualified_operator_function_id& o);

		qualified_operator_function_id(qualified_operator_function_id&& o);

		const qualified_operator_function_id&
		operator=(const qualified_operator_function_id& o);

};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
