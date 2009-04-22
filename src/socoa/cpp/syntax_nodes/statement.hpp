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

#ifndef SOCOA_CPP_SYNTAX_NODES_STATEMENT_HPP
#define SOCOA_CPP_SYNTAX_NODES_STATEMENT_HPP

#include "alternative_node.hpp"
#include "labeled_statement.hpp"
#include "expression_statement.hpp"
#include "compound_statement.hpp"
#include "selection_statement.hpp"
#include "iteration_statement.hpp"
#include "jump_statement.hpp"
#include "block_declaration.hpp"
#include "try_block.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

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
	statement_t
;

struct statement: public statement_t
{
	statement(labeled_statement&& o): statement_t(std::move(o)){};
	statement(expression_statement&& o): statement_t(std::move(o)){};
	statement(compound_statement&& o): statement_t(std::move(o)){};
	statement(selection_statement&& o): statement_t(std::move(o)){};
	statement(iteration_statement&& o): statement_t(std::move(o)){};
	statement(jump_statement&& o): statement_t(std::move(o)){};
	statement(block_declaration&& o): statement_t(std::move(o)){};
	statement(try_block&& o): statement_t(std::move(o)){};

	statement(const statement& o): statement_t(static_cast<const statement_t&>(o)){};

	statement(statement&& o): statement_t(std::move(static_cast<statement_t&&>(std::move(o)))){};

	using statement_t::operator=;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
