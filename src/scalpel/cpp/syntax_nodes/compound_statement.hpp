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
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "sequence_node.hpp"
#include "space.hpp"
#include "statement_fwd.hpp"

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
			boost::optional<space>&& post_opening_brace_space,
			boost::optional<sequence_node<statement>>&& statement_seq_node,
			boost::optional<space>&& post_statement_seq_space
		);

		compound_statement(const compound_statement& o);

		compound_statement(compound_statement&& o);

		~compound_statement();

		const compound_statement&
		operator=(const compound_statement& o);

		inline
		const boost::optional<sequence_node<statement>&>
		statement_seq_node() const;

	private:
		void
		update_node_list();

		boost::optional<space> post_opening_brace_space_;
		sequence_node<statement>* statement_seq_;
		boost::optional<space> post_statement_seq_space_;
};

inline
const boost::optional<sequence_node<statement>&>
compound_statement::statement_seq_node() const
{
	if(statement_seq_)
		return boost::optional<sequence_node<statement>&>(*statement_seq_);
	else
		return boost::optional<sequence_node<statement>&>();
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
