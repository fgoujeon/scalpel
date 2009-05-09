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

#include "base_specifier.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

base_specifier::base_specifier
(
    bool virtual_keyword,
    bool virtual_keyword_first,
	boost::optional<space>&& post_virtual_keyword_space_node,
    boost::optional<access_specifier>&& an_access_specifier,
	boost::optional<space>&& post_access_specifier_space_node,
    boost::optional<nested_identifier_or_template_id>&& a_nested_identifier_or_template_id
):
    virtual_keyword_(virtual_keyword),
    virtual_keyword_first_(virtual_keyword_first),
	post_virtual_keyword_space_(post_virtual_keyword_space_node),
    access_specifier_(an_access_specifier),
	post_access_specifier_space_(post_access_specifier_space_node),
    nested_identifier_or_template_id_(a_nested_identifier_or_template_id)
{
	update_node_list();
}

base_specifier::base_specifier(const base_specifier& o):
	composite_node(),
    virtual_keyword_(o.virtual_keyword_),
    virtual_keyword_first_(o.virtual_keyword_first_),
	post_virtual_keyword_space_(o.post_virtual_keyword_space_),
    access_specifier_(o.access_specifier_),
	post_access_specifier_space_(o.post_access_specifier_space_),
    nested_identifier_or_template_id_(o.nested_identifier_or_template_id_)
{
	update_node_list();
}

base_specifier::base_specifier(base_specifier&& o):
    virtual_keyword_(o.virtual_keyword_),
    virtual_keyword_first_(o.virtual_keyword_first_),
	post_virtual_keyword_space_(std::move(o.post_virtual_keyword_space_)),
    access_specifier_(std::move(o.access_specifier_)),
	post_access_specifier_space_(std::move(o.post_access_specifier_space_)),
    nested_identifier_or_template_id_(std::move(o.nested_identifier_or_template_id_))
{
	update_node_list();
}

const base_specifier&
base_specifier::operator=(const base_specifier& o)
{
    virtual_keyword_ = o.virtual_keyword_;
    virtual_keyword_first_ = o.virtual_keyword_first_;
	post_virtual_keyword_space_ = o.post_virtual_keyword_space_;
    access_specifier_ = o.access_specifier_;
	post_access_specifier_space_ = o.post_access_specifier_space_;
    nested_identifier_or_template_id_ = o.nested_identifier_or_template_id_;
	update_node_list();

	return *this;
}

void
base_specifier::update_node_list()
{
	clear();
	if(virtual_keyword_first_)
	{
		if(virtual_keyword_) add(global_nodes::virtual_keyword);
		if(post_virtual_keyword_space_) add(*post_virtual_keyword_space_);
	}
	if(access_specifier_) add(*access_specifier_);
	if(post_access_specifier_space_) add(*post_access_specifier_space_);
	if(!virtual_keyword_first_)
	{
		if(virtual_keyword_) add(global_nodes::virtual_keyword);
		if(post_virtual_keyword_space_) add(*post_virtual_keyword_space_);
	}
	if(nested_identifier_or_template_id_) add(*nested_identifier_or_template_id_);
}

}}} //namespace scalpel::cpp::syntax_nodes
