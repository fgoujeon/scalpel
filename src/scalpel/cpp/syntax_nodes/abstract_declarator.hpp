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

#ifndef SCALPEL_CPP_SYNTAX_NODES_ABSTRACT_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_ABSTRACT_DECLARATOR_HPP

#include <memory>
#include "common.hpp"
#include "ptr_operator_seq.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class direct_abstract_declarator;

typedef
	alternative_node
	<
		ptr_operator_seq,
		direct_abstract_declarator
	>
	abstract_declarator_t
;

typedef
	alternative_node
	<
		direct_abstract_declarator
	>
	abstract_declarator_tail_t
;


/**
abstract_declarator
	= ptr_operator_seq
	| direct_abstract_declarator
;
*/
class abstract_declarator: public composite_node
{
	public:
		typedef abstract_declarator_t type;
		typedef ptr_operator_seq head_node_t;
		typedef abstract_declarator_tail_t tail_alternative_node_t;

		abstract_declarator(ptr_operator_seq&& o);

		abstract_declarator(direct_abstract_declarator&& o);

		abstract_declarator(const abstract_declarator& o);

		abstract_declarator(abstract_declarator&& o);

		~abstract_declarator();

		const abstract_declarator&
		operator=(const abstract_declarator& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
