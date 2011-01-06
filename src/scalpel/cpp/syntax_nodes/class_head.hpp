/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_HEAD_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_HEAD_HPP

#include "class_key.hpp"
#include "nested_name_specifier.hpp"
#include "template_id.hpp"
#include "identifier.hpp"
#include "base_clause.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
class_head
	= class_key >> !(!s >> nested_name_specifier) >> !s >> identifier_or_template_id >> !(!s >> base_clause)
	| class_key >> !(!s >> base_clause)
;
\endverbatim
*/
typedef
	sequence_node
	<
		class_key,
		optional_node<space>,
		optional_node<nested_name_specifier>,
		optional_node<space>,
		optional_node<identifier_or_template_id>,
		optional_node<space>,
		optional_node<base_clause>
	>
	class_head
;

inline
const class_key&
get_class_key(const class_head& o)
{
	return get<0>(o);
}

inline
const optional_node<nested_name_specifier>&
get_nested_name_specifier(const class_head& o)
{
	return get<2>(o);
}

inline
const optional_node<identifier_or_template_id>&
get_identifier_or_template_id(const class_head& o)
{
	return get<4>(o);
}

inline
const optional_node<base_clause>&
get_base_clause(const class_head& o)
{
	return get<6>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
