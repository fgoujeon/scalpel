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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ARRAY_DELETE_EXPRESION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ARRAY_DELETE_EXPRESION_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class cast_expression;

/**
array_delete_expression
	= !(str_p("::") >> !s) >> "delete" >> !s >> '[' >> !s >> ']' >> !s >> cast_expression
;
*/
class array_delete_expression: public composite_node
{
	public:
		array_delete_expression
		(
			bool leading_double_colon,
			boost::optional<space>&& post_double_colon_space_node,
			boost::optional<space>&& post_delete_keyword_space_node,
			boost::optional<space>&& post_opening_bracket_space_node,
			boost::optional<space>&& post_closing_bracket_space_node,
			cast_expression&& cast_expression_node
		);

		array_delete_expression(const array_delete_expression& o);

		array_delete_expression(array_delete_expression&& o);

		const array_delete_expression&
		operator=(const array_delete_expression& o);

	private:
		void
		update_node_list();

		bool leading_double_colon_;
		boost::optional<space> post_double_colon_space_;
		boost::optional<space> post_delete_keyword_space_;
		boost::optional<space> post_opening_bracket_space_;
		boost::optional<space> post_closing_bracket_space_;
		std::unique_ptr<cast_expression> cast_expression_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
