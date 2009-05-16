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

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "declarator.hpp"
#include "space.hpp"
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
class init_declarator: public composite_node
{
	public:
		init_declarator
		(
			declarator&& a_declarator,
			optional_node<space>&& space_node,
			optional_node<initializer>&& initializer_node
		);

		init_declarator(const init_declarator& o);

		init_declarator(init_declarator&& o);

		const init_declarator&
		operator=(const init_declarator& o);

		inline
		const declarator&
		declarator_node() const;

	private:
		void
		update_node_list();

		declarator declarator_;
		optional_node<space> space_;
		optional_node<initializer> initializer_;
};

inline
const declarator&
init_declarator::declarator_node() const
{
	return declarator_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
