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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_PART_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_SPECIFICATION_PART_HPP

#include "composite_node.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class member_specification_part_impl;
class member_specification_part_tail;
class member_declaration;
class member_specification_access_specifier;

class member_specification_part: public composite_node
{
	public:
		typedef member_declaration head_node_t;
		typedef member_specification_part_tail tail_alternative_node_t;

		member_specification_part(member_declaration&& o);

		member_specification_part(member_specification_access_specifier&& o);

		member_specification_part(const member_specification_part& o);

		member_specification_part(member_specification_part&& o);

		~member_specification_part();

		const member_specification_part&
		operator=(const member_specification_part& o);

	private:
		member_specification_part_impl* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
