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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PTR_TO_MEMBER_OPERATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PTR_TO_MEMBER_OPERATOR_HPP

#include "nested_name_specifier.hpp"
#include "cv_qualifier_seq.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		nested_name_specifier,
		predefined_text_node<str::asterisk>,
		optional_node<cv_qualifier_seq>
	>
	ptr_to_member_operator
;

inline
bool
has_leading_double_colon(const ptr_to_member_operator& o)
{
	return get<0>(o);
}

inline
const nested_name_specifier&
get_nested_name_specifier(const ptr_to_member_operator& o)
{
	return get<1>(o);
}

inline
const optional_node<cv_qualifier_seq>&
get_cv_qualifier_seq(const ptr_to_member_operator& o)
{
	return get<3>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

