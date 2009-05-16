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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BRACKETED_INITIALIZER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BRACKETED_INITIALIZER_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "expression_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
bracketed_initializer
	= ch_p('(') >> !s >> expression_list >> !s >> ')'
;
*/
class bracketed_initializer: public composite_node
{
	public:
		bracketed_initializer
		(
			optional_node<space>&& post_opening_bracket_space_node,
			expression_list&& expression_list_node,
			optional_node<space>&& post_expression_list_space_node
		);

		bracketed_initializer(const bracketed_initializer& o);

		bracketed_initializer(bracketed_initializer&& o);

		const bracketed_initializer&
		operator=(const bracketed_initializer& o);

	private:
		void
		update_node_list();

		optional_node<space> post_opening_bracket_space_;
		expression_list expression_list_;
		optional_node<space> post_expression_list_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
