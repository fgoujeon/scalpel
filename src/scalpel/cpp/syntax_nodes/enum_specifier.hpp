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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ENUM_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ENUM_SPECIFIER_HPP

#include "identifier.hpp"
#include "enumerator_list.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
enum_specifier
	= str_p("enum") >> !s >> !(identifier >> !s) >> ch_p('{') >> !s >> !(enumerator_list >> !s) >> !(ch_p(',') >> !s) >> ch_p('}')
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::basic_enum>,
		optional_node<identifier>,
		predefined_text_node<str::opening_brace>,
		optional_node<enumerator_list>,
		optional_node<predefined_text_node<str::comma>>,
		predefined_text_node<str::closing_brace>
	>
	enum_specifier
;

inline
const optional_node<identifier>&
get_identifier(const enum_specifier& o)
{
	return get<1>(o);
}

inline
const optional_node<enumerator_list>&
get_enumerator_list(const enum_specifier& o)
{
	return get<3>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif

