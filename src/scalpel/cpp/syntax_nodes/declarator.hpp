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

#ifndef SCALPEL_CPP_SYNTAX_NODES_DECLARATOR_HPP
#define SCALPEL_CPP_SYNTAX_NODES_DECLARATOR_HPP

#include "common.hpp"
#include "list_node.hpp"
#include "space.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class direct_declarator;
class ptr_operator;
typedef list_node<ptr_operator> ptr_operator_seq;

typedef
	sequence_node
	<
		optional_node<ptr_operator_seq>,
		optional_node<space>,
		direct_declarator
	>
	declarator_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		direct_declarator
	>
	declarator_tail_t
;

/**
\verbatim
declarator
	= {ptr_operator}, direct_declarator
;
\endverbatim
*/
class declarator: public composite_node
{
	public:
		typedef declarator_t type;
		typedef optional_node<ptr_operator_seq> head_node_t;
		typedef declarator_tail_t tail_sequence_node_t;

        declarator
        (
            optional_node<ptr_operator_seq>&& ptr_operator_seq,
			optional_node<space>&& post_ptr_operator_seq_space_node,
            direct_declarator&& a_direct_declarator
        );

        declarator
        (
            head_node_t&& head,
			tail_sequence_node_t&& tail
        );

		declarator(const declarator& o);

		declarator(declarator&& o);

		~declarator();

		const declarator&
		operator=(const declarator& o);

		const direct_declarator&
		direct_declarator_node() const;

    private:
		declarator_t* impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
