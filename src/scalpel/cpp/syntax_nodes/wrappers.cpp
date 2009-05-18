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

#include "wrappers.hpp"

#include "cast_expression.hpp"
#include "statement.hpp"
#include "member_specification.hpp"

#define SCALPEL_CPP_SYNTAX_NODES_WRAPPER_DEFINITION(node_type)	\
node_type::node_type											\
(																\
	syntax_nodes::node_type&& node								\
):																\
	node_(new syntax_nodes::node_type(std::move(node)))			\
{																\
	add(*node_);												\
}																\
																\
node_type::node_type											\
(																\
	const node_type& o											\
):																\
	composite_node(),											\
	node_(new syntax_nodes::node_type(*o.node_))				\
{																\
	add(*node_);												\
}																\
																\
node_type::node_type											\
(																\
	node_type&& o												\
):																\
	composite_node(),											\
	node_(o.node_)												\
{																\
	o.node_ = 0;												\
	add(*node_);												\
}																\
																\
const node_type&												\
node_type::operator=(const node_type& o)						\
{																\
	node_ = o.node_;											\
	return *this;												\
}																\
																\
node_type::~node_type()											\
{																\
	delete node_;												\
}																\
																\
const syntax_nodes::node_type&									\
node_type::node() const											\
{																\
	return *node_;												\
}

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace wrappers
{

SCALPEL_CPP_SYNTAX_NODES_WRAPPER_DEFINITION(cast_expression)
SCALPEL_CPP_SYNTAX_NODES_WRAPPER_DEFINITION(statement)
SCALPEL_CPP_SYNTAX_NODES_WRAPPER_DEFINITION(optional_member_specification)

}}}} //namespace scalpel::cpp::syntax_nodes::wrappers

#undef SCALPEL_CPP_SYNTAX_NODES_WRAPPER_DEFINITION

