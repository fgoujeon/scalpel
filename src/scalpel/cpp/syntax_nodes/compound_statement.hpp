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

#ifndef SCALPEL_CPP_SYNTAX_NODES_COMPOUND_STATEMENT_HPP
#define SCALPEL_CPP_SYNTAX_NODES_COMPOUND_STATEMENT_HPP

#include <memory>
#include "optional_node.hpp"
#include "composite_node.hpp"
#include "list_node.hpp"
#include "space.hpp"
#include "statement.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
compound_statement
	= "{", [statement_seq], "}"
;
\endverbatim
*/
class compound_statement: public composite_node
{
	public:
		compound_statement
		(
			optional_node<space>&& post_opening_brace_space,
			optional_node<list_node<statement>>&& statement_seq_node,
			optional_node<space>&& post_statement_seq_space
		);

		compound_statement(const compound_statement& o);

		compound_statement(compound_statement&& o);

		~compound_statement();

		const compound_statement&
		operator=(const compound_statement& o);

		inline
		const optional_node<list_node<statement>>&
		statement_seq_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_opening_brace_space_;
		optional_node<list_node<statement>>* statement_seq_;
		optional_node<space> post_statement_seq_space_;
};

inline
const optional_node<list_node<statement>>&
compound_statement::statement_seq_node() const
{
	return *statement_seq_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
