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

#ifndef SCALPEL_CPP_SYNTAX_NODES_OPERATOR_FUNCTION_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_OPERATOR_FUNCTION_ID_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "operator_.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
operator_function_id
	= str_p("operator") >> !s >> operator_
;
*/
class operator_function_id: public composite_node
{
    public:
		operator_function_id
		(
			optional_node<space>&& post_operator_keyword_space_node,
			operator_&& operator_node
		);

		operator_function_id(const operator_function_id& o);

		operator_function_id(operator_function_id&& o);

		const operator_function_id&
		operator=(const operator_function_id& o);

    private:
		void
		update_node_list();

		optional_node<space> post_operator_keyword_space_;
		operator_ operator__;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
