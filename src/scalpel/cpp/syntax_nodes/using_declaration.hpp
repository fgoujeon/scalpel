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

#ifndef SCALPEL_CPP_SYNTAX_NODES_USING_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_USING_DECLARATION_HPP

#include "nested_name_specifier.hpp"
#include "unqualified_id.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
using_declaration
	= "using" >> !s >> !(str_p("typename") >> !s) >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> unqualified_id >> !s >> ch_p(';')
	| "using" >> !s >> str_p("::") >> !s >> unqualified_id >> !s >> ch_p(';')
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::using_>,
		optional_node<predefined_text_node<str::typename_>>,
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<nested_name_specifier>,
		unqualified_id,
		predefined_text_node<str::semicolon>
	>
	using_declaration
;

inline
bool
has_typename_keyword(const using_declaration& o)
{
	return get<1>(o);
}

inline
bool
has_leading_double_colon(const using_declaration& o)
{
	return get<2>(o);
}

inline
const optional_node<nested_name_specifier>&
get_nested_name_specifier(const using_declaration& o)
{
	return get<3>(o);
}

inline
const unqualified_id&
get_unqualified_id(const using_declaration& o)
{
	return get<4>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

