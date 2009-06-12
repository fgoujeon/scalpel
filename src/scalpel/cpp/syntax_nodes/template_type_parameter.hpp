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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_TYPE_PARAMETER
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_TYPE_PARAMETER

#include <memory>
#include "common.hpp"
#include "identifier.hpp"
#include "id_expression.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class template_parameter_list;

typedef
	sequence_node
	<
		simple_text_node<str::template_>,
		optional_node<space>,
		simple_text_node<str::left_angle_bracket>,
		optional_node<space>,
		template_parameter_list,
		optional_node<space>,
		simple_text_node<str::right_angle_bracket>,
		optional_node<space>,
		simple_text_node<str::class_>,
		optional_node<space>,
		optional_node<identifier>,
		optional_node<space>,
		optional_node<simple_text_node<str::equal>>,
		optional_node<space>,
		optional_node<id_expression>
	>
	template_type_parameter_t
;

typedef
	sequence_node
	<
		optional_node<space>,
		simple_text_node<str::left_angle_bracket>,
		optional_node<space>,
		template_parameter_list,
		optional_node<space>,
		simple_text_node<str::right_angle_bracket>,
		optional_node<space>,
		simple_text_node<str::class_>,
		optional_node<space>,
		optional_node<identifier>,
		optional_node<space>,
		optional_node<simple_text_node<str::equal>>,
		optional_node<space>,
		optional_node<id_expression>
	>
	template_type_parameter_tail_t
;

/**
template_type_parameter
	= "template" >> !s >> '<' >> !s >> template_parameter_list >> !s >> '>' >> !s >> "class" >> !(!s >> identifier) >> !(!s >> '=' >> !s >> id_expression)
;
*/
class template_type_parameter: public composite_node
{
	public:
		typedef template_type_parameter_t type;
		typedef simple_text_node<str::template_> head_node_t;
		typedef template_type_parameter_tail_t tail_sequence_node_t;

		template_type_parameter
		(
			simple_text_node<str::template_>&& o0,
			optional_node<space>&& o1,
			simple_text_node<str::left_angle_bracket>&& o2,
			optional_node<space>&& o3,
			template_parameter_list&& o4,
			optional_node<space>&& o5,
			simple_text_node<str::right_angle_bracket>&& o6,
			optional_node<space>&& o7,
			simple_text_node<str::class_>&& o8,
			optional_node<space>&& o9,
			optional_node<identifier>&& o10,
			optional_node<space>&& o11,
			optional_node<simple_text_node<str::equal>>&& o12,
			optional_node<space>&& o13,
			optional_node<id_expression>&& o14
		);

		template_type_parameter
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		template_type_parameter(const template_type_parameter& o);

		template_type_parameter(template_type_parameter&& o);

		~template_type_parameter();

		const template_type_parameter&
		operator=(const template_type_parameter& o);

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
