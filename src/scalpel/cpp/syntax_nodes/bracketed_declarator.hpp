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

#ifndef SCALPEL_CPP_SYNTAX_NODES_BRACKETED_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_BRACKETED_DECLARATOR_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
bracketed_declarator
	= '(' >> !s >> declarator >> !s >> ')'
;
*/
class bracketed_declarator: public composite_node
{
	public:
		bracketed_declarator
		(
			boost::optional<space>&& post_opening_bracket_space_node,
			declarator&& declarator_node,
			boost::optional<space>&& post_declarator_space_node
		);

		bracketed_declarator(const bracketed_declarator& o);

		bracketed_declarator(bracketed_declarator&& o);

		const bracketed_declarator&
		operator=(const bracketed_declarator& o);

	private:
		void
		update_node_list();

		boost::optional<space> post_opening_bracket_space_;
		declarator declarator_;
		boost::optional<space> post_declarator_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
