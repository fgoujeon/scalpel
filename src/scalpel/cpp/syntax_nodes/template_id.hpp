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

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ID_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_ID_HPP

#include <memory>
#include "common.hpp"
#include "common_nodes.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class template_argument;
typedef list_node<template_argument, common_nodes::comma> template_argument_list;

typedef
	sequence_node
	<
		identifier,
		optional_node<space>,
		predefined_text_node<str::left_angle_bracket>,
		optional_node<space>,
		optional_node<template_argument_list>,
		optional_node<space>,
		predefined_text_node<str::right_angle_bracket>
	>
	template_id_t
;

/**
template_id
	= type_name >> !s >> '<' >> !s >> !(template_argument_list >> !s) >> '>'
;
*/
class template_id: public composite_node
{
	public:
		typedef template_id_t type;
		typedef type::head_node_t head_node_t;
		typedef type::tail_sequence_node_t tail_sequence_node_t;

		template_id
		(
			identifier&& o0,
			optional_node<space>&& o1,
			predefined_text_node<str::left_angle_bracket>&& o2,
			optional_node<space>&& o3,
			optional_node<template_argument_list>&& o4,
			optional_node<space>&& o5,
			predefined_text_node<str::right_angle_bracket>&& o6
		);

		template_id
		(
			head_node_t&& head,
			tail_sequence_node_t&& tail
		);

		template_id(const template_id& o);

		template_id(template_id&& o);

		~template_id();

		const template_id&
		operator=(const template_id& o);

		/*
		inline
		const identifier&
		identifier_node() const;

		inline
		const optional_node<list_node<template_argument, common_nodes::comma>>&
		template_argument_list_node() const;
		*/

	private:
		std::unique_ptr<type> impl_;
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif
