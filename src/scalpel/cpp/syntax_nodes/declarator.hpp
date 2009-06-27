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

#include <memory>
#include "common.hpp"
#include "list_node.hpp"
#include "space.hpp"
#include "ptr_operator.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class direct_declarator;
typedef list_node<ptr_operator> ptr_operator_seq;

/**
\verbatim
declarator
	= {ptr_operator}, direct_declarator
;
\endverbatim
*/
class declarator: public node
{
	public:
		typedef
			sequence_node
			<
				optional_node<ptr_operator_seq>,
				optional_node<space>,
				direct_declarator
			>
			type
		;
		typedef optional_node<ptr_operator_seq> head_node_t;
		typedef
			sequence_node
			<
				optional_node<space>,
				direct_declarator
			>
			tail_sequence_node_t
		;

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

		child_const_iterator_range
		children() const;

		const std::string
		value() const;

		const tail_sequence_node_t&
		tail() const;

    private:
		std::unique_ptr<type> impl_;
};

const direct_declarator&
get_direct_declarator(const declarator& o);

}}} //namespace scalpel::cpp::syntax_nodes

#endif
