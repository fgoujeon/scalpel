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

#include "qualified_nested_id.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

qualified_nested_id::qualified_nested_id
(
    bool leading_double_colon,
	boost::optional<space>&& post_double_colon_space_node,
    nested_name_specifier&& a_nested_name_specifier,
	boost::optional<space>&& post_nested_name_specifier_space_node,
    bool template_keyword,
	boost::optional<space>&& post_template_keyword_space_node,
    unqualified_id&& an_unqualified_id
):
    leading_double_colon_(leading_double_colon),
	post_double_colon_space_(post_double_colon_space_node),
    nested_name_specifier_(std::move(a_nested_name_specifier)),
	post_nested_name_specifier_space_(post_nested_name_specifier_space_node),
    template_keyword_(template_keyword),
	post_template_keyword_space_(post_template_keyword_space_node),
    unqualified_id_(std::move(an_unqualified_id))
{
	update_node_list();
}

qualified_nested_id::qualified_nested_id(const qualified_nested_id& o):
	composite_node(),
    leading_double_colon_(o.leading_double_colon_),
	post_double_colon_space_(o.post_double_colon_space_),
    nested_name_specifier_(o.nested_name_specifier_),
	post_nested_name_specifier_space_(o.post_nested_name_specifier_space_),
    template_keyword_(o.template_keyword_),
	post_template_keyword_space_(o.post_template_keyword_space_),
    unqualified_id_(o.unqualified_id_)
{
	update_node_list();
}

qualified_nested_id::qualified_nested_id(qualified_nested_id&& o):
    leading_double_colon_(std::move(o.leading_double_colon_)),
	post_double_colon_space_(std::move(o.post_double_colon_space_)),
    nested_name_specifier_(std::move(o.nested_name_specifier_)),
	post_nested_name_specifier_space_(std::move(o.post_nested_name_specifier_space_)),
    template_keyword_(std::move(o.template_keyword_)),
	post_template_keyword_space_(std::move(o.post_template_keyword_space_)),
    unqualified_id_(std::move(o.unqualified_id_))
{
	update_node_list();
}

const qualified_nested_id&
qualified_nested_id::operator=(const qualified_nested_id& o)
{
    leading_double_colon_ = o.leading_double_colon_;
	post_double_colon_space_ = o.post_double_colon_space_;
    nested_name_specifier_ = o.nested_name_specifier_;
	post_nested_name_specifier_space_ = o.post_nested_name_specifier_space_;
    template_keyword_ = o.template_keyword_;
	post_template_keyword_space_ = o.post_template_keyword_space_;
    unqualified_id_ = o.unqualified_id_;

	update_node_list();

	return *this;
}

void
qualified_nested_id::update_node_list()
{
	clear();
	if(leading_double_colon_) add(global_nodes::double_colon);
	if(post_double_colon_space_) add(*post_double_colon_space_);
	add(nested_name_specifier_);
	if(post_nested_name_specifier_space_) add(*post_nested_name_specifier_space_);
	if(template_keyword_) add(global_nodes::template_keyword);
	if(post_template_keyword_space_) add(*post_template_keyword_space_);
	add(unqualified_id_);
}

}}} //namespace scalpel::cpp::syntax_nodes
