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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TYPE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TYPE_ID_HPP

#include "type_specifier_seq.hpp"
#include "abstract_declarator.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
type_id
	= type_specifier_seq >> !(!s >> abstract_declarator)
;
*/
typedef
	sequence_node
	<
		type_specifier_seq,
		optional_node<abstract_declarator>
	>
	type_id
;

inline
const type_specifier_seq&
get_type_specifier_seq(const type_id& o)
{
	return get<0>(o);
}

inline
const optional_node<abstract_declarator>&
get_abstract_declarator(const type_id& o)
{
	return get<1>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

