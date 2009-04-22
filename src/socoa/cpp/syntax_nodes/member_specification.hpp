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

#ifndef SOCOA_CPP_SYNTAX_TREE_MEMBER_SPECIFICATION_HPP
#define SOCOA_CPP_SYNTAX_TREE_MEMBER_SPECIFICATION_HPP

#include "sequence_node.hpp"
#include "alternative_node.hpp"
#include "member_declaration.hpp"
#include "member_specification_access_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

typedef
	alternative_node
	<
		member_declaration,
		member_specification_access_specifier
	>
	member_specification_part
;

typedef
	sequence_node<member_specification_part>
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

}}} //namespace socoa::cpp::syntax_nodes

#endif
