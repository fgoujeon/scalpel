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

#ifndef SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_MEMBER_DECLARATOR_DECLARATOR_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class member_declarator_declarator: public composite_node
{
	public:
		member_declarator_declarator
		(
			declarator&& a_declarator,
			bool pure_specifier
		);

		member_declarator_declarator(const member_declarator_declarator& o);

		member_declarator_declarator(member_declarator_declarator&& o);

		const member_declarator_declarator&
		operator=(const member_declarator_declarator& o);

		inline
		const declarator&
		declarator_node() const;

		inline
		bool
		has_pure_specifier() const;

	private:
		void
		update_node_list();

		declarator declarator_;
		bool pure_specifier_;
};

inline
const declarator&
member_declarator_declarator::declarator_node() const
{
	return declarator_;
}

inline
bool
member_declarator_declarator::has_pure_specifier() const
{
	return pure_specifier_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
