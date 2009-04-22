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

#include "elaborated_type_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

elaborated_type_specifier::elaborated_type_specifier
(
	boost::optional<class_key>&& a_class_key,
	boost::optional<nested_name_specifier>&& a_nested_name_specifier,
	boost::optional<template_id>&& a_template_id,
	boost::optional<identifier>&& an_identifier,
	bool leading_double_colon,
	bool enum_keyword,
	bool typename_keyword,
	bool template_keyword
):
	class_key_(a_class_key),
	nested_name_specifier_(a_nested_name_specifier),
	template_id_(a_template_id),
	identifier_(an_identifier),
	leading_double_colon_(leading_double_colon),
	enum_keyword_(enum_keyword),
	typename_keyword_(typename_keyword),
	template_keyword_(template_keyword)
{
	update_node_list();
}

elaborated_type_specifier::elaborated_type_specifier(const elaborated_type_specifier& o):
	composite_node(),
	class_key_(o.class_key_),
	nested_name_specifier_(o.nested_name_specifier_),
	template_id_(o.template_id_),
	identifier_(o.identifier_),
	leading_double_colon_(o.leading_double_colon_),
	enum_keyword_(o.enum_keyword_),
	typename_keyword_(o.typename_keyword_),
	template_keyword_(o.template_keyword_)
{
	update_node_list();
}

elaborated_type_specifier::elaborated_type_specifier(elaborated_type_specifier&& o):
	class_key_(std::move(o.class_key_)),
	nested_name_specifier_(std::move(o.nested_name_specifier_)),
	template_id_(std::move(o.template_id_)),
	identifier_(std::move(o.identifier_)),
	leading_double_colon_(std::move(o.leading_double_colon_)),
	enum_keyword_(std::move(o.enum_keyword_)),
	typename_keyword_(std::move(o.typename_keyword_)),
	template_keyword_(std::move(o.template_keyword_))
{
	update_node_list();
}

const elaborated_type_specifier&
elaborated_type_specifier::operator=(const elaborated_type_specifier& o)
{
	class_key_ = o.class_key_;
	nested_name_specifier_ = o.nested_name_specifier_;
	template_id_ = o.template_id_;
	identifier_ = o.identifier_;
	leading_double_colon_ = o.leading_double_colon_;
	enum_keyword_ = o.enum_keyword_;
	typename_keyword_ = o.typename_keyword_;
	template_keyword_ = o.template_keyword_;
	update_node_list();

	return *this;
}

const boost::optional<const class_key&>
elaborated_type_specifier::get_class_key() const
{
	return boost::optional<const class_key&>(class_key_);
}

const boost::optional<const nested_name_specifier&>
elaborated_type_specifier::get_nested_name_specifier() const
{
	return boost::optional<const nested_name_specifier&>(nested_name_specifier_);
}

const boost::optional<const template_id&>
elaborated_type_specifier::get_template_id() const
{
	return boost::optional<const template_id&>(template_id_);
}

const boost::optional<const identifier&>
elaborated_type_specifier::get_identifier() const
{
	return boost::optional<const identifier&>(identifier_);
}

bool
elaborated_type_specifier::has_leading_double_colon() const
{
	return leading_double_colon_;
}

bool
elaborated_type_specifier::has_enum_keyword() const
{
	return enum_keyword_;
}

bool
elaborated_type_specifier::has_typename_keyword() const
{
	return typename_keyword_;
}

bool
elaborated_type_specifier::has_template_keyword() const
{
	return template_keyword_;
}

void
elaborated_type_specifier::update_node_list()
{
	clear();
	if(class_key_) add(*class_key_);
	if(nested_name_specifier_) add(*nested_name_specifier_);
	if(template_id_) add(*template_id_);
	if(identifier_) add(*identifier_);
}

}}} //namespace socoa::cpp::syntax_nodes

