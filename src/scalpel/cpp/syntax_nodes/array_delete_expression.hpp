/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_ARRAY_DELETE_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ARRAY_DELETE_EXPRESSION_HPP

#include "cast_expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
array_delete_expression
	= ["::"], "delete", "[", "]", cast_expression
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		predefined_text_node<str::delete_>,
		predefined_text_node<str::opening_square_bracket>,
		predefined_text_node<str::closing_square_bracket>,
		cast_expression
	>
	array_delete_expression
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
