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

#ifndef SOCOA_CPP_SYNTAX_NODES_NEW_TYPE_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_NEW_TYPE_ID_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "new_declarator.hpp"
#include "type_specifier_seq.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

/**
new_type_id
	= type_specifier_seq >> !(!s >> new_declarator)
;
*/
class new_type_id: public composite_node
{
	public:
		new_type_id
		(
			type_specifier_seq&& type_specifier_seq_node,
			boost::optional<space>&& pre_new_declarator_space_node,
			boost::optional<new_declarator>&& new_declarator_node
		);

		new_type_id(const new_type_id& o);

		new_type_id(new_type_id&& o);

		const new_type_id&
		operator=(const new_type_id& o);

	private:
		void
		update_node_list();

		type_specifier_seq type_specifier_seq_;
		boost::optional<space> pre_new_declarator_space_;
		boost::optional<new_declarator> new_declarator_;
};

}}} //namespace socoa::cpp::syntax_nodes

#endif
