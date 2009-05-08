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

#include "class_template_elaborated_specifier.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

class_template_elaborated_specifier::class_template_elaborated_specifier
(
	class_key&& class_key_node,
	boost::optional<space>&& post_class_key_space_node,
	bool double_colon,
	boost::optional<space>&& post_double_colon_space_node,
	boost::optional<nested_name_specifier>&& nested_name_specifier_node,
	boost::optional<space>&& post_nested_name_specifier_space_node,
	template_id&& template_id_node
):
	class_key_(class_key_node),
	post_class_key_space_(post_class_key_space_node),
	double_colon_(double_colon),
	post_double_colon_space_(post_double_colon_space_node),
	nested_name_specifier_(nested_name_specifier_node),
	post_nested_name_specifier_space_(post_nested_name_specifier_space_node),
	template_id_(template_id_node)
{
	update_node_list();
}

class_template_elaborated_specifier::class_template_elaborated_specifier(const class_template_elaborated_specifier& o):
	composite_node(),
	class_key_(o.class_key_),
	post_class_key_space_(o.post_class_key_space_),
	double_colon_(o.double_colon_),
	post_double_colon_space_(o.post_double_colon_space_),
	nested_name_specifier_(o.nested_name_specifier_),
	post_nested_name_specifier_space_(o.post_nested_name_specifier_space_),
	template_id_(o.template_id_)
{
	update_node_list();
}

class_template_elaborated_specifier::class_template_elaborated_specifier(class_template_elaborated_specifier&& o):
	composite_node(),
	class_key_(std::move(o.class_key_)),
	post_class_key_space_(std::move(o.post_class_key_space_)),
	double_colon_(std::move(o.double_colon_)),
	post_double_colon_space_(std::move(o.post_double_colon_space_)),
	nested_name_specifier_(std::move(o.nested_name_specifier_)),
	post_nested_name_specifier_space_(std::move(o.post_nested_name_specifier_space_)),
	template_id_(std::move(o.template_id_))
{
	update_node_list();
}

const class_template_elaborated_specifier&
class_template_elaborated_specifier::operator=(const class_template_elaborated_specifier& o)
{
	class_key_ = o.class_key_;
	post_class_key_space_ = o.post_class_key_space_;
	double_colon_ = o.double_colon_;
	post_double_colon_space_ = o.post_double_colon_space_;
	nested_name_specifier_ = o.nested_name_specifier_;
	post_nested_name_specifier_space_ = o.post_nested_name_specifier_space_;
	template_id_ = o.template_id_;

	update_node_list();

	return *this;
}

void
class_template_elaborated_specifier::update_node_list()
{
	clear();
	add(class_key_);
	if(post_class_key_space_) add(*post_class_key_space_);
	if(double_colon_) add(global_nodes::double_colon);
	if(post_double_colon_space_) add(*post_double_colon_space_);
	if(nested_name_specifier_) add(*nested_name_specifier_);
	if(post_nested_name_specifier_space_) add(*post_nested_name_specifier_space_);
	add(template_id_);
}

}}} //namespace socoa::cpp::syntax_nodes

