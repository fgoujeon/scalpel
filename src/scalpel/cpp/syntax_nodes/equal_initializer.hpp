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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EQUAL_INITIALIZER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EQUAL_INITIALIZER_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "initializer_clause.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
equal_initializer
	= "=", initializer_clause
;
\endverbatim
*/
class equal_initializer: public composite_node
{
	public:
		equal_initializer
		(
			boost::optional<space>&& space_node,
			initializer_clause&& initializer_clause_node
		);

		equal_initializer(const equal_initializer& o);

		equal_initializer(equal_initializer&& o);

		const equal_initializer&
		operator=(const equal_initializer& o);

	private:
		void
		update_node_list();

		boost::optional<space> space_;
		initializer_clause initializer_clause_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
