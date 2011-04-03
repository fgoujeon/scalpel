/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2011  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BRACKETED_ABSTRACT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BRACKETED_ABSTRACT_DECLARATOR_HPP

#include "abstract_declarator.hpp"
#include "direct_declarator.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
bracketed_abstract_declarator
	= '(' >> !s >> abstract_declarator >> !s >> ')' >> !(!s >> direct_declarator_last_part)
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::opening_round_bracket>,
		abstract_declarator,
		predefined_text_node<str::closing_round_bracket>,
		optional_node<direct_declarator_last_part>
	>
	bracketed_abstract_declarator
;

inline
const abstract_declarator&
get_abstract_declarator(const bracketed_abstract_declarator& o)
{
	return get<1>(o);
}

inline
const optional_node<direct_declarator_last_part>&
get_last_part(const bracketed_abstract_declarator& o)
{
	return get<3>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

