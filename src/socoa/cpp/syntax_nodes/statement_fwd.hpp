/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_NODES_STATEMENT_FWD_HPP
#define SOCOA_CPP_SYNTAX_NODES_STATEMENT_FWD_HPP

#include "alternative_node.hpp"
#include "block_declaration_fwd.hpp"
#include "iteration_statement_fwd.hpp"
#include "jump_statement.hpp"
#include "labeled_statement_fwd.hpp"
#include "selection_statement_fwd.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class expression_statement;
class compound_statement;
class try_block;

typedef
	alternative_node
	<
		labeled_statement,
		expression_statement,
		compound_statement,
		selection_statement,
		iteration_statement,
		jump_statement,
		block_declaration,
		try_block
	>
	statement
;

}}} //namespace socoa::cpp::syntax_nodes

#endif
