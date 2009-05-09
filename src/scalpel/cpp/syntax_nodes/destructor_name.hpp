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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DESTRUCTOR_NAME_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DESTRUCTOR_NAME_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "identifier_or_template_id.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
destructor_name
	= "~", identifier_or_template_id
;
*/
class destructor_name: public composite_node
{
	public:
		destructor_name
		(
			boost::optional<space>&& post_tilde_space_node,
			identifier_or_template_id&& identifier_or_template_id_node
		);

		destructor_name(const destructor_name& o);

		destructor_name(destructor_name&& o);

		const destructor_name&
		operator=(const destructor_name& o);

		inline
		const identifier_or_template_id&
		identifier_node() const;

	private:
		void
		update_node_list();

		boost::optional<space> post_tilde_space_;
		identifier_or_template_id identifier_or_template_id_;
};

inline
const identifier_or_template_id&
destructor_name::identifier_node() const
{
	return identifier_or_template_id_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
