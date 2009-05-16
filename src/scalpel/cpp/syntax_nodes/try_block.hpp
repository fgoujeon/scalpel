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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TRY_BLOCK_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TRY_BLOCK_HPP

#include "composite_node.hpp"
#include "space.hpp"
#include "compound_statement.hpp"
#include "handler_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
try_block
	= "try", compound_statement, handler_seq
;
*/
class try_block: public composite_node
{
	public:
		try_block
		(
			optional_node<space>&& post_try_keyword_space_node,
			compound_statement&& compound_statement_node,
			optional_node<space>&& post_compound_statement_space_node,
			handler_seq&& handler_seq_node
		);

		try_block(const try_block& o);

		try_block(try_block&& o);

		const try_block&
		operator=(const try_block& o);

		inline
		const compound_statement&
		compound_statement_node() const;

		inline
		const handler_seq&
		handler_seq_node() const;

	private:
		void
		update_node_list();

		optional_node<space> post_try_keyword_space_;
		compound_statement compound_statement_;
		optional_node<space> post_compound_statement_space_;
		handler_seq handler_seq_;
};

inline
const compound_statement&
try_block::compound_statement_node() const
{
	return compound_statement_;
}

inline
const handler_seq&
try_block::handler_seq_node() const
{
	return handler_seq_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
