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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_ACCESS_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_ACCESS_SPECIFIER_HPP

#include "access_specifier.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
member_specification_access_specifier
	= access_specifier >> !s >> ':'
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	member_specification_access_specifier,
	(access_specifier)
	(predefined_text_node<str::colon>)
)

const access_specifier&
get_access_specifier(const member_specification_access_specifier& o);

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

