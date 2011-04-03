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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TRY_BLOCK_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TRY_BLOCK_HPP

#include "compound_statement.hpp"
#include "handler_seq.hpp"
#include "common.hpp"

#include "detail/macros/sequence_node_pimpl_declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
try_block
	= "try", compound_statement, handler_seq
;
*/
SCALPEL_SEQUENCE_NODE_PIMPL_DECLARATION
(
	try_block,
	(predefined_text_node<str::try_>)
	(compound_statement)
	(handler_seq)
)

inline
const compound_statement&
get_compound_statement(const try_block& o)
{
	return get<1>(o);
}

inline
const handler_seq&
get_handler_seq(const try_block& o)
{
	return get<2>(o);
}

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/sequence_node_pimpl_declaration_undef.hpp"

#endif

