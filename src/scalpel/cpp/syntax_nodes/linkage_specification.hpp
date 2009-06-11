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

#ifndef SCALPEL_CPP_SYNTAX_NODES_LINKAGE_SPECIFICATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_LINKAGE_SPECIFICATION_HPP

#include "common.hpp"
#include "declaration_linkage_specification.hpp"
#include "declaration_seq_linkage_specification.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
linkage_specification
	= declaration_seq_linkage_specification
	| declaration_linkage_specification
;
*/
typedef
	alternative_node
	<
		declaration_seq_linkage_specification,
		declaration_linkage_specification
	>
	linkage_specification_t
;

class linkage_specification: public composite_node
{
	public:
		typedef linkage_specification_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_alternative_node_t tail_alternative_node_t;

		linkage_specification(declaration_linkage_specification&& o);

		linkage_specification(declaration_seq_linkage_specification&& o);

		linkage_specification(const linkage_specification& o);

		linkage_specification(linkage_specification&& o);

		const linkage_specification&
		operator=(const linkage_specification& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
