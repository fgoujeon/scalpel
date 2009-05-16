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

#include "using_directive.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

using_directive::using_directive
(
	optional_node<space>&& post_using_keyword_space_node,
	optional_node<space>&& post_namespace_keyword_space_node,
	bool leading_double_colon,
	optional_node<space>&& post_leading_double_colon_space_node,
	optional_node<nested_name_specifier>&& nested_name_specifier_node,
	optional_node<space>&& post_nested_name_specifier_space_node,
	identifier&& identifier_node,
	optional_node<space>&& post_identifier_space_node
):
	post_using_keyword_space_(post_using_keyword_space_node),
	post_namespace_keyword_space_(post_namespace_keyword_space_node),
	leading_double_colon_(leading_double_colon),
	post_leading_double_colon_space_(post_leading_double_colon_space_node),
	nested_name_specifier_(nested_name_specifier_node),
	post_nested_name_specifier_space_(post_nested_name_specifier_space_node),
	identifier_(identifier_node),
	post_identifier_space_(post_identifier_space_node)
{
	update_node_list();
}

using_directive::using_directive(const using_directive& o):
	composite_node(),
	post_using_keyword_space_(o.post_using_keyword_space_),
	post_namespace_keyword_space_(o.post_namespace_keyword_space_),
	leading_double_colon_(o.leading_double_colon_),
	post_leading_double_colon_space_(o.post_leading_double_colon_space_),
	nested_name_specifier_(o.nested_name_specifier_),
	post_nested_name_specifier_space_(o.post_nested_name_specifier_space_),
	identifier_(o.identifier_),
	post_identifier_space_(o.post_identifier_space_)
{
	update_node_list();
}

using_directive::using_directive(using_directive&& o):
	post_using_keyword_space_(std::move(o.post_using_keyword_space_)),
	post_namespace_keyword_space_(std::move(o.post_namespace_keyword_space_)),
	leading_double_colon_(std::move(o.leading_double_colon_)),
	post_leading_double_colon_space_(std::move(o.post_leading_double_colon_space_)),
	nested_name_specifier_(std::move(o.nested_name_specifier_)),
	post_nested_name_specifier_space_(std::move(o.post_nested_name_specifier_space_)),
	identifier_(std::move(o.identifier_)),
	post_identifier_space_(std::move(o.post_identifier_space_))
{
	update_node_list();
}

const using_directive&
using_directive::operator=(const using_directive& o)
{
	post_using_keyword_space_ = o.post_using_keyword_space_;
	post_namespace_keyword_space_ = o.post_namespace_keyword_space_;
	leading_double_colon_ = o.leading_double_colon_;
	post_leading_double_colon_space_ = o.post_leading_double_colon_space_;
	nested_name_specifier_ = o.nested_name_specifier_;
	post_nested_name_specifier_space_ = o.post_nested_name_specifier_space_;
	identifier_ = o.identifier_;
	post_identifier_space_ = o.post_identifier_space_;

	update_node_list();

	return *this;
}

void
using_directive::update_node_list()
{
	clear();
	add(common_nodes::using_keyword);
	if(post_using_keyword_space_) add(*post_using_keyword_space_);
	add(common_nodes::namespace_keyword);
	if(post_namespace_keyword_space_) add(*post_namespace_keyword_space_);
	if(leading_double_colon_) add(common_nodes::double_colon);
	if(post_leading_double_colon_space_) add(*post_leading_double_colon_space_);
	if(nested_name_specifier_) add(*nested_name_specifier_);
	if(post_nested_name_specifier_space_) add(*post_nested_name_specifier_space_);
	add(identifier_);
	if(post_identifier_space_) add(*post_identifier_space_);
	add(common_nodes::semicolon);
}

}}} //namespace scalpel::cpp::syntax_nodes

