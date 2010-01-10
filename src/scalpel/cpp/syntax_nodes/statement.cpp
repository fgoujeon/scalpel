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

#include "statement.hpp"
#include "labeled_statement.hpp"
#include "expression_statement.hpp"
#include "compound_statement.hpp"
#include "selection_statement.hpp"
#include "iteration_statement.hpp"
#include "jump_statement.hpp"
#include "block_declaration.hpp"
#include "try_block.hpp"

#include "detail/macros/alternative_node_pimpl_definition.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

SCALPEL_ALTERNATIVE_NODE_PIMPL_DEFINITION
(
	statement,
	(labeled_statement)
	(expression_statement)
	(compound_statement)
	(selection_statement)
	(iteration_statement)
	(jump_statement)
	(block_declaration)
	(try_block)
)

}}} //namespace scalpel::cpp::syntax_nodes

#include "detail/macros/alternative_node_pimpl_definition_undef.hpp"

