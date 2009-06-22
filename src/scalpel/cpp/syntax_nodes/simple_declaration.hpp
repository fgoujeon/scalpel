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

#ifndef SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_SIMPLE_DECLARATION_HPP

#include "common.hpp"
#include "decl_specifier_seq.hpp"
#include "init_declarator_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	sequence_node
	<
		optional_node<decl_specifier_seq>,
		optional_node<space>,
		optional_node<init_declarator_list>,
		optional_node<space>,
		predefined_text_node<str::semicolon>
	>
	simple_declaration_t
;

/**
\verbatim
simple_declaration
	= [decl_specifier_seq], [init_declarator_list], ";"
;
\endverbatim
*/
class simple_declaration: public composite_node
{
	public:
		typedef simple_declaration_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		simple_declaration
		(
			optional_node<decl_specifier_seq>&& o0,
			optional_node<space>&& o1,
			optional_node<init_declarator_list>&& o2,
			optional_node<space>&& o3,
			predefined_text_node<str::semicolon>&& o4
		);

		simple_declaration
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		simple_declaration(const simple_declaration& o);

		simple_declaration(simple_declaration&& o);

		const simple_declaration&
		operator=(const simple_declaration& o);

		inline
		const optional_node<decl_specifier_seq>&
		decl_specifier_seq_node() const;

		inline
		const optional_node<init_declarator_list>&
		init_declarator_list_node() const;

	private:
		type impl_;
};

inline
const optional_node<decl_specifier_seq>&
simple_declaration::decl_specifier_seq_node() const
{
	return get<0>(impl_);
}

inline
const optional_node<init_declarator_list>&
simple_declaration::init_declarator_list_node() const
{
	return get<2>(impl_);
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
