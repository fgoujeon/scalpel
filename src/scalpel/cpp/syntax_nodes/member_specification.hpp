/*
Scalpel - Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2010  Florian Goujeon

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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_HPP

#include "member_specification_part.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	list_node<member_specification_part>
	member_specification_t
;

class member_specification: public member_specification_t
{
	public:
        member_specification(){};

        member_specification(const member_specification& s): member_specification_t(static_cast<const member_specification_t&>(s)){};

        member_specification(member_specification&& s): member_specification_t(static_cast<member_specification_t&&>(s)){};

		static
		const leaf_node&
		separator_node;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
