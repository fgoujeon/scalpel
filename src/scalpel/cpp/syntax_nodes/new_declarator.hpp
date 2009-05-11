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

#ifndef SCALPEL_CPP_SYNTAX_NODES_NEW_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_NEW_DECLARATOR_HPP

#include <memory>
#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "space.hpp"
#include "ptr_operator_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class direct_new_declarator;

/**
new_declarator
	= ptr_operator_seq, direct_new_declarator
	| ptr_operator_seq
	| direct_new_declarator
;
*/
class new_declarator: public composite_node
{
	public:
		new_declarator
		(
			boost::optional<ptr_operator_seq>&& ptr_operator_seq_node,
			boost::optional<space>&& space_node,
			boost::optional<direct_new_declarator>&& direct_new_declarator_node
		);

		new_declarator(const new_declarator& o);

		new_declarator(new_declarator&& o);

		~new_declarator();

		const new_declarator&
		operator=(const new_declarator& o);

	private:
		void
		update_node_list();

		boost::optional<ptr_operator_seq> ptr_operator_seq_;
		boost::optional<space> space_;
		direct_new_declarator* direct_new_declarator_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
