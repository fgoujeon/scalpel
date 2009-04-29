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

#include "namespace_definition.hpp"

#include "declaration_seq.hpp"
#include "common_nodes.hpp"

namespace socoa { namespace cpp { namespace syntax_nodes
{

namespace_definition::namespace_definition
(
	boost::optional<space>&& post_namespace_keyword_space_node,
	boost::optional<identifier>&& identifier_node,
	boost::optional<space>&& post_identifier_space_node,
	boost::optional<space>&& post_opening_brace_space_node,
	boost::optional<declaration_seq>&& declaration_seq_node,
	boost::optional<space>&& post_declaration_seq_space_node
):
	post_namespace_keyword_space_(post_namespace_keyword_space_node),
	identifier_(identifier_node),
	post_identifier_space_(post_identifier_space_node),
	post_opening_brace_space_(post_opening_brace_space_node),
	post_declaration_seq_space_(post_declaration_seq_space_node)
{
	if(declaration_seq_node)
	{
		declaration_seq_ = std::move(std::unique_ptr<declaration_seq>(new declaration_seq(*declaration_seq_node)));
	}
	update_node_list();
}

namespace_definition::namespace_definition(const namespace_definition& o):
	composite_node(),
	post_namespace_keyword_space_(o.post_namespace_keyword_space_),
	identifier_(o.identifier_),
	post_identifier_space_(o.post_identifier_space_),
	post_opening_brace_space_(o.post_opening_brace_space_),
	post_declaration_seq_space_(o.post_declaration_seq_space_)
{
	if(o.declaration_seq_)
	{
		declaration_seq_ = std::move(std::unique_ptr<declaration_seq>(new declaration_seq(*o.declaration_seq_)));
	}
	update_node_list();
}

namespace_definition::namespace_definition(namespace_definition&& o):
	post_namespace_keyword_space_(std::move(o.post_namespace_keyword_space_)),
	identifier_(std::move(o.identifier_)),
	post_identifier_space_(std::move(o.post_identifier_space_)),
	post_opening_brace_space_(std::move(o.post_opening_brace_space_)),
	declaration_seq_(std::move(o.declaration_seq_)),
	post_declaration_seq_space_(std::move(o.post_declaration_seq_space_))
{
	update_node_list();
}

const namespace_definition&
namespace_definition::operator=(const namespace_definition& o)
{
	post_namespace_keyword_space_ = o.post_namespace_keyword_space_;
	identifier_ = o.identifier_;
	post_identifier_space_ = o.post_identifier_space_;
	post_opening_brace_space_ = o.post_opening_brace_space_;
	if(o.declaration_seq_)
	{
		declaration_seq_ = std::move(std::unique_ptr<declaration_seq>(new declaration_seq(*o.declaration_seq_)));
	}
	post_declaration_seq_space_ = o.post_declaration_seq_space_;

	update_node_list();

	return *this;
}

void
namespace_definition::update_node_list()
{
	clear();
	add(namespace_keyword);
	if(post_namespace_keyword_space_) add(*post_namespace_keyword_space_);
	if(identifier_) add(*identifier_);
	if(post_identifier_space_) add(*post_identifier_space_);
	add(opening_brace);
	if(post_opening_brace_space_) add(*post_opening_brace_space_);
	if(declaration_seq_) add(*declaration_seq_);
	if(post_declaration_seq_space_) add(*post_declaration_seq_space_);
	add(closing_brace);
}

}}} //namespace socoa::cpp::syntax_nodes
