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

#ifndef SCALPEL_CPP_SYNTAX_NODES_USING_DIRECTIVE_HPP
#define SCALPEL_CPP_SYNTAX_NODES_USING_DIRECTIVE_HPP

#include "common.hpp"
#include "identifier.hpp"
#include "nested_name_specifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
\verbatim
using_directive
	= "using" >> !s >> "namespace" >> !s >> !(str_p("::") >> !s) >> !(nested_name_specifier >> !s) >> identifier >> !s >> ch_p(';')
;
\endverbatim
*/
typedef
	sequence_node
	<
		predefined_text_node<str::using_>,
		optional_node<space>,
		predefined_text_node<str::namespace_>,
		optional_node<space>,
		optional_node<predefined_text_node<str::double_colon>>,
		optional_node<space>,
		optional_node<nested_name_specifier>,
		optional_node<space>,
		identifier,
		optional_node<space>,
		predefined_text_node<str::semicolon>
	>
	using_directive_t
;

class using_directive: public composite_node
{
	public:
		typedef using_directive_t type;
		typedef using_directive_t::head_node_t head_node_t;
		typedef using_directive_t::tail_sequence_node_t tail_sequence_node_t;

		using_directive
		(
			predefined_text_node<str::using_>&& o0,
			optional_node<space>&& o1,
			predefined_text_node<str::namespace_>&& o2,
			optional_node<space>&& o3,
			optional_node<predefined_text_node<str::double_colon>>&& o4,
			optional_node<space>&& o5,
			optional_node<nested_name_specifier>&& o6,
			optional_node<space>&& o7,
			identifier&& o8,
			optional_node<space>&& o9,
			predefined_text_node<str::semicolon>&& o10
		);

		using_directive(head_node_t&& head, tail_sequence_node_t&& tail);

		using_directive(const using_directive& o);

		using_directive(using_directive&& o);

		const using_directive&
		operator=(const using_directive& o);

		bool
		double_colon_node() const;

		const optional_node<nested_name_specifier>&
		nested_name_specifier_node() const;

		const identifier&
	   	identifier_node() const;

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
