/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_PTR_PTR_OPERATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_PTR_PTR_OPERATOR_HPP

#include "nested_name_specifier.hpp"
#include "cv_qualifier_seq.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
ptr_ptr_operator
	= ch_p('*') >> !(!s >> cv_qualifier_seq)
	| !(str_p("::") >> !s) >> nested_name_specifier >> !s >> '*' >> !(!s >> cv_qualifier_seq)
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<space>,
		optional_node<nested_name_specifier>,
		optional_node<space>,
		predefined_text_node<str::asterisk>,
		optional_node<space>,
		optional_node<cv_qualifier_seq>
	>
	ptr_ptr_operator
;

inline
const optional_node<cv_qualifier_seq>&
get_cv_qualifier_seq(const ptr_ptr_operator& o)
{
	return get<6>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

