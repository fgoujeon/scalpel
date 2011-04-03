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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_DECLARATOR_HPP

#include "constant_initializer.hpp"
#include "declarator.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_declarator_declarator
	= declarator >> !(!s >> constant_initializer)
;
*/
typedef
	sequence_node
	<
		declarator,
		optional_node<constant_initializer>
	>
	member_declarator_declarator
;

inline
const declarator&
get_declarator(const member_declarator_declarator& o)
{
	return get<0>(o);
}

inline
const optional_node<constant_initializer>&
get_constant_initializer(const member_declarator_declarator& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

