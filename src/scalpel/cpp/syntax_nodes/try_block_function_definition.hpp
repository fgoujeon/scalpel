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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TRY_BLOCK_FUNCTION_DEFINITION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TRY_BLOCK_FUNCTION_DEFINITION_HPP

#include "common.hpp"
#include "decl_specifier_seq.hpp"
#include "declarator.hpp"
#include "function_try_block.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
try_block_function_definition
	= [decl_specifier_seq], declarator, function_try_block
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
		function_try_block
	>
	try_block_function_definition
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif