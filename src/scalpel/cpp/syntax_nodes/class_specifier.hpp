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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP

#include "class_head.hpp"
#include "member_specification.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
class_specifier
	= class_head, "{", [member_specification], "}"
;
\endverbatim
*/

SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	class_specifier,
	(class_head)
	(predefined_text_node<str::opening_brace>)
	(optional_node<member_specification>)
	(predefined_text_node<str::closing_brace>)
)

inline
const class_head&
get_class_head(const class_specifier& o)
{
	return get<0>(o);
}

inline
const optional_node<member_specification>&
get_member_specification(const class_specifier& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

