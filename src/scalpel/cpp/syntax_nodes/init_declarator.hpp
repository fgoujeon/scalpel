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

#ifndef SCALPEL_CPP_SYNTAX_NODES_INIT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_INIT_DECLARATOR_HPP

#include "declarator.hpp"
#include "initializer.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
init_declarator
	= declarator, [initializer]
;
\endverbatim
*/
typedef
	sequence_node
	<
		declarator,
		optional_node<initializer>
	>
	init_declarator
;

inline
const declarator&
get_declarator(const init_declarator& o)
{
	return get<0>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

