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

#ifndef SCALPEL_CPP_SYNTAX_NODES_INIT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_INIT_DECLARATOR_HPP

#include "common.hpp"
#include "declarator.hpp"
#include "initializer.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
init_declarator
	= declarator, [initializer]
;
\endverbatim
*/
typedef
	sequence_node
	<
		declarator,
		optional_node<space>,
		optional_node<initializer>
	>
	init_declarator_t
;

class init_declarator: public composite_node
{
	public:
		typedef init_declarator_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		init_declarator
		(
			declarator&& o0,
			optional_node<space>&& o1,
			optional_node<initializer>&& o2
		);

		init_declarator
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		init_declarator(const init_declarator& o);

		init_declarator(init_declarator&& o);

		const init_declarator&
		operator=(const init_declarator& o);

		inline
		const declarator&
		declarator_node() const;

	private:
		type impl_;
};

const declarator&
init_declarator::declarator_node() const
{
	return get<0>(impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
