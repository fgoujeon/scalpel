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

#include "template_id.hpp"

#include "template_argument_list.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

template_id::template_id
(
    identifier&& an_identifier,
    boost::optional<template_argument_list>&& a_template_argument_list
):
    identifier_(std::move(an_identifier))
{
	if(a_template_argument_list)
	{
		template_argument_list_ = std::make_shared<template_argument_list>(*a_template_argument_list);
	}
	update_node_list();
}

template_id::template_id(const template_id& o):
	composite_node(),
    identifier_(o.identifier_),
	template_argument_list_(o.template_argument_list_)
{
	update_node_list();
}

template_id::template_id(template_id&& o):
    identifier_(std::move(o.identifier_)),
	template_argument_list_(std::move(o.template_argument_list_))
{
	update_node_list();
}

const template_id&
template_id::operator=(const template_id& o)
{
    identifier_ = o.identifier_;
	template_argument_list_ = o.template_argument_list_;
	update_node_list();

	return *this;
}

void
template_id::update_node_list()
{
	clear();
	add(identifier_);
	if(template_argument_list_) add(*template_argument_list_);
}

}}} //namespace socoa::cpp::syntax_nodes
