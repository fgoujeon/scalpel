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

#ifndef SCALPEL_CPP_SYNTAX_NODES_WRAPPERS_HPP
#define SCALPEL_CPP_SYNTAX_NODES_WRAPPERS_HPP

#include "composite_node.hpp"
#include "cast_expression_fwd.hpp"
#include "statement_fwd.hpp"

#define SCALPEL_CPP_SYNTAX_NODES_WRAPPER_SPECIFIER(node_type)\
class node_type: public syntax_nodes::composite_node	\
{														\
	public:												\
		explicit										\
		node_type										\
		(												\
			syntax_nodes::node_type&& node				\
		);												\
														\
		node_type										\
		(												\
			const node_type& o							\
		);												\
														\
		node_type										\
		(												\
			node_type&& o								\
		);												\
														\
		const node_type&								\
		operator=(const node_type& o);					\
														\
		~node_type();									\
														\
	private:											\
		syntax_nodes::node_type* node_;					\
};

namespace scalpel { namespace cpp { namespace syntax_nodes { namespace wrappers
{

SCALPEL_CPP_SYNTAX_NODES_WRAPPER_SPECIFIER(cast_expression)
SCALPEL_CPP_SYNTAX_NODES_WRAPPER_SPECIFIER(statement)

}}}} //namespace scalpel::cpp::syntax_nodes::wrappers

#undef SCALPEL_CPP_SYNTAX_NODES_WRAPPER_CLASS_SPECIFIER

#endif
