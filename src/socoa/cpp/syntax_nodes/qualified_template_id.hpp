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

#ifndef SOCOA_CPP_SYNTAX_NODES_QUALIFIED_TEMPLATE_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_QUALIFIED_TEMPLATE_ID_HPP

#include "composite_node.hpp"
#include "template_id.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class qualified_template_id: public composite_node
{
	public:
		explicit
		qualified_template_id(template_id&& a_template_id);

		qualified_template_id(const qualified_template_id& o);

		qualified_template_id(qualified_template_id&& o);

		const qualified_template_id&
		operator=(const qualified_template_id& o);

		inline
		const template_id&
		template_id_node() const;

	private:
		void
		update_node_list();

		template_id template_id_;
};

inline
const template_id&
qualified_template_id::template_id_node() const
{
	return template_id_;
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
