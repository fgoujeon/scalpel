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

#ifndef SOCOA_CPP_SYNTAX_NODES_AROW_PSEUDO_DESTRUCTOR_NAME_HPP
#define SOCOA_CPP_SYNTAX_NODES_AROW_PSEUDO_DESTRUCTOR_NAME_HPP

#include "composite_node.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class arrow_pseudo_destructor_name: public composite_node
{
	public:
		arrow_pseudo_destructor_name
		(
		);

		arrow_pseudo_destructor_name(const arrow_pseudo_destructor_name& o);

		arrow_pseudo_destructor_name(arrow_pseudo_destructor_name&& o);

		const arrow_pseudo_destructor_name&
		operator=(const arrow_pseudo_destructor_name& o);

	private:
		void
		update_node_list();
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
