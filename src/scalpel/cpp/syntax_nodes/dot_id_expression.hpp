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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DOT_ID_EXPRESSION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DOT_ID_EXPRESSION_HPP

#include "id_expression.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
dot_id_expression
	= '.' >> !s >> !(str_p("template") >> !s) >> id_expression
;
\endverbatim
*/
typedef
	sequence_node
	<
		predefined_text_node<str::dot>,
		optional_node<predefined_text_node<str::template_>>,
		id_expression
	>
	dot_id_expression
;

inline
bool
has_template_keyword(const dot_id_expression& o)
{
	return get<1>(o);
}

inline
const id_expression&
get_id_expression(const dot_id_expression& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

