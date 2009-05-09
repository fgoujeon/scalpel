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

#ifndef SCALPEL_CPP_SYNTAX_NODES_EXCEPTION_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_EXCEPTION_DECLARATOR_HPP

#include <boost/optional.hpp>
#include "composite_node.hpp"
#include "type_specifier_seq.hpp"
#include "space.hpp"
#include "declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
exception_declarator
	= type_specifier_seq >> !s >> declarator
;
*/
class exception_declarator: public composite_node
{
	public:
		exception_declarator
		(
			type_specifier_seq&& type_specifier_seq_node,
			boost::optional<space>&& post_type_specifier_seq_space_node,
			declarator&& declarator_node
		);

		exception_declarator(const exception_declarator& o);

		exception_declarator(exception_declarator&& o);

		const exception_declarator&
		operator=(const exception_declarator& o);

	private:
		void
		update_node_list();

		type_specifier_seq type_specifier_seq_;
		boost::optional<space> post_type_specifier_seq_space_;
		declarator declarator_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
