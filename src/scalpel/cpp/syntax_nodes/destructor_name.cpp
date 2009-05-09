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

#include "destructor_name.hpp"

#include "common_nodes.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

destructor_name::destructor_name
(
	boost::optional<space>&& post_tilde_space_node,
	identifier_or_template_id&& identifier_or_template_id_node
):
	post_tilde_space_(post_tilde_space_node),
	identifier_or_template_id_(std::move(identifier_or_template_id_node))
{
	update_node_list();
}

destructor_name::destructor_name(const destructor_name& o):
	composite_node(),
	post_tilde_space_(o.post_tilde_space_),
	identifier_or_template_id_(o.identifier_or_template_id_)
{
	update_node_list();
}

destructor_name::destructor_name(destructor_name&& o):
	post_tilde_space_(std::move(o.post_tilde_space_)),
	identifier_or_template_id_(std::move(o.identifier_or_template_id_))
{
	update_node_list();
}

const destructor_name&
destructor_name::operator=(const destructor_name& o)
{
	post_tilde_space_ = o.post_tilde_space_;
	identifier_or_template_id_ = o.identifier_or_template_id_;

	update_node_list();

	return *this;
}

void
destructor_name::update_node_list()
{
	clear();
	add(global_nodes::tilde);
	if(post_tilde_space_) add(*post_tilde_space_);
	add(identifier_or_template_id_);
}

}}} //namespace scalpel::cpp::syntax_nodes
