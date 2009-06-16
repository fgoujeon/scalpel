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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_ACCESS_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_ACCESS_SPECIFIER_HPP

#include "common.hpp"
#include "access_specifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_specification_access_specifier
	= access_specifier >> !s >> ':'
;
*/
typedef
	sequence_node
	<
		access_specifier,
		optional_node<space>,
		simple_text_node<str::colon>
	>
	member_specification_access_specifier_t
;

struct member_specification_access_specifier: public member_specification_access_specifier_t
{
	member_specification_access_specifier
	(
		access_specifier&& o0,
		optional_node<space>&& o1,
		simple_text_node<str::colon>&& o2
	):
		member_specification_access_specifier_t(o0, o1, o2)
	{
	}

	member_specification_access_specifier
	(
		head_node_t&& head,
		tail_sequence_node_t&& tail
	):
		member_specification_access_specifier_t(head, tail)
	{
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
