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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FUNDAMENTAL_TYPE_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FUNDAMENTAL_TYPE_SPECIFIER_HPP

#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		predefined_text_node<str::char_>,
		predefined_text_node<str::wchar_t_>,
		predefined_text_node<str::bool_>,
		predefined_text_node<str::short_>,
		predefined_text_node<str::int_>,
		predefined_text_node<str::long_>,
		predefined_text_node<str::signed_>,
		predefined_text_node<str::unsigned_>,
		predefined_text_node<str::float_>,
		predefined_text_node<str::double_>,
		predefined_text_node<str::void_>
	>
	fundamental_type_specifier
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif

