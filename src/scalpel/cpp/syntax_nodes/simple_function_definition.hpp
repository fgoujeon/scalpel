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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_FUNCTION_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_FUNCTION_DEFINITION_HPP

#include "common.hpp"
#include "decl_specifier_seq.hpp"
#include "ctor_initializer.hpp"
#include "compound_statement.hpp"
#include "declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
simple_function_definition
	= [decl_specifier_seq], declarator, [ctor_initializer], compound_statement
;
\endverbatim
*/
typedef
	sequence_node
	<
		optional_node<decl_specifier_seq>,
		optional_node<space>,
		declarator,
		optional_node<space>,
		optional_node<ctor_initializer>,
		optional_node<space>,
		compound_statement
	>
	simple_function_definition
;

inline
const optional_node<decl_specifier_seq>&
get_decl_specifier_seq(const simple_function_definition& o)
{
	return get<0>(o);
}

inline
const compound_statement&
get_compound_statement(const simple_function_definition& o)
{
	return get<6>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
