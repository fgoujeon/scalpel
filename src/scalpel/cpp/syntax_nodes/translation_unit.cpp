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

#include "translation_unit.hpp"

namespace scalpel { namespace cpp { namespace syntax_nodes
{

translation_unit::translation_unit
(
	boost::optional<space>&& first_space_node,
	boost::optional<declaration_seq>&& declaration_seq_node,
	boost::optional<space>&& post_declaration_seq_node
):
	first_space_(first_space_node),
	declaration_seq_(declaration_seq_node),
	post_declaration_seq_(post_declaration_seq_node)
{
	update_node_list();
}

translation_unit::translation_unit(const translation_unit& o):
	composite_node(),
	first_space_(o.first_space_),
	declaration_seq_(o.declaration_seq_),
	post_declaration_seq_(o.post_declaration_seq_)
{
	update_node_list();
}

translation_unit::translation_unit(translation_unit&& o):
	composite_node(),
	first_space_(std::move(o.first_space_)),
	declaration_seq_(std::move(o.declaration_seq_)),
	post_declaration_seq_(std::move(o.post_declaration_seq_))
{
	update_node_list();
}

const translation_unit&
translation_unit::operator=(const translation_unit& o)
{
	first_space_ = o.first_space_;
	declaration_seq_ = o.declaration_seq_;
	post_declaration_seq_ = o.post_declaration_seq_;

	update_node_list();

	return *this;
}

void
translation_unit::update_node_list()
{
	clear();
	if(first_space_) add(*first_space_);
	if(declaration_seq_) add(*declaration_seq_);
	if(post_declaration_seq_) add(*post_declaration_seq_);
}

}}} //namespace scalpel::cpp::syntax_nodes

