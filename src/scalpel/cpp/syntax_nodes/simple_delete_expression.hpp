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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DELETE_EXPRESION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DELETE_EXPRESION_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class cast_expression;

/**
simple_delete_expression
	= !(str_p("::") >> !s) >> "delete" >> !s >> cast_expression
;
*/
class simple_delete_expression: public composite_node
{
	public:
		simple_delete_expression
		(
			bool leading_double_colon,
			optional_node<space>&& post_double_colon_space_node,
			optional_node<space>&& post_delete_keyword_space_node,
			cast_expression&& cast_expression_node
		);

		simple_delete_expression(const simple_delete_expression& o);

		simple_delete_expression(simple_delete_expression&& o);

		const simple_delete_expression&
		operator=(const simple_delete_expression& o);

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		optional_node<space> post_double_colon_space_;
		optional_node<space> post_delete_keyword_space_;
		std::unique_ptr<cast_expression> cast_expression_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
