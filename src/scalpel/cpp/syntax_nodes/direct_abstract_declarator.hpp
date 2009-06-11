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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DIRECT_ABSTRACT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DIRECT_ABSTRACT_DECLARATOR_HPP

#include <memory>
#include "common.hpp"
#include "direct_declarator.hpp"
#include "bracketed_abstract_declarator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
direct_abstract_declarator
	= bracketed_abstract_declarator
	| direct_declarator_last_part_seq
;
*/
typedef
	alternative_node
	<
		bracketed_abstract_declarator,
		direct_declarator_last_part_seq
	>
	direct_abstract_declarator_t
;

class direct_abstract_declarator: public composite_node
{
	public:
		typedef direct_abstract_declarator_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_alternative_node_t tail_alternative_node_t;

		direct_abstract_declarator(const bracketed_abstract_declarator& o);

		direct_abstract_declarator(const direct_declarator_last_part_seq& o);

		direct_abstract_declarator(const direct_abstract_declarator& o);

		direct_abstract_declarator(direct_abstract_declarator&& o);

		~direct_abstract_declarator();

		const direct_abstract_declarator&
		operator=(const direct_abstract_declarator& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
