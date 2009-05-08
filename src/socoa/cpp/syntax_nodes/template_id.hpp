/*
Socoa - Source Code Analysis Library
Copyright © 2008, 2009  Florian Goujeon

This file is part of Socoa.

Socoa is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Socoa is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Socoa.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SOCOA_CPP_SYNTAX_NODES_TEMPLATE_ID_HPP
#define SOCOA_CPP_SYNTAX_NODES_TEMPLATE_ID_HPP

#include <memory>
#include <boost/optional.hpp>
#include "../../util/extern_strings.hpp"
#include "composite_node.hpp"
#include "sequence_node.hpp"
#include "identifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
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
			boost::optional<space>&& post_type_name_space_node,
			boost::optional<space>&& post_opening_angle_bracket_space_node,
			boost::optional<sequence_node<template_argument, global_nodes::comma>>&& template_argument_list_node,
			boost::optional<space>&& post_template_argument_list_space_node
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
		const boost::optional<const sequence_node<template_argument, global_nodes::comma>&>
		template_argument_list_node() const;

	private:
		void
		update_node_list();

		identifier identifier_;
		boost::optional<space> post_type_name_space_;
		boost::optional<space> post_opening_angle_bracket_space_;
		sequence_node<template_argument, global_nodes::comma>* template_argument_list_;
		boost::optional<space> post_template_argument_list_space_;
};

inline
const identifier&
template_id::identifier_node() const
{
	return identifier_;
}

inline
const boost::optional<const sequence_node<template_argument, global_nodes::comma>&>
template_id::template_argument_list_node() const
{
	if(template_argument_list_)
		return boost::optional<const sequence_node<template_argument, global_nodes::comma>&>(*template_argument_list_);
	else
		return boost::optional<const sequence_node<template_argument, global_nodes::comma>&>();
}

}}} //namespace socoa::cpp::syntax_nodes

#endif
