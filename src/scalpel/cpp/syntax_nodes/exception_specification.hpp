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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXCEPTION_SPECIFICATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXCEPTION_SPECIFICATION_HPP

#include "optional_node.hpp"
#include "composite_node.hpp"
#include "space.hpp"
#include "type_id_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
exception_specification
	= "throw", "(", [type_id_list], ")"
;
*/
class exception_specification: public composite_node
{
	public:
		exception_specification
		(
			optional_node<space>&& post_throw_keyword_space_node,
			optional_node<space>&& post_opening_bracket_space_node,
			optional_node<type_id_list>&& type_id_list_node,
			optional_node<space>&& post_type_id_list_space_node
		);

		exception_specification(const exception_specification& o);

		exception_specification(exception_specification&& o);

		const exception_specification&
		operator=(const exception_specification& o);

	private:
		void
		update_node_list();

		optional_node<space> post_throw_keyword_space_;
		optional_node<space> post_opening_bracket_space_;
		optional_node<type_id_list> type_id_list_;
		optional_node<space> post_type_id_list_space_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
