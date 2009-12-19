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

#ifndef SCALPEL_CPP_SYNTAX_NODES_FUNCTION_TRY_BLOCK_HPP
#define SCALPEL_CPP_SYNTAX_NODES_FUNCTION_TRY_BLOCK_HPP

#include "ctor_initializer.hpp"
#include "compound_statement.hpp"
#include "handler_seq.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
function_try_block
	= str_p("try") >> !s >> !(ctor_initializer >> !s) >> compound_statement >> !s >> handler_seq
;
*/
typedef
	sequence_node
	<
		predefined_text_node<str::try_>,
		optional_node<space>,
		optional_node<ctor_initializer>,
		optional_node<space>,
		compound_statement,
		optional_node<space>,
		handler_seq
	>
	function_try_block
;

}}} //namespace scalpel::cpp::syntax_nodes

#endif
