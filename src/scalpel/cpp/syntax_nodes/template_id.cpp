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

#include "template_id.hpp"

#include "template_argument_list.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

template_id::template_id
(
	identifier&& identifier_node,
	boost::optional<space>&& post_type_name_space_node,
	boost::optional<space>&& post_opening_angle_bracket_space_node,
	boost::optional<template_argument_list>&& template_argument_list_node,
	boost::optional<space>&& post_template_argument_list_space_node
):
	identifier_(identifier_node),
	post_type_name_space_(post_type_name_space_node),
	post_opening_angle_bracket_space_(post_opening_angle_bracket_space_node),
	post_template_argument_list_space_(post_template_argument_list_space_node)
{
	if(template_argument_list_node)
		template_argument_list_ = new template_argument_list(*template_argument_list_node);
	else
		template_argument_list_ = 0;
	update_node_list();
}

template_id::template_id(const template_id& o):
	composite_node(),
	identifier_(o.identifier_),
	post_type_name_space_(o.post_type_name_space_),
	post_opening_angle_bracket_space_(o.post_opening_angle_bracket_space_),
	post_template_argument_list_space_(o.post_template_argument_list_space_)
{
	if(o.template_argument_list_)
		template_argument_list_ = new template_argument_list(*o.template_argument_list_);
	else
		template_argument_list_ = 0;
	update_node_list();
}

template_id::template_id(template_id&& o):
	identifier_(std::move(o.identifier_)),
	post_type_name_space_(std::move(o.post_type_name_space_)),
	post_opening_angle_bracket_space_(std::move(o.post_opening_angle_bracket_space_)),
	template_argument_list_(std::move(o.template_argument_list_)),
	post_template_argument_list_space_(std::move(o.post_template_argument_list_space_))
{
	update_node_list();
}

template_id::~template_id()
{
	delete template_argument_list_;
}

const template_id&
template_id::operator=(const template_id& o)
{
	identifier_ = o.identifier_;
	post_type_name_space_ = o.post_type_name_space_;
	post_opening_angle_bracket_space_ = o.post_opening_angle_bracket_space_;
	delete template_argument_list_;
	if(o.template_argument_list_)
		template_argument_list_ = new template_argument_list(*o.template_argument_list_);
	else
		template_argument_list_ = 0;
	post_template_argument_list_space_ = o.post_template_argument_list_space_;
	update_node_list();

	return *this;
}

void
template_id::update_node_list()
{
	clear();
	add(identifier_);
	if(post_type_name_space_) add(*post_type_name_space_);
	add(common_nodes::left_angle_bracket);
	if(post_opening_angle_bracket_space_) add(*post_opening_angle_bracket_space_);
	if(template_argument_list_) add(*template_argument_list_);
	if(post_template_argument_list_space_) add(*post_template_argument_list_space_);
	add(common_nodes::right_angle_bracket);
}

}}} //namespace scalpel::cpp::syntax_nodes
