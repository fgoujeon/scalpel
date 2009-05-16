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

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "ctor_initializer.hpp"
#include "compound_statement.hpp"
#include "handler_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
function_try_block
	= str_p("try") >> !s >> !(ctor_initializer >> !s) >> compound_statement >> !s >> handler_seq
;
*/
class function_try_block: public composite_node
{
	public:
		function_try_block
		(
			optional_node<space>&& post_try_keyword_space_node,
			optional_node<ctor_initializer>&& ctor_initializer_node,
			optional_node<space>&& post_ctor_initializer_space_node,
			compound_statement&& compound_statement_node,
			optional_node<space>&& post_compound_statement_space_node,
			handler_seq&& handler_seq_node
		);

		function_try_block(const function_try_block& o);

		function_try_block(function_try_block&& o);

		const function_try_block&
		operator=(const function_try_block& o);

	private:
		void
		update_node_list();

		optional_node<space> post_try_keyword_space_;
		optional_node<ctor_initializer> ctor_initializer_;
		optional_node<space> post_ctor_initializer_space_;
		compound_statement compound_statement_;
		optional_node<space> post_compound_statement_space_;
		handler_seq handler_seq_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
