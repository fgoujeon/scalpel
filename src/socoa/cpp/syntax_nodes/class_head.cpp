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

#include "class_head.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class_head::class_head
(
    class_key&& a_class_key,
    boost::optional<nested_name_specifier>&& a_nested_name_specifier,
    boost::optional<template_id>&& a_template_id,
    boost::optional<identifier>&& an_identifier,
    boost::optional<base_clause>&& a_base_clause
):
    class_key_(std::move(a_class_key)),
    nested_name_specifier_(a_nested_name_specifier),
    template_id_(a_template_id),
    identifier_(an_identifier),
    base_clause_(a_base_clause)
{
	update_node_list();
}

class_head::class_head(const class_head& o):
	composite_node(),
    class_key_(o.class_key_),
    nested_name_specifier_(o.nested_name_specifier_),
    template_id_(o.template_id_),
    identifier_(o.identifier_),
    base_clause_(o.base_clause_)
{
	update_node_list();
}

class_head::class_head(class_head&& o):
    class_key_(std::move(o.class_key_)),
    nested_name_specifier_(std::move(o.nested_name_specifier_)),
    template_id_(std::move(o.template_id_)),
    identifier_(std::move(o.identifier_)),
    base_clause_(std::move(o.base_clause_))
{
	update_node_list();
}

const class_head&
class_head::operator=(const class_head& o)
{
    class_key_ = o.class_key_;
    nested_name_specifier_ = o.nested_name_specifier_;
    template_id_ = o.template_id_;
    identifier_ = o.identifier_;
    base_clause_ = o.base_clause_;
	update_node_list();

	return *this;
}

void
class_head::update_node_list()
{
	clear();
	add(class_key_);
    if(nested_name_specifier_) add(*nested_name_specifier_);
    if(template_id_) add(*template_id_);
    if(identifier_) add(*identifier_);
    if(base_clause_) add(*base_clause_);
}

}}} //namespace socoa::cpp::syntax_nodes
