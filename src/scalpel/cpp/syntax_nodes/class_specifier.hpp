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

#ifndef SCALPEL_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_CLASS_SPECIFIER_HPP

#include "common.hpp"
#include "wrappers.hpp"
#include "class_head.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class member_specification;

/**
\verbatim
class_specifier
	= class_head, "{", [member_specification], "}"
;
\endverbatim
*/
typedef
	sequence_node
	<
		class_head,
		optional_node<space>,
		simple_text_node<str::opening_brace>,
		optional_node<space>,
		incomplete_node<optional_node<member_specification>, wrappers::optional_member_specification>,
		optional_node<space>,
		simple_text_node<str::closing_brace>
	>
	class_specifier_t
;

struct class_specifier: public class_specifier_t
{
	typedef class_specifier_t type;

	class_specifier
	(
		class_head&& o1,
		optional_node<space>&& o2,
		simple_text_node<str::opening_brace>&& o3,
		optional_node<space>&& o4,
		incomplete_node<optional_node<member_specification>, wrappers::optional_member_specification>&& o5,
		optional_node<space>&& o6,
		simple_text_node<str::closing_brace>&& o7
	):
		type(o1, o2, o3, o4, o5, o6, o7)
	{
	}

	class_specifier(type&& o): type(o){}

	class_specifier(const class_specifier& o): type(o){}

	class_specifier(class_specifier&& o): type(o){}

	using type::operator=;

	const class_head&
	class_head_node() const
	{
		return get<0>(static_cast<const type&>(*this));
	}

	const optional_node<member_specification>&
	member_specification_node() const
	{
		return get<4>(static_cast<const type&>(*this)).node();
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
