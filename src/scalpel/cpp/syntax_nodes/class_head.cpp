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

#include "class_head.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

class_head::class_head
(
	class_key&& class_key_node,
	optional_node<space>&& pre_nested_name_specifier_space_node,
	optional_node<nested_name_specifier>&& nested_name_specifier_node,
	optional_node<space>&& pre_template_id_space_node,
	optional_node<template_id>&& template_id_node,
	optional_node<space>&& pre_identifier_space_node,
	optional_node<identifier>&& identifier_node,
	optional_node<space>&& pre_base_clause_space_node,
	optional_node<base_clause>&& base_clause_node
):
	class_key_(class_key_node),
	pre_nested_name_specifier_space_(pre_nested_name_specifier_space_node),
	nested_name_specifier_(nested_name_specifier_node),
	pre_template_id_space_(pre_template_id_space_node),
	template_id_(template_id_node),
	pre_identifier_space_(pre_identifier_space_node),
	identifier_(identifier_node),
	pre_base_clause_space_(pre_base_clause_space_node),
	base_clause_(std::move(base_clause_node))
{
	update_node_list();
}

class_head::class_head(const class_head& o):
	composite_node(),
	class_key_(o.class_key_),
	pre_nested_name_specifier_space_(o.pre_nested_name_specifier_space_),
	nested_name_specifier_(o.nested_name_specifier_),
	pre_template_id_space_(o.pre_template_id_space_),
	template_id_(o.template_id_),
	pre_identifier_space_(o.pre_identifier_space_),
	identifier_(o.identifier_),
	pre_base_clause_space_(o.pre_base_clause_space_),
	base_clause_(o.base_clause_)
{
	update_node_list();
}

class_head::class_head(class_head&& o):
	composite_node(),
	class_key_(std::move(o.class_key_)),
	pre_nested_name_specifier_space_(std::move(o.pre_nested_name_specifier_space_)),
	nested_name_specifier_(std::move(o.nested_name_specifier_)),
	pre_template_id_space_(std::move(o.pre_template_id_space_)),
	template_id_(std::move(o.template_id_)),
	pre_identifier_space_(std::move(o.pre_identifier_space_)),
	identifier_(std::move(o.identifier_)),
	pre_base_clause_space_(std::move(o.pre_base_clause_space_)),
	base_clause_(std::move(o.base_clause_))
{
	update_node_list();
}

const class_head&
class_head::operator=(const class_head& o)
{
	class_key_ = o.class_key_;
	pre_nested_name_specifier_space_ = o.pre_nested_name_specifier_space_;
	nested_name_specifier_ = o.nested_name_specifier_;
	pre_template_id_space_ = o.pre_template_id_space_;
	template_id_ = o.template_id_;
	pre_identifier_space_ = o.pre_identifier_space_;
	identifier_ = o.identifier_;
	pre_base_clause_space_ = o.pre_base_clause_space_;
	base_clause_ = o.base_clause_;

	update_node_list();

	return *this;
}

void
class_head::update_node_list()
{
	clear();
	add(class_key_);
	if(pre_nested_name_specifier_space_) add(*pre_nested_name_specifier_space_);
	if(nested_name_specifier_) add(*nested_name_specifier_);
	if(pre_template_id_space_) add(*pre_template_id_space_);
	if(template_id_) add(*template_id_);
	if(pre_identifier_space_) add(*pre_identifier_space_);
	if(identifier_) add(*identifier_);
	if(pre_base_clause_space_) add(*pre_base_clause_space_);
	if(base_clause_) add(*base_clause_);
}

}}} //namespace scalpel::cpp::syntax_nodes
