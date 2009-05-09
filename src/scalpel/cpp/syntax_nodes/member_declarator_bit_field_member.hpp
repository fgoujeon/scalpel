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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_BIT_FIELD_MEMBER_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_BIT_FIELD_MEMBER_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class member_declarator_bit_field_member: public composite_node
{
	public:
		member_declarator_bit_field_member
		(
			boost::optional<identifier>&& an_identifier
		);

		member_declarator_bit_field_member(const member_declarator_bit_field_member& o);

		member_declarator_bit_field_member(member_declarator_bit_field_member&& o);

		const member_declarator_bit_field_member&
		operator=(const member_declarator_bit_field_member& o);

		inline
		const boost::optional<const identifier&>
		identifier_node() const;

	private:
		void
		update_node_list();

		boost::optional<identifier> identifier_;
};

inline
const boost::optional<const identifier&>
member_declarator_bit_field_member::identifier_node() const
{
	return boost::optional<const identifier&>(identifier_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
