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

#ifndef SCALPEL_CPP_SYNTAX_NODES_USING_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_USING_DECLARATION_HPP

#include "common.hpp"
#include "nested_name_specifier.hpp"
#include "unqualified_id.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
using_declaration
	= "using" >> !s >> !(str_p("typename") >> !s) >> !(str_p("::") >> !s) >> nested_name_specifier >> !s >> unqualified_id >> !s >> ch_p(';')
	| "using" >> !s >> str_p("::") >> !s >> unqualified_id >> !s >> ch_p(';')
;
*/
typedef
	sequence_node
	<
		simple_text_node<str::using_>,
		optional_node<space>,
		optional_node<simple_text_node<str::typename_>>,
		optional_node<space>,
		optional_node<simple_text_node<str::double_colon>>,
		optional_node<space>,
		optional_node<nested_name_specifier>,
		optional_node<space>,
		unqualified_id,
		optional_node<space>,
		simple_text_node<str::semicolon>
	>
	using_declaration_t
;

class using_declaration: public composite_node
{
	public:
		typedef using_declaration_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		using_declaration
		(
			simple_text_node<str::using_>&& o0,
			optional_node<space>&& o1,
			optional_node<simple_text_node<str::typename_>>&& o2,
			optional_node<space>&& o3,
			optional_node<simple_text_node<str::double_colon>>&& o4,
			optional_node<space>&& o5,
			optional_node<nested_name_specifier>&& o6,
			optional_node<space>&& o7,
			unqualified_id&& o8,
			optional_node<space>&& o9,
			simple_text_node<str::semicolon>&& o10
		);

		using_declaration(head_node_t&& head, tail_sequence_node_t&& tail);

		using_declaration(const using_declaration& o);

		using_declaration(using_declaration&& o);

		const using_declaration&
		operator=(const using_declaration& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
