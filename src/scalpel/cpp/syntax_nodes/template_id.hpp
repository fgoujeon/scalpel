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
#include "optional_node.hpp"
#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"
#include "sequence_node.hpp"
#include "identifier.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class template_argument;

/**
template_id
	= type_name >> !s >> '<' >> !s >> !(template_argument_list >> !s) >> '>'
;
*/
class template_id: public composite_node
{
	public:
		template_id
		(
			identifier&& identifier_node,
			optional_node<space>&& post_type_name_space_node,
			optional_node<space>&& post_opening_angle_bracket_space_node,
			optional_node<sequence_node<template_argument, common_nodes::comma>>&& template_argument_list_node,
			optional_node<space>&& post_template_argument_list_space_node
		);

		template_id(const template_id& o);

		template_id(template_id&& o);

		~template_id();

		const template_id&
		operator=(const template_id& o);

		inline
		const identifier&
		identifier_node() const;

		inline
		const optional_node<sequence_node<template_argument, common_nodes::comma>>&
		template_argument_list_node() const;

	private:
		void
		update_node_list();

		identifier identifier_;
		optional_node<space> post_type_name_space_;
		optional_node<space> post_opening_angle_bracket_space_;
		optional_node<sequence_node<template_argument, common_nodes::comma>>* template_argument_list_;
		optional_node<space> post_template_argument_list_space_;
};

inline
const identifier&
template_id::identifier_node() const
{
	return identifier_;
}

inline
const optional_node<sequence_node<template_argument, common_nodes::comma>>&
template_id::template_argument_list_node() const
{
	return *template_argument_list_;
}

}}} //namespace scalpel::cpp::syntax_nodes

#endif
