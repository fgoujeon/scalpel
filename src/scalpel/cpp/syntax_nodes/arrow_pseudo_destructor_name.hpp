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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ARROW_PSEUDO_DESTRUCTOR_NAME_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ARROW_PSEUDO_DESTRUCTOR_NAME_HPP

#include "common.hpp"
//#include "pseudo_destructor_name.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
arrow_pseudo_destructor_name
	= "->" >> !s >> pseudo_destructor_name
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::arrow>,
		optional_node<space>/*,
		pseudo_destructor_name*/
	>
	arrow_pseudo_destructor_name
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
