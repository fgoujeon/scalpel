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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_DECLARATION_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_DECLARATION_HPP

#include "common.hpp"
#include "template_parameter_list.hpp"
#include "declaration.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

/**
template_declaration
	= !(str_p("export") >> !s) >> str_p("template") >> !s >> '<' >> !s >> template_parameter_list >> !s >> '>' >> !s >> declaration
;
*/
typedef
	sequence_node
	<
		optional_node<predefined_text_node<str::export_>>,
		optional_node<space>,
		predefined_text_node<str::template_>,
		optional_node<space>,
		predefined_text_node<str::left_angle_bracket>,
		optional_node<space>,
		template_parameter_list,
		optional_node<space>,
		predefined_text_node<str::right_angle_bracket>,
		optional_node<space>,
		declaration
	>
	template_declaration_t
;

class template_declaration: public composite_node
{
	public:
		typedef template_declaration_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		template_declaration
		(
			optional_node<predefined_text_node<str::export_>>&& o0,
			optional_node<space>&& o1,
			predefined_text_node<str::template_>&& o2,
			optional_node<space>&& o3,
			predefined_text_node<str::left_angle_bracket>&& o4,
			optional_node<space>&& o5,
			template_parameter_list&& o6,
			optional_node<space>&& o7,
			predefined_text_node<str::right_angle_bracket>&& o8,
			optional_node<space>&& o9,
			declaration&& o10
		);

		template_declaration
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		template_declaration(const template_declaration& o);

		template_declaration(template_declaration&& o);

		const template_declaration&
		operator=(const template_declaration& o);

	private:
		type impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
