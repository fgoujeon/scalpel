/*
Scalpel _ Source Code Analysis, Libre and PortablE Library
Copyright © 2008 - 2012  Florian Goujeon

This file is part of Scalpel.

Scalpel is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Scalpel is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with Scalpel.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_PARAMETER_LIST_HPP
#define SCALPEL_CPP_SYNTAX_NODES_TEMPLATE_PARAMETER_LIST_HPP

#include "template_parameter.hpp"
#include "common.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

typedef
	list_node<template_parameter>
	template_parameter_list_t
;

struct template_parameter_list: public template_parameter_list_t
{
	template_parameter_list()
	{
	}

	template_parameter_list(const template_parameter_list& o):
		template_parameter_list_t(o)
	{
	}

	template_parameter_list(template_parameter_list&& o):
		template_parameter_list_t(o)
	{
	}
};

}}} //namespace scalpel::cpp::syntax_nodes

#endif

